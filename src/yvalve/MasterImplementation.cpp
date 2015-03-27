/*
 *	PROGRAM:		Firebird interface.
 *	MODULE:			MasterImplementation.cpp
 *	DESCRIPTION:	Main firebird interface, used to get other interfaces.
 *
 *  The contents of this file are subject to the Initial
 *  Developer's Public License Version 1.0 (the "License");
 *  you may not use this file except in compliance with the
 *  License. You may obtain a copy of the License at
 *  http://www.ibphoenix.com/main.nfs?a=ibphoenix&page=ibp_idpl.
 *
 *  Software distributed under the License is distributed AS IS,
 *  WITHOUT WARRANTY OF ANY KIND, either express or implied.
 *  See the License for the specific language governing rights
 *  and limitations under the License.
 *
 *  The Original Code was created by Alex Peshkov
 *  for the Firebird Open Source RDBMS project.
 *
 *  Copyright (c) 2010 Alex Peshkov <peshkoff at mail.ru>
 *  and all contributors signed below.
 *
 *  All Rights Reserved.
 *  Contributor(s): ______________________________________.
 *
 *
 */

#include "firebird.h"
#include "firebird/Interface.h"

#include <string.h>

#include "../yvalve/MasterImplementation.h"
#include "../common/classes/init.h"
#include "../common/MsgMetadata.h"
#include "../common/StatusHolder.h"
#include "../yvalve/PluginManager.h"
#include "../common/classes/GenericMap.h"
#include "../common/classes/fb_pair.h"
#include "../common/classes/rwlock.h"
#include "../common/classes/semaphore.h"
#include "../common/isc_proto.h"
#include "../common/ThreadStart.h"
#include "../common/utils_proto.h"
#include "../jrd/ibase.h"
#include "../yvalve/utl_proto.h"

using namespace Firebird;

namespace Why {

//
// getStatus()
//

class UserStatus FB_FINAL : public Firebird::DisposeIface<Firebird::BaseStatus<UserStatus> >
{
public:
	// IStatus implementation
	void dispose()
	{
		delete this;
	}
};

IStatus* MasterImplementation::getStatus()
{
	return new UserStatus;
}


//
// getDispatcher()
//

IProvider* MasterImplementation::getDispatcher()
{
	IProvider* dispatcher = new Dispatcher;
	dispatcher->addRef();
	return dispatcher;
}

//
// getDtc()
//

Static<Dtc> MasterImplementation::dtc;

Dtc* MasterImplementation::getDtc()
{
	return &dtc;
}

//
// getPluginManager()
//

IPluginManager* MasterImplementation::getPluginManager()
{
	static Static<PluginManager> manager;

	return &manager;
}

IMetadataBuilder* MasterImplementation::getMetadataBuilder(CheckStatusWrapper* status, unsigned fieldCount)
{
	try
	{
		IMetadataBuilder* bld = new MetadataBuilder(fieldCount);
		bld->addRef();
		return bld;
	}
	catch (const Exception& ex)
	{
		ex.stuffException(status);
		return NULL;
	}
}

/***
IDebug* MasterImplementation::getDebug()
{
#ifdef DEV_BUILD
	return getImpDebug();
#else
	return NULL;
#endif
}
***/

int MasterImplementation::serverMode(int mode)
{
	static int currentMode = -1;
	if (mode >= 0)
		currentMode = mode;
	return currentMode;
}

} // namespace Why

//
// timer
//

namespace Why {

namespace {

// Protects timerQueue array
GlobalPtr<Mutex> timerAccess;
// Protects from races during module unload process
// Should be taken before timerAccess
GlobalPtr<Mutex> timerPause;

GlobalPtr<Semaphore> timerWakeup;
// Should use atomic flag for thread stop to provide correct membar
AtomicCounter stopTimerThread(0);
Thread::Handle timerThreadHandle = 0;

struct TimerEntry
{
	ISC_UINT64 fireTime;
	ITimer* timer;

	static const ISC_UINT64 generate(const TimerEntry& item) { return item.fireTime; }
	static THREAD_ENTRY_DECLARE timeThread(THREAD_ENTRY_PARAM);

	static void init()
	{
		Thread::start(timeThread, 0, 0, &timerThreadHandle);
	}

