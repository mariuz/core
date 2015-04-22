/*
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
 *  Copyright (c) 2008 Alex Peshkov <alexpeshkoff@users.sf.net>
 *  and all contributors signed below.
 *
 *  All Rights Reserved.
 *  Contributor(s): ______________________________________.
 */

#include "firebird.h"
#include "../common/classes/ClumpletWriter.h"
#include "../jrd/UserManagement.h"
#include "../jrd/jrd.h"
#include "../jrd/tra.h"
#include "../common/msg_encode.h"
#include "../utilities/gsec/gsec.h"
#include "../common/security.h"
#include "../jrd/met_proto.h"
#include "../jrd/ini.h"
#include "gen/ids.h"

using namespace Jrd;
using namespace Firebird;

namespace
{
	class UserIdInfo : public AutoIface<ILogonInfoImpl<UserIdInfo, CheckStatusWrapper> >
	{
	public:
		explicit UserIdInfo(const Attachment* pAtt)
			: att(pAtt)
		{ }

		// ILogonInfo implementation
		const char* name()
		{
			return att->att_user->usr_user_name.c_str();
		}

		const char* role()
		{
			return att->att_user->usr_sql_role_name.c_str();
		}

		const char* networkProtocol()
		{
			return att->att_network_protocol.c_str();
		}

		const char* remoteAddress()
		{
			return att->att_remote_address.c_str();
		}

		const unsigned char* authBlock(unsigned* length)
		{
			const Auth::AuthenticationBlock& aBlock = att->att_user->usr_auth_block;
			*length = aBlock.getCount();
			return aBlock.getCount() ? aBlock.begin() : NULL;
		}

	private:
		const Attachment* att;
	};

	class FillSnapshot : public AutoIface<IListUsersImpl<FillSnapshot, CheckStatusWrapper> >
	{
	public:
		explicit FillSnapshot(UserManagement* um)
			: userManagement(um), pos(0)
		{ }

		// IListUsers implementation
		void list(CheckStatusWrapper* status, IUser* user)
		{
			try
			{
				userManagement->list(user, pos);
			}
			catch (const Exception& ex)
			{
				ex.stuffException(status);
			}
		}

	private:
		UserManagement* userManagement;

	public:
		unsigned pos;
	};

	class OldAttributes : public AutoIface<IListUsersImpl<OldAttributes, CheckStatusWrapper> >
	{
	public:
		OldAttributes()
			: present(false)
		{ }

		// IListUsers implementation
		void list(CheckStatusWrapper* status, IUser* data)
		{
			try
			{
				value = data->attributes()->entered() ? data->attributes()->get() : "";
				present = true;
			}
			catch (const Exception& ex)
			{
				ex.stuffException(status);
			}
		}

		string value;
		bool present;
	};
} // anonymous namespace

const Format* UsersTableScan::getFormat(thread_db* tdbb, jrd_rel* relation) const
{
	jrd_tra* const transaction = tdbb->getTransaction();
	return transaction->getUserManagement()->getList(tdbb, relation)->getFormat();
}


bool UsersTableScan::retrieveRecord(thread_db* tdbb, jrd_rel* relation,
									FB_UINT64 position, Record* record) const
{
	jrd_tra* const transaction = tdbb->getTransaction();
	return transaction->getUserManagement()->getList(tdbb, relation)->fetch(position, record);
}


UserManagement::UserManagement(jrd_tra* tra)
	: SnapshotData(*tra->tra_pool),
	  threadDbb(NULL),
	  commands(*tra->tra_pool),
	  managers(*tra->tra_pool),
	  plugins(*tra->tra_pool),
	  att(tra->tra_attachment)
{
	if (!att || !att->att_user)
	{
		(Arg::Gds(isc_random) << "Unknown user name for given transaction").raise();
	}

	plugins = att->att_database->dbb_config->getPlugins(IPluginManager::TYPE_AUTH_USER_MANAGEMENT);
}


