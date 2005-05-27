/*
 *	PROGRAM:	JRD International support
 *	MODULE:		unicode_util.h
 *	DESCRIPTION:	Unicode functions
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
 *  The Original Code was created by Adriano dos Santos Fernandes
 *  for the Firebird Open Source RDBMS project.
 *
 *  Copyright (c) 2004 Adriano dos Santos Fernandes <adrianosf@uol.com.br>
 *  and all contributors signed below.
 *
 *  All Rights Reserved.
 *  Contributor(s): ______________________________________.
 */

#ifndef JRD_UNICODE_UTIL_H
#define JRD_UNICODE_UTIL_H

#include "intlobj_new.h"

namespace Jrd {

class UnicodeUtil
{
public:
	// routines equivalent with intlobj_new.h

	static USHORT utf16KeyLength(USHORT len);	// BOCU-1
	static USHORT utf16ToKey(USHORT srcLen, const USHORT* src, USHORT dstLen, UCHAR* dst,
							 USHORT key_type);	// BOCU-1
	static ULONG utf16LowerCase(ULONG srcLen, const USHORT* src, ULONG dstLen, USHORT* dst);
	static ULONG utf16UpperCase(ULONG srcLen, const USHORT* src, ULONG dstLen, USHORT* dst);
	static ULONG utf16ToUtf8(ULONG srcLen, const USHORT* src, ULONG dstLen, UCHAR* dst,
							 USHORT* err_code, ULONG* err_position);
	static ULONG utf8ToUtf16(ULONG srcLen, const UCHAR* src, ULONG dstLen, USHORT* dst,
							 USHORT* err_code, ULONG* err_position);
	static ULONG utf16ToUtf32(ULONG srcLen, const USHORT* src, ULONG dstLen, ULONG* dst,
							  USHORT* err_code, ULONG* err_position);
	static ULONG utf32ToUtf16(ULONG srcLen, const ULONG* src, ULONG dstLen, USHORT* dst,
							  USHORT* err_code, ULONG* err_position);
	static SSHORT utf16Compare(ULONG len1, const USHORT* str1, ULONG len2, const USHORT* str2,
							   INTL_BOOL* error_flag);

	static ULONG utf16Length(ULONG len, const USHORT* str);
	static ULONG utf16Substring(ULONG srcLen, const USHORT* src, ULONG dstLen, USHORT* dst, 
								ULONG startPos, ULONG length);
	static INTL_BOOL utf8WellFormed(ULONG len, const UCHAR* str, ULONG* offending_position);
	static INTL_BOOL utf16WellFormed(ULONG len, const USHORT* str, ULONG* offending_position);
	static INTL_BOOL utf32WellFormed(ULONG len, const ULONG* str, ULONG* offending_position);

	class Utf16Collation
	{
	public:
		static Utf16Collation* create(const char* locale);

		~Utf16Collation();

		USHORT keyLength(USHORT len);
		USHORT stringToKey(USHORT srcLen, const USHORT* src, USHORT dstLen, UCHAR* dst,
						   USHORT key_type);
		SSHORT compare(ULONG len1, const USHORT* str1, ULONG len2, const USHORT* str2,
					   INTL_BOOL* error_flag);

	private:
		void* collator;
	};
};

}	// namespace Jrd

#endif	// JRD_UNICODE_UTIL_H