	static void cleanup();
};

typedef SortedArray<TimerEntry, InlineStorage<TimerEntry, 64>, ISC_UINT64, TimerEntry> TimerQueue;
GlobalPtr<TimerQueue> timerQueue;

InitMutex<TimerEntry> timerHolder("TimerHolder");

void TimerEntry::cleanup()
{
	{
		MutexLockGuard guard(timerAccess, FB_FUNCTION);

		stopTimerThread.setValue(1);
		timerWakeup->release();
	}
	Thread::waitForCompletion(timerThreadHandle);

	while (timerQueue->hasData())
	{
		ITimer* timer = NULL;
		{
			MutexLockGuard guard(timerAccess, FB_FUNCTION);

			TimerEntry* e = timerQueue->end();
			timer = (--e)->timer;
			timerQueue->remove(e);
		}
		timer->release();
	}
}

ISC_UINT64 curTime()
{
	ISC_UINT64 rc = fb_utils::query_performance_counter();
	rc *= 1000000;
	rc /= fb_utils::query_performance_frequency();
	return rc;
}

TimerEntry* getTimer(ITimer* timer)
{
	fb_assert(timerAccess->locked());

	for (unsigned int i = 0; i < timerQueue->getCount(); ++i)
	{
		TimerEntry& e(timerQueue->operator[](i));
		if (e.timer == timer)
		{
			return &e;
		}
	}

	return NULL;
}

THREAD_ENTRY_DECLARE TimerEntry::timeThread(THREAD_ENTRY_PARAM)
{
	while (stopTimerThread.value() == 0)
	{
		ISC_UINT64 microSeconds = 0;

		{
			MutexLockGuard pauseGuard(timerPause, FB_FUNCTION);
			MutexLockGuard guard(timerAccess, FB_FUNCTION);

			const ISC_UINT64 cur = curTime();

			while (timerQueue->getCount() > 0)
			{
				TimerEntry e(timerQueue->operator[](0));

				if (e.fireTime <= cur)
				{
					timerQueue->remove((FB_SIZE_T) 0);

					// We must leave timerAccess mutex here to avoid deadlocks
					MutexUnlockGuard ug(timerAccess, FB_FUNCTION);

					e.timer->handler();
					e.timer->release();
				}
				else
				{
					microSeconds = e.fireTime - cur;
					break;
				}
			}
		}

		if (microSeconds)
		{
			timerWakeup->tryEnter(0, microSeconds / 1000);
		}
		else
		{
			timerWakeup->enter();
		}
	}

	return 0;
}

} // namespace

class TimerImplementation :
	public AutoIface<ITimerControlImpl<TimerImplementation, CheckStatusWrapper> >
{
public:
	// ITimerControl implementation
	void start(CheckStatusWrapper* status, ITimer* timer, ISC_UINT64 microSeconds)
	{
		try
		{
			MutexLockGuard guard(timerAccess, FB_FUNCTION);

			if (stopTimerThread.value() != 0)
			{
				// Ignore an attempt to start timer - anyway thread to make it fire is down

				// We must leave timerAccess mutex here to avoid deadlocks
				MutexUnlockGuard ug(timerAccess, FB_FUNCTION);

				timer->addRef();
				timer->release();
				return;
			}

			timerHolder.init();

			TimerEntry* curTimer = getTimer(timer);
			if (!curTimer)
			{
				TimerEntry newTimer;

				newTimer.timer = timer;
				newTimer.fireTime = curTime() + microSeconds;
				timerQueue->add(newTimer);
				timer->addRef();
			}
			else
			{
				curTimer->fireTime = curTime() + microSeconds;
			}

			timerWakeup->release();
		}
		catch (const Firebird::Exception& ex)
		{
			ex.stuffException(status);
		}
	}

	void stop(CheckStatusWrapper* status, ITimer* timer)
	{
		try
		{
			MutexLockGuard guard(timerAccess, FB_FUNCTION);

			TimerEntry* curTimer = getTimer(timer);
			if (curTimer)
			{
				curTimer->timer->release();
				timerQueue->remove(curTimer);
			}
		}
		catch (const Firebird::Exception& ex)
		{
			ex.stuffException(status);
		}
	}
};

ITimerControl* MasterImplementation::getTimerControl()
{
	static Static<TimerImplementation> timer;

	return &timer;
}

void shutdownTimers()
{
	timerHolder.cleanup();
}

Mutex& pauseTimer()
{
	return timerPause;
}

} // namespace Why


//
// Util (misc calls)
//

namespace Why {

	extern UtilInterface utilInterface;		// Implemented in utl.cpp

	IUtil* MasterImplementation::getUtilInterface()
	{
		return &utilInterface;
	}

} // namespace Why


//
// ConfigManager (config info access)
//

namespace Firebird {

	extern IConfigManager* iConfigManager;

} // namespace Firebird

namespace Why {

	IConfigManager* MasterImplementation::getConfigManager()
	{
		return Firebird::iConfigManager;
	}

} // namespace Why


//
// get master
//

namespace Firebird
{
	typedef IMaster* IMasterPtr;

	extern "C" IMasterPtr API_ROUTINE fb_get_master_interface()
	{
		static Static<Why::MasterImplementation> instance;
		return &instance;
	}
}
