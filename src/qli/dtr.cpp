/*
 *	PROGRAM:	JRD Command Oriented Query Language
 *	MODULE:		dtr.cpp
 *	DESCRIPTION:	Top level driving module
 *                         
 * The contents of this file are subject to the Interbase Public
 * License Version 1.0 (the "License"); you may not use this file
 * except in compliance with the License. You may obtain a copy
 * of the License at http://www.Inprise.com/IPL.html
 *
 * Software distributed under the License is distributed on an
 * "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, either express
 * or implied. See the License for the specific language governing
 * rights and limitations under the License.
 *
 * The Original Code was created by Inprise Corporation
 * and its predecessors. Portions created by Inprise Corporation are
 * Copyright (C) Inprise Corporation.
 *
 * All Rights Reserved.
 * Contributor(s): ______________________________________.
 *
 * 2002.10.30 Sean Leyne - Removed support for obsolete "PC_PLATFORM" define
 *
 */

#include "firebird.h"

#define QLI_MAIN

#include "../jrd/ib_stdio.h"
#include <setjmp.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include "../qli/dtr.h"
#include "../qli/parse.h"
#include "../qli/compile.h"
#include "../jrd/perf.h"
#include "../jrd/license.h"
#include "../jrd/y_ref.h"
#include "../jrd/ibase.h"
#include "../qli/exe.h"
#include "../qli/all_proto.h"
#include "../qli/compi_proto.h"
#include "../qli/err_proto.h"
#include "../qli/exe_proto.h"
#include "../qli/expan_proto.h"
#include "../qli/gener_proto.h"
#include "../qli/help_proto.h"
#include "../qli/lex_proto.h"
#include "../qli/meta_proto.h"
#include "../qli/parse_proto.h"
#include "../jrd/gds_proto.h"
#include "../jrd/perf_proto.h"
#include "../include/fb_exception.h"

#ifdef VMS
#define STARTUP_FILE	"QLI_STARTUP"
#endif

#ifndef STARTUP_FILE
#define STARTUP_FILE    "HOME"	// Assume its Unix 
#endif

#ifndef SIGQUIT
#define SIGQUIT		SIGINT
#define SIGPIPE		SIGINT
#endif

// Program wide globals 

jmp_buf QLI_env;					// Error return environment 

TEXT *QLI_error;
bool sw_verify;
bool sw_trace;
USHORT sw_buffers;
USHORT QLI_lines = 60, QLI_prompt_count, QLI_reprompt, QLI_name_columns = 0;

// Let's define the default number of columns on a machine by machine basis 

#ifdef VMS
USHORT QLI_columns = 80;
#else
USHORT QLI_columns = 80;
#endif

extern TEXT *QLI_prompt;

static void enable_signals(void);
static bool process_statement(bool);
static void CLIB_ROUTINE signal_arith_excp(USHORT, USHORT, USHORT);
static void CLIB_ROUTINE signal_quit(void);
static bool yes_no(USHORT, const TEXT*);

struct answer_t {
	TEXT answer[30];
	bool value;
};

static int yes_no_loaded = 0;
static answer_t answer_table[] =
{
	{ "NO", false },					// NO   
	{ "YES", true },					// YES  
	{ "", false }
};