IManagement* UserManagement::registerManager(Auth::Get& getPlugin, const char* plugName)
{
	IManagement* manager = getPlugin.plugin();
	fb_assert(manager);

	// Start new management plugin ...
	LocalStatus status;
	CheckStatusWrapper statusWrapper(&status);

	UserIdInfo idInfo(att);
	manager->start(&statusWrapper, &idInfo);
	if (status.getState() & IStatus::STATE_ERRORS)
	{
		status_exception::raise(&statusWrapper);
	}

	// ... and store it in cache
	Manager& m(managers.add());
	m.first = plugName;
	m.second = manager;
	manager->addRef();

	return manager;
}


IManagement* UserManagement::getManager(const char* name)
{
	// Determine required name
	NoCaseString plugName;
	NoCaseString p(plugins);
	if (!(name && name[0]))	// Use default plugin
		plugName.getWord(p, " \t,;");
	else
	{
		while (plugName.getWord(p, " \t,;"))
		{
			if (plugName == name)
				break;
		}
	}
	if (!plugName.hasData())
	{
		(Arg::Gds(isc_random) << "Missing requested management plugin").raise();
	}

	// Search for it in cache of already loaded plugins
	for (unsigned i = 0; i < managers.getCount(); ++i)
	{
		if (plugName == managers[i].first.c_str())
			return managers[i].second;
	}

	// We have new user manager plugin
	Auth::Get getPlugin(att->att_database->dbb_config, plugName.c_str());
	return registerManager(getPlugin, plugName.c_str());
}

void UserManagement::openAllManagers()
{
	NoCaseString plugName;
	NoCaseString p(plugins);
	while (plugName.getWord(p, " \t,;"))
	{
		// Search for it in cache of already loaded plugins
		bool flag = false;
		for (unsigned i = 0; i < managers.getCount(); ++i)
		{
			if (plugName == managers[i].first.c_str())
			{
				flag = true;
				break;
			}
		}
		if (flag)
			continue;

		Auth::Get getPlugin(att->att_database->dbb_config, plugName.c_str());
		registerManager(getPlugin, plugName.c_str());
	}
}

UserManagement::~UserManagement()
{
	for (ULONG i = 0; i < commands.getCount(); ++i)
	{
		delete commands[i];
	}
	commands.clear();

	for (unsigned i = 0; i < managers.getCount(); ++i)
	{
		IManagement* manager = managers[i].second;
		if (manager)
		{
			LocalStatus status;
			CheckStatusWrapper statusWrapper(&status);

			manager->rollback(&statusWrapper);
			PluginManagerInterfacePtr()->releasePlugin(manager);
			managers[i].second = NULL;

			/***
			if (status.getState() & IStatus::STATE_ERRORS)
				status_exception::raise(&status);
			***/
		}
	}
}

void UserManagement::commit()
{
	for (unsigned i = 0; i < managers.getCount(); ++i)
	{
		IManagement* manager = managers[i].second;
		if (manager)
		{
			LocalStatus status;
			CheckStatusWrapper statusWrapper(&status);

			manager->commit(&statusWrapper);
			if (status.getState() & IStatus::STATE_ERRORS)
				status_exception::raise(&statusWrapper);

			PluginManagerInterfacePtr()->releasePlugin(manager);
			managers[i].second = NULL;
		}
	}
}

USHORT UserManagement::put(Auth::DynamicUserData* userData)
{
	const FB_SIZE_T ret = commands.getCount();
	if (ret > MAX_USHORT)
	{
		status_exception::raise(Arg::Gds(isc_random) << "Too many user management DDL per transaction)");
	}
	commands.push(userData);
	return ret;
}

void UserManagement::checkSecurityResult(int errcode, IStatus* status,
	const char* userName, IUser* user)
{
	if (!errcode)
	{
	    return;
	}
	errcode = Auth::setGsecCode(errcode, user);

	Arg::StatusVector tmp;
	tmp << Arg::Gds(ENCODE_ISC_MSG(errcode, GSEC_MSG_FAC));
	if (errcode == GsecMsg22)
	{
		tmp << userName;
	}
	tmp.append(Arg::StatusVector(status));

	tmp.raise();
}

static inline void merge(string& s, ConfigFile::Parameters::const_iterator& p)
{
	if (p->value.hasData())
	{
		string attr;
		attr.printf("%s=%s\n", p->name.c_str(), p->value.c_str());
		s += attr;
	}
}