int  CLIB_ROUTINE main( int argc, char **argv)
{
/**************************************
 *
 *	m a i n
 *
 **************************************
 *
 * Functional description
 *	Top level routine.  
 *
 **************************************/
	jmp_buf env;

// Look at options, if any 

	const TEXT* startup_file = STARTUP_FILE;

#ifdef UNIX
// If a Unix system, get home directory from environment 
	SCHAR home_directory[256];
	startup_file = getenv("HOME");
	if (startup_file == NULL) {
		startup_file = ".qli_startup";
	}
	else {
		strcpy(home_directory, startup_file);
		strcat(home_directory, "/.qli_startup");
		startup_file = home_directory;
	}
#endif

	TEXT* application_file = NULL;
	ALLQ_init();
	LEX_init();
	bool version_flag = false, flush_flag = false;
	bool banner_flag = true;
	sw_buffers = 0;
	strcpy(QLI_prompt_string, "QLI> ");
	strcpy(QLI_cont_string, "CON> ");
	QLI_prompt = QLI_prompt_string;
	QLI_matching_language = 0;
	QLI_default_user[0] = 0;
	QLI_default_password[0] = 0;
	QLI_charset[0] = 0;

#ifdef DEV_BUILD
	QLI_hex_output = false;
#endif

#ifdef VMS
	argc = VMS_parse(&argv, argc);
#endif

	SLONG debug_value; // aparently unneeded, see usage below.

	const TEXT* const* const arg_end = argv + argc;
	argv++;
	while (argv < arg_end) {
		const TEXT* p = *argv++;
		if (*p++ != '-') {
			banner_flag = false;
			LEX_pop_line();
			LEX_push_string(p - 1);
			continue;
		}
		TEXT c;
		while (c = *p++)
			switch (UPPER(c)) {
			case 'A':
				if (argv >= arg_end) {
					ERRQ_msg_put(23, NULL, NULL, NULL, NULL, NULL);	// Msg23 Please retry, supplying an application script file name  
					exit(FINI_ERROR);
				}

				application_file = *argv++;
				break;

			case 'B':
				if (argv < arg_end && **argv != '-')
					sw_buffers = atoi(*argv++);
				break;

			case 'I':
				if (argv >= arg_end || **argv == '-')
					startup_file = NULL;
				else
					startup_file = *argv++;
				break;

			case 'N':
				banner_flag = false;
				break;

			case 'P':
				{
					if (argv >= arg_end || **argv == '-')
						break;
					TEXT* r = QLI_default_password;
					const TEXT* const end = r + sizeof(QLI_default_password) - 1;
					for (const TEXT* q = *argv++; *q && r < end;)
						*r++ = *q++;
					*r = 0;
					break;
				}

			case 'T':
				sw_trace = true;
				break;

			case 'U':
				{
					if (argv >= arg_end || **argv == '-')
						break;
					TEXT* r = QLI_default_user;
					const TEXT* const end = r + sizeof(QLI_default_user) - 1;
					for (const TEXT* q = *argv++; *q && r < end;)
						*r++ = *q++;
					*r = 0;
					break;
				}

			case 'V':
				sw_verify = true;
				break;

			case 'X':
				debug_value = 1;
				isc_set_debug(debug_value);
				break;

				/* This switch's name is arbitrary; since it is an internal 
				   mechanism it can be changed at will */

			case 'Y':
				QLI_trace = true;
				break;

			case 'Z':
				version_flag = true;
				break;

			default:
				ERRQ_msg_put(469, (TEXT *)(IPTR) c, NULL, NULL, NULL, NULL);	// Msg469 qli: ignoring unknown switch %c 
				break;
			}
	}

	enable_signals();

	if (banner_flag)
		ERRQ_msg_put(24, NULL, NULL, NULL, NULL, NULL);	// Msg24 Welcome to QLI Query Language Interpreter 

	if (version_flag)
		ERRQ_msg_put(25, GDS_VERSION, NULL, NULL, NULL, NULL);	// Msg25 qli version %s 

	if (application_file)
		LEX_push_file(application_file, true);

	if (startup_file)
		LEX_push_file(startup_file, false);

#ifdef VMS
	bool vms_tryagain_flag = false;
	if (startup_file)
		vms_tryagain_flag = LEX_push_file(startup_file, false);

/* If default value of startup file wasn't altered by the use of -i,
   and LEX returned FALSE (above), try the old logical name, QLI_INIT */

	if (!vms_tryagain_flag && startup_file
		&& !(strcmp(startup_file, STARTUP_FILE)))
	{
		LEX_push_file("QLI_INIT", false);
	}
#endif

	for (bool got_started = false; !got_started;)
	{
		got_started = true;
		try {
			memcpy(QLI_env, env, sizeof(QLI_env));
			PAR_token();
		}
		catch (const std::exception&) {
			// try again 
			got_started = false;
			ERRQ_pending();
		}
	}
	memset(QLI_env, 0, sizeof(QLI_env));
	QLI_error = NULL;

// Loop until end of file or forced exit 

	while (QLI_line) {
		plb* temp = QLI_default_pool = ALLQ_pool();
		flush_flag = process_statement(flush_flag);
		ERRQ_pending();
		ALLQ_rlpool(temp);
	}
	HELP_fini();
	MET_shutdown();
	LEX_fini();
	ALLQ_fini();
#ifdef DEBUG_GDS_ALLOC
/* Report any memory leaks noticed.  
 * We don't particularly care about QLI specific memory leaks, so all
 * QLI allocations have been marked as "don't report".  However, much
 * of the test-base uses QLI so having a report when QLI finishes
 * could find leaks within the engine.
 */
	gds_alloc_report(0, __FILE__, __LINE__);
#endif
	return (FINI_OK);
}


static void enable_signals(void)
{
/**************************************
 *
 *	e n a b l e _ s i g n a l s
 *
 **************************************
 *
 * Functional description
 *	Enable signals.
 *
 **************************************/
	typedef void (*new_handler) (int);

	signal(SIGQUIT, (new_handler) signal_quit);
	signal(SIGINT, (new_handler) signal_quit);
	signal(SIGPIPE, (new_handler) signal_quit);
	signal(SIGFPE, (new_handler) signal_arith_excp);
}


static bool process_statement(bool flush_flag)
{
/**************************************
 *
 *	p r o c e s s _ s t a t e m e n t
 *
 **************************************
 *
 * Functional description
 *	Parse, compile, and execute a single statement.  If an input flush
 *	is required, return true (or status), otherwise return false.
 *
 **************************************/
	DBB dbb;
	jmp_buf env;

// Clear database active flags in preparation for a new statement 

	QLI_abort = false;
	blk* execution_tree = NULL;

	for (dbb = QLI_databases; dbb; dbb = dbb->dbb_next)
		dbb->dbb_flags &= ~DBB_active;

// If the last statement wrote out anything to the terminal, skip a line 

	if (QLI_skip_line) {
		ib_printf("\n");
		QLI_skip_line = false;
	}

/* Enable signal handling for the next statement.  Each signal will
   be caught at least once, then reset to allow the user to really
   kill the process */

	enable_signals();

// Enable error unwinding and enable the unwinding environment 

	try {

	memcpy(QLI_env, env, sizeof(QLI_env));

/* Set up the appropriate prompt and get the first significant token.  If
   we don't get one, we're at end of file */

	QLI_prompt = QLI_prompt_string;

/* This needs to be done after setting QLI_prompt to prevent
 * and infinite loop in LEX/next_line.
 */
// If there was a prior syntax error, flush the token stream 

	if (flush_flag)
		LEX_flush();

	while (QLI_token->tok_keyword == KW_SEMI)
		LEX_token();

	PAR_real();

	if (!QLI_line)
		return false;

	EXEC_poll_abort();

/* Mark the current token as starting the statement.  This is allows
   the EDIT command to find the last statement */

	LEX_mark_statement();

/* Change the prompt string to the continuation prompt, and parse
   the next statement */

	QLI_prompt = QLI_cont_string;

	qli_syntax* syntax_tree = PARQ_parse();
	if (!syntax_tree)
		return false;

	EXEC_poll_abort();

// If the statement was EXIT, force end of file on command input 

	if (syntax_tree->syn_type == nod_exit) {
		QLI_line = NULL;
		return false;
	}

// If the statement was quit, ask the user if he want to rollback 

	if (syntax_tree->syn_type == nod_quit) {
		QLI_line = NULL;
		for (dbb = QLI_databases; dbb; dbb = dbb->dbb_next)
			if ((dbb->dbb_transaction) && (dbb->dbb_flags & DBB_updates))
				if (yes_no(460, dbb->dbb_symbol->sym_string))	/* Msg460 Do you want to rollback updates for <dbb>? */
					MET_transaction(nod_rollback, dbb);
				else
					MET_transaction(nod_commit, dbb);
		return false;
	}

/* Expand the statement.  It will return NULL is the statement was
   a command.  An error will be unwound */

	blk* expanded_tree = (BLK) EXP_expand(syntax_tree);
	if (!expanded_tree)
		return false;

// Compile the statement 

	if (!(execution_tree = (BLK) CMPQ_compile((qli_nod*) expanded_tree)))
		return false;

// Generate any BLR needed to support the request 

	if (!GEN_generate(( (qli_nod*) execution_tree)))
		return false;

	if (QLI_statistics)
		for (dbb = QLI_databases; dbb; dbb = dbb->dbb_next)
			if (dbb->dbb_flags & DBB_active) {
				if (!dbb->dbb_statistics) {
					dbb->dbb_statistics =
						(int *) gds__alloc((SLONG) sizeof(PERF));
#ifdef DEBUG_GDS_ALLOC
					// We don't care about QLI specific memory leaks for V4.0 
					gds_alloc_flag_unfreed((void *) dbb->dbb_statistics);	// QLI: don't care 
#endif
				}
				perf_get_info(&dbb->dbb_handle, (perf *)dbb->dbb_statistics);
			}

// Execute the request, for better or worse 

	EXEC_top((qli_nod*) execution_tree);

	if (QLI_statistics)
	{
		PERF statistics;
		TEXT buffer[512], report[256];
		for (dbb = QLI_databases; dbb; dbb = dbb->dbb_next)
		{
			if (dbb->dbb_flags & DBB_active)
			{
				ERRQ_msg_get(505, report);
				// Msg505 "    reads = !r writes = !w fetches = !f marks = !m\n" 
				ERRQ_msg_get(506, report + strlen(report));
				// Msg506 "    elapsed = !e cpu = !u system = !s mem = !x, buffers = !b" 
				perf_get_info(&dbb->dbb_handle, &statistics);
				perf_format((perf*) dbb->dbb_statistics, &statistics,
							report, buffer, 0);
				ERRQ_msg_put(26, dbb->dbb_filename, buffer, NULL, NULL, NULL);	// Msg26 Statistics for database %s %s  
				QLI_skip_line = true;
			}
		}
	}

// Release resources associated with the request 

	GEN_release();

	return false;

	}	// try
	catch (const Firebird::status_exception& e) {
		GEN_release();
		return e.value();
	}
}