void UserManagement::execute(USHORT id)
{
	if (id >= commands.getCount())
	{
		status_exception::raise(Arg::Gds(isc_random) << "Wrong job id passed to UserManagement::execute()");
	}

	if (!commands[id])
		return;	// Already executed

	Auth::UserData* command = commands[id];
	IManagement* manager = getManager(command->plugin.c_str());

	if (!manager)
		return;	// Already commited

	LocalStatus status;
	CheckStatusWrapper statusWrapper(&status);

	if (command->attr.entered() || command->op == Auth::ADDMOD_OPER)
	{
		Auth::StackUserData cmd;
		cmd.op = Auth::DIS_OPER;
		cmd.user.set(&statusWrapper, command->userName()->get());
		check(&statusWrapper);
		cmd.user.setEntered(&statusWrapper, 1);
		check(&statusWrapper);

		OldAttributes oldAttributes;
		int ret = manager->execute(&statusWrapper, &cmd, &oldAttributes);
		checkSecurityResult(ret, &status, command->userName()->get(), command);

		if (command->op == Auth::ADDMOD_OPER)
		{
			command->op = oldAttributes.present ? Auth::MOD_OPER : Auth::ADD_OPER;
		}

		if (command->attr.entered())
		{
			ConfigFile ocf(ConfigFile::USE_TEXT, oldAttributes.value.c_str(), ConfigFile::NO_COMMENTS);
			ConfigFile::Parameters::const_iterator old(ocf.getParameters().begin());
			ConfigFile::Parameters::const_iterator oldEnd(ocf.getParameters().end());

			ConfigFile ccf(ConfigFile::USE_TEXT, command->attr.get(), ConfigFile::NO_COMMENTS);
			ConfigFile::Parameters::const_iterator cur(ccf.getParameters().begin());
			ConfigFile::Parameters::const_iterator curEnd(ccf.getParameters().end());

			// Dup check
			ConfigFile::KeyType prev;
			while (cur != curEnd)
			{
				if (cur->name == prev)
				{
					(Arg::Gds(isc_dup_attribute) << cur->name).raise();
				}
				prev = cur->name;
				++cur;
			}
			cur = ccf.getParameters().begin();

			string merged;
			while (old != oldEnd && cur != curEnd)
			{
				if (old->name == cur->name)
				{
					merge(merged, cur);
					++old;
					++cur;
				}
				else if (old->name < cur->name)
				{
					merge(merged, old);
					++old;
				}
				else
				{
					merge(merged, cur);
					++cur;
				}
			}

			while (cur != curEnd)
			{
				merge(merged, cur);
				++cur;
			}

			while (old != oldEnd)
			{
				merge(merged, old);
				++old;
			}

			if (merged.hasData())
			{
				command->attr.set(&statusWrapper, merged.c_str());
				check(&statusWrapper);
			}
			else
			{
				command->attr.setEntered(&statusWrapper, 0);
				check(&statusWrapper);
				command->attr.setSpecified(1);
				command->attr.set(&statusWrapper, "");
				check(&statusWrapper);
			}
		}
	}

	if (command->op == Auth::ADD_OPER)
	{
		if (!command->act.entered())
		{
			command->act.set(&statusWrapper, 1);
			check(&statusWrapper);
			command->act.setEntered(&statusWrapper, 1);
			check(&statusWrapper);
		}
	}

	int errcode = manager->execute(&statusWrapper, command, NULL);
	checkSecurityResult(errcode, &status, command->userName()->get(), command);

	delete commands[id];
	commands[id] = NULL;
}