static void CLIB_ROUTINE signal_arith_excp(USHORT sig, USHORT code, USHORT scp)
{
/**************************************
 *
 *	s i g n a l _ a r i t h _ e x c p
 *
 **************************************
 *
 * Functional description
 *	Catch arithmetic exception.
 *
 **************************************/
	USHORT msg_number;

#if defined(FPE_INOVF_TRAP) || defined(FPE_INTDIV_TRAP) \
	|| defined(FPE_FLTOVF_TRAP) || defined(FPE_FLTDIV_TRAP) \
	|| defined(FPE_FLTUND_TRAP) || defined(FPE_FLTOVF_FAULT) \
	|| defined(FPE_FLTUND_FAULT)

	switch (code) {
#ifdef FPE_INOVF_TRAP
	case FPE_INTOVF_TRAP:
		msg_number = 14;		// Msg14 integer overflow 
		break;
#endif

#ifdef FPE_INTDIV_TRAP
	case FPE_INTDIV_TRAP:
		msg_number = 15;		// Msg15 integer division by zero 
		break;
#endif

#ifdef FPE_FLTOVF_TRAP
	case FPE_FLTOVF_TRAP:
		msg_number = 16;		// Msg16 floating overflow trap 
		break;
#endif

#ifdef FPE_FLTDIV_TRAP
	case FPE_FLTDIV_TRAP:
		msg_number = 17;		// Msg17 floating division by zero 
		break;
#endif

#ifdef FPE_FLTUND_TRAP
	case FPE_FLTUND_TRAP:
		msg_number = 18;		// Msg18 floating underflow trap 
		break;
#endif

#ifdef FPE_FLTOVF_FAULT
	case FPE_FLTOVF_FAULT:
		msg_number = 19;		// Msg19 floating overflow fault 
		break;
#endif

#ifdef FPE_FLTUND_FAULT
	case FPE_FLTUND_FAULT:
		msg_number = 20;		// Msg20 floating underflow fault 
		break;
#endif

	default:
		msg_number = 21;		// Msg21 arithmetic exception 
	}
#else
	msg_number = 21;
#endif

	signal(SIGFPE, (void(*)(int)) signal_arith_excp);

	IBERROR(msg_number);
}


static void CLIB_ROUTINE signal_quit(void)
{
/**************************************
 *
 *	s i g n a l _ q u i t
 *
 **************************************
 *
 * Functional description
 *	Stop whatever we happened to be doing.
 *
 **************************************/
	//void (*prev_handler) ();

	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);

	EXEC_abort();
}


static bool yes_no(USHORT number, const TEXT* arg1)
{
/**************************************
 *
 *	y e s _ n o
 *
 **************************************
 *
 * Functional description
 *	Put out a prompt that expects a yes/no
 *	answer, and keep trying until we get an
 *	acceptable answer (e.g. y, Yes, N, etc.)
 *
 **************************************/
	TEXT prompt[256];

	ERRQ_msg_format(number, sizeof(prompt), prompt, arg1, NULL, NULL, NULL,
					NULL);
	if (!yes_no_loaded) {
		yes_no_loaded = 1;
		if (!ERRQ_msg_get(498, answer_table[0].answer))	// Msg498 NO    
			strcpy(answer_table[0].answer, "NO");	// default if msg_get fails 
		if (!ERRQ_msg_get(497, answer_table[1].answer))	// Msg497 YES   
			strcpy(answer_table[1].answer, "YES");
	}

	TEXT buffer[256];
	while (true) {
		buffer[0] = 0;
		if (!LEX_get_line(prompt, buffer, sizeof(buffer)))
			return true;
		for (answer_t* response = answer_table; *response->answer != '\0';
			response++)
		{
			const TEXT* p = buffer;
			while (*p == ' ')
				p++;
			if (*p == EOF)
				return true;
			for (const TEXT* q = response->answer; *p && UPPER(*p) == *q++; p++);
			if (!*p || *p == '\n')
				return response->value;
		}
	}
}