void UserManagement::list(IUser* u, unsigned cachePosition)
{
	RecordBuffer* buffer = getData(rel_sec_users);
	Record* record = buffer->getTempRecord();
	record->nullify();

	int charset = CS_METADATA;

	const MetaName& plugName(managers[cachePosition].first);
	putField(threadDbb, record,
			 DumpField(f_sec_plugin, VALUE_STRING, static_cast<USHORT>(plugName.length()), plugName.c_str()),
			 charset);

	if (u->userName()->entered())
	{
		putField(threadDbb, record,
				 DumpField(f_sec_user_name, VALUE_STRING, static_cast<USHORT>(strlen(u->userName()->get())), u->userName()->get()),
				 charset);
	}

	if (u->firstName()->entered())
	{
		putField(threadDbb, record,
				 DumpField(f_sec_first_name, VALUE_STRING, static_cast<USHORT>(strlen(u->firstName()->get())), u->firstName()->get()),
				 charset);
	}

	if (u->middleName()->entered())
	{
		putField(threadDbb, record,
				 DumpField(f_sec_middle_name, VALUE_STRING, static_cast<USHORT>(strlen(u->middleName()->get())), u->middleName()->get()),
				 charset);
	}

	if (u->lastName()->entered())
	{
		putField(threadDbb, record,
				 DumpField(f_sec_last_name, VALUE_STRING, static_cast<USHORT>(strlen(u->lastName()->get())), u->lastName()->get()),
				 charset);
	}

	if (u->active()->entered())
	{
		UCHAR v = u->active()->get() ? '\1' : '\0';
		putField(threadDbb, record,
				 DumpField(f_sec_active, VALUE_BOOLEAN, sizeof(v), &v),
				 charset);
	}

	if (u->admin()->entered())
	{
		UCHAR v = u->admin()->get() ? '\1' : '\0';
		putField(threadDbb, record,
				 DumpField(f_sec_admin, VALUE_BOOLEAN, sizeof(v), &v),
				 charset);
	}

	if (u->comment()->entered())
	{
		putField(threadDbb, record,
				 DumpField(f_sec_comment, VALUE_STRING, static_cast<USHORT>(strlen(u->comment()->get())), u->comment()->get()),
				 charset);
	}

	buffer->store(record);

	if (u->userName()->entered() && u->attributes()->entered())
	{
		buffer = getData(rel_sec_user_attributes);

		ConfigFile cf(ConfigFile::USE_TEXT, u->attributes()->get(), ConfigFile::NO_COMMENTS);
		ConfigFile::Parameters::const_iterator e(cf.getParameters().end());
		for (ConfigFile::Parameters::const_iterator b(cf.getParameters().begin()); b != e; ++b)
		{
			record = buffer->getTempRecord();
			record->nullify();

			putField(threadDbb, record,
					 DumpField(f_sec_attr_user, VALUE_STRING, static_cast<USHORT>(strlen(u->userName()->get())), u->userName()->get()),
					 charset);

			putField(threadDbb, record,
					 DumpField(f_sec_attr_key, VALUE_STRING, b->name.length(), b->name.c_str()),
					 charset);

			putField(threadDbb, record,
					 DumpField(f_sec_attr_value, VALUE_STRING, b->value.length(), b->value.c_str()),
					 charset);

			buffer->store(record);
		}
	}
}

RecordBuffer* UserManagement::getList(thread_db* tdbb, jrd_rel* relation)
{
	fb_assert(relation);
	fb_assert(relation->rel_id == rel_sec_user_attributes || relation->rel_id == rel_sec_users);

	RecordBuffer* recordBuffer = getData(relation);
	if (recordBuffer)
	{
		return recordBuffer;
	}

	try
	{
		openAllManagers();

		threadDbb = tdbb;
		MemoryPool* const pool = threadDbb->getTransaction()->tra_pool;
		allocBuffer(threadDbb, *pool, rel_sec_users);
		allocBuffer(threadDbb, *pool, rel_sec_user_attributes);

		for (FillSnapshot fillSnapshot(this); fillSnapshot.pos < managers.getCount(); ++fillSnapshot.pos)
		{
			LocalStatus status;
			CheckStatusWrapper statusWrapper(&status);

			Auth::StackUserData u;
			u.op = Auth::DIS_OPER;

			int errcode = managers[fillSnapshot.pos].second->execute(&statusWrapper, &u, &fillSnapshot);
			checkSecurityResult(errcode, &status, "Unknown", &u);
		}
	}
	catch (const Exception&)
	{
		clearSnapshot();
		throw;
	}

	return getData(relation);
}
