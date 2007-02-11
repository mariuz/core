/*
 *	PROGRAM:	JRD Access Method
 *	MODULE:		intlnames.h
 *	DESCRIPTION:	International objects for metadata initialization
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
 */

/*
 *	CHARSET
 *	Binding's of symbols to character set ids.
 *	With implementation ID of default collation
 * 	CHARSET (name, ID, default_subtype, max_bytes_per_char, num_chars,
 *           cs_symbol, coll_symbol, coll_attributes)
 *
 *	Note: "name" is official name per Firebird
 *
 */

/*
 *	CSALIAS
 *	Alternate name for a character set (to account for platforms
 *	naming the same character set by alternate ways).
 *	CSALIAS	(name, ID)
 */

/*
 *	COLLATION
 *	Binding's of symbols to Collation ID's and Character
 *	set id's.
 *	Collation ID tells us the locale.
 *	Character Set ID tells us the character set.
 *
 *	COLLATION (name, country, charset_id, subtype_id, symbol, attributes)
 *
 *	Note: "name" is official name per Firebird
 */

#ifndef INTL_COMPONENT_FB

CHARSET("NONE", CS_NONE, 0, 1, 256, cs_none_init, dummy, TEXTTYPE_ATTR_PAD_SPACE)
END_CHARSET

CHARSET("OCTETS", CS_BINARY, 0, 1, 256, cs_binary_init, dummy, TEXTTYPE_ATTR_PAD_SPACE)
	CSALIAS("BINARY", CS_BINARY)
END_CHARSET

CHARSET("ASCII", CS_ASCII, 0, 1, 256, cs_ascii_init, dummy, TEXTTYPE_ATTR_PAD_SPACE)
	CSALIAS("USASCII", CS_ASCII)
	CSALIAS("ASCII7", CS_ASCII)
END_CHARSET

/* V3 SUB_TYPE 201 */
CHARSET("UNICODE_FSS", CS_UNICODE_FSS, 0, 3, 256 * 256, cs_unicode_fss_init,
		dummy, TEXTTYPE_ATTR_PAD_SPACE)
	CSALIAS("UTF_FSS", CS_UNICODE_FSS)
	CSALIAS("SQL_TEXT", CS_UNICODE_FSS)
END_CHARSET

CHARSET("UTF8", CS_UTF8, 0, 4, 256 * 256, cs_utf8_init, dummy, TEXTTYPE_ATTR_PAD_SPACE)
	CSALIAS("UTF-8", CS_UTF8)
	COLLATION("UCS_BASIC", NULL, CC_INTL, CS_UTF8, 1, NULL, TEXTTYPE_ATTR_PAD_SPACE)
	COLLATION("UNICODE", NULL, CC_INTL, CS_UTF8, 2, NULL, TEXTTYPE_ATTR_PAD_SPACE)
	COLLATION("UNICODE_CI", "UNICODE", CC_INTL, CS_UTF8, 3, NULL, TEXTTYPE_ATTR_PAD_SPACE | TEXTTYPE_ATTR_CASE_INSENSITIVE)
END_CHARSET

#ifdef FB_NEW_INTL_ALLOW_NOT_READY
CHARSET("UTF16", CS_UTF16, 0, 4, 256 * 256, cs_utf16_init, dummy, TEXTTYPE_ATTR_PAD_SPACE)
    CSALIAS("UTF-16", CS_UTF16)
	COLLATION("UCS_BASIC", NULL, CC_INTL, CS_UTF16, 1, NULL, TEXTTYPE_ATTR_PAD_SPACE)
END_CHARSET

CHARSET("UTF32", CS_UTF32, 0, 4, 256 * 256, cs_utf32_init, dummy, TEXTTYPE_ATTR_PAD_SPACE)
    CSALIAS("UTF-32", CS_UTF32)
	COLLATION("UCS_BASIC", NULL, CC_INTL, CS_UTF32, 1, NULL, TEXTTYPE_ATTR_PAD_SPACE)
END_CHARSET
#endif	// FB_NEW_INTL_NOT_READY

#endif	// INTL_COMPONENT_FB

/* V3 SUB_TYPE 220 */
CHARSET("SJIS_0208", CS_SJIS, 0, 2, 7007, CS_sjis, JIS220_init, TEXTTYPE_ATTR_PAD_SPACE)
	CSALIAS("SJIS", CS_SJIS)
END_CHARSET

/* V3 SUB_TYPE 230 */
CHARSET("EUCJ_0208", CS_EUCJ, 0, 2, 7007, CS_euc_j, JIS230_init, TEXTTYPE_ATTR_PAD_SPACE)
	CSALIAS("EUCJ", CS_EUCJ)
END_CHARSET

CHARSET("DOS437", CS_DOS_437, 0, 1, 256, CS_dos_437, DOS101_init, TEXTTYPE_ATTR_PAD_SPACE)
	CSALIAS("DOS_437", CS_DOS_437)
	/* V3 SUB_TYPE 101 */
	COLLATION("PDOX_ASCII", NULL, CC_ASCII, CS_DOS_437, 1, DOS101_init, TEXTTYPE_ATTR_PAD_SPACE)
	/* V3 SUB_TYPE 102 */
	COLLATION("PDOX_INTL", NULL, CC_INTL, CS_DOS_437, 2, DOS102_init, TEXTTYPE_ATTR_PAD_SPACE)
	/* V3 SUB_TYPE 106 */
	COLLATION("PDOX_SWEDFIN", NULL, CC_SWEDFIN, CS_DOS_437, 3, DOS106_init, TEXTTYPE_ATTR_PAD_SPACE)
	COLLATION("DB_DEU437", NULL, CC_GERMANY, CS_DOS_437, 4, DOS101_c2_init, TEXTTYPE_ATTR_PAD_SPACE)
	COLLATION("DB_ESP437", NULL, CC_SPAIN, CS_DOS_437, 5, DOS101_c3_init, TEXTTYPE_ATTR_PAD_SPACE)
	COLLATION("DB_FIN437", NULL, CC_FINLAND, CS_DOS_437, 6, DOS101_c4_init, TEXTTYPE_ATTR_PAD_SPACE)
	COLLATION("DB_FRA437", NULL, CC_FRANCE, CS_DOS_437, 7, DOS101_c5_init, TEXTTYPE_ATTR_PAD_SPACE)
	COLLATION("DB_ITA437", NULL, CC_ITALY, CS_DOS_437, 8, DOS101_c6_init, TEXTTYPE_ATTR_PAD_SPACE)
	COLLATION("DB_NLD437", NULL, CC_NEDERLANDS, CS_DOS_437, 9, DOS101_c7_init, TEXTTYPE_ATTR_PAD_SPACE)
	COLLATION("DB_SVE437", NULL, CC_SWEDEN, CS_DOS_437, 10, DOS101_c8_init, TEXTTYPE_ATTR_PAD_SPACE)
	COLLATION("DB_UK437", NULL, CC_UK, CS_DOS_437, 11, DOS101_c9_init, TEXTTYPE_ATTR_PAD_SPACE)
	COLLATION("DB_US437", NULL, CC_US, CS_DOS_437, 12, DOS101_c10_init, TEXTTYPE_ATTR_PAD_SPACE)
END_CHARSET

/* V3 SUB_TYPE 160 */
CHARSET("DOS850", CS_DOS_850, 0, 1, 256, CS_dos_850, DOS160_init, TEXTTYPE_ATTR_PAD_SPACE)
	CSALIAS("DOS_850", CS_DOS_850)
	COLLATION("DB_FRC850", NULL, CC_FRENCHCAN, CS_DOS_850, 1, DOS160_c1_init, TEXTTYPE_ATTR_PAD_SPACE)
	COLLATION("DB_DEU850", NULL, CC_GERMANY, CS_DOS_850, 2, DOS160_c2_init, TEXTTYPE_ATTR_PAD_SPACE)
	COLLATION("DB_ESP850", NULL, CC_SPAIN, CS_DOS_850, 3, DOS160_c3_init, TEXTTYPE_ATTR_PAD_SPACE)
	COLLATION("DB_FRA850", NULL, CC_FRANCE, CS_DOS_850, 4, DOS160_c4_init, TEXTTYPE_ATTR_PAD_SPACE)
	COLLATION("DB_ITA850", NULL, CC_ITALY, CS_DOS_850, 5, DOS160_c5_init, TEXTTYPE_ATTR_PAD_SPACE)
	COLLATION("DB_NLD850", NULL, CC_NEDERLANDS, CS_DOS_850, 6, DOS160_c6_init, TEXTTYPE_ATTR_PAD_SPACE)
	COLLATION("DB_PTB850", NULL, CC_PORTUGAL, CS_DOS_850, 7, DOS160_c7_init, TEXTTYPE_ATTR_PAD_SPACE)
	COLLATION("DB_SVE850", NULL, CC_SWEDEN, CS_DOS_850, 8, DOS160_c8_init, TEXTTYPE_ATTR_PAD_SPACE)
	COLLATION("DB_UK850", NULL, CC_UK, CS_DOS_850, 9, DOS160_c9_init, TEXTTYPE_ATTR_PAD_SPACE)
	COLLATION("DB_US850", NULL, CC_US, CS_DOS_850, 10, DOS160_c10_init, TEXTTYPE_ATTR_PAD_SPACE)
END_CHARSET

/* V3 SUB_TYPE 107 */
CHARSET("DOS865", CS_DOS_865, 0, 1, 256, CS_dos_865, DOS107_init, TEXTTYPE_ATTR_PAD_SPACE)
	CSALIAS("DOS_865", CS_DOS_865)
	/* V3 SUB_TYPE 105 */
	COLLATION("PDOX_NORDAN4", NULL, CC_NORDAN, CS_DOS_865, 1, DOS107_c1_init, TEXTTYPE_ATTR_PAD_SPACE)
	COLLATION("DB_DAN865", NULL, CC_DENMARK, CS_DOS_865, 2, DOS107_c2_init, TEXTTYPE_ATTR_PAD_SPACE)
	COLLATION("DB_NOR865", NULL, CC_NORWAY, CS_DOS_865, 3, DOS107_c3_init, TEXTTYPE_ATTR_PAD_SPACE)
END_CHARSET

CHARSET("ISO8859_1", CS_ISO8859_1, 0, 1, 256, CS_iso_ISO8859_1, ISO88591_cp_init, TEXTTYPE_ATTR_PAD_SPACE)
	CSALIAS("ISO8859_1", CS_ISO8859_1)
	CSALIAS("ISO88591", CS_ISO8859_1)
	CSALIAS("LATIN1", CS_ISO8859_1)
	CSALIAS("ANSI", CS_ISO8859_1)
	/* V3 SUB_TYPE 139 */
	COLLATION("DA_DA", NULL, CC_DENMARK, CS_ISO8859_1, 1, ISO88591_39_init, TEXTTYPE_ATTR_PAD_SPACE)
	/* V3 SUB_TYPE 140 */
	COLLATION("DU_NL", NULL, CC_NEDERLANDS, CS_ISO8859_1, 2, ISO88591_40_init, TEXTTYPE_ATTR_PAD_SPACE)
	/* V3 SUB_TYPE 141 */
	COLLATION("FI_FI", NULL, CC_FINLAND, CS_ISO8859_1, 3, ISO88591_41_init, TEXTTYPE_ATTR_PAD_SPACE)
	/* V3 SUB_TYPE 142 */
	COLLATION("FR_FR", NULL, CC_FRANCE, CS_ISO8859_1, 4, ISO88591_42_init, TEXTTYPE_ATTR_PAD_SPACE)
	/* V3 SUB_TYPE 143 */
	COLLATION("FR_CA", NULL, CC_FRENCHCAN, CS_ISO8859_1, 5, ISO88591_43_init, TEXTTYPE_ATTR_PAD_SPACE)
	/* V3 SUB_TYPE 144 */
	COLLATION("DE_DE", NULL, CC_GERMANY, CS_ISO8859_1, 6, ISO88591_44_init, TEXTTYPE_ATTR_PAD_SPACE)
	/* V3 SUB_TYPE 145 */
	COLLATION("IS_IS", NULL, CC_ICELAND, CS_ISO8859_1, 7, ISO88591_45_init, TEXTTYPE_ATTR_PAD_SPACE)
	/* V3 SUB_TYPE 146 */
	COLLATION("IT_IT", NULL, CC_ITALY, CS_ISO8859_1, 8, ISO88591_46_init, TEXTTYPE_ATTR_PAD_SPACE)
	/* V3 SUB_TYPE 148 */
	COLLATION("NO_NO", NULL, CC_NORWAY, CS_ISO8859_1, 9, ISO88591_48_init, TEXTTYPE_ATTR_PAD_SPACE)
	/* V3 SUB_TYPE 149 */
	COLLATION("ES_ES", NULL, CC_SPAIN, CS_ISO8859_1, 10, ISO88591_49_init, TEXTTYPE_ATTR_PAD_SPACE)
	/* V3 SUB_TYPE 151 */
	COLLATION("SV_SV", NULL, CC_SWEDEN, CS_ISO8859_1, 11, ISO88591_51_init, TEXTTYPE_ATTR_PAD_SPACE)
	/* V3 SUB_TYPE 152 */
	COLLATION("EN_UK", NULL, CC_UK, CS_ISO8859_1, 12, ISO88591_52_init, TEXTTYPE_ATTR_PAD_SPACE)
	/* V3 SUB_TYPE 153 */
	COLLATION("EN_US", NULL, CC_US, CS_ISO8859_1, 14, ISO88591_53_init, TEXTTYPE_ATTR_PAD_SPACE)
	/* V3 SUB_TYPE 154 */
	COLLATION("PT_PT", NULL, CC_PORTUGAL, CS_ISO8859_1, 15, ISO88591_54_init, TEXTTYPE_ATTR_PAD_SPACE)
	/* V3 SUB_TYPE 155 */
	COLLATION("PT_BR", NULL, CC_BRAZIL, CS_ISO8859_1, 16, ISO88591_55_init, TEXTTYPE_ATTR_PAD_SPACE | TEXTTYPE_ATTR_CASE_INSENSITIVE | TEXTTYPE_ATTR_ACCENT_INSENSITIVE)
	/* V3 SUB_TYPE 156 */
	COLLATION("ES_ES_CI_AI", NULL, CC_SPAIN, CS_ISO8859_1, 17, ISO88591_56_init, TEXTTYPE_ATTR_PAD_SPACE | TEXTTYPE_ATTR_CASE_INSENSITIVE | TEXTTYPE_ATTR_ACCENT_INSENSITIVE)
END_CHARSET

CHARSET("ISO8859_2", CS_ISO8859_2, 0, 1, 256, CS_iso_ISO8859_2, ISO88592_cp_init, TEXTTYPE_ATTR_PAD_SPACE)
	CSALIAS("ISO8859_2", CS_ISO8859_2)
	CSALIAS("ISO88592", CS_ISO8859_2)
	CSALIAS("LATIN2", CS_ISO8859_2)
	CSALIAS("ISO-8859-2", CS_ISO8859_2)	/* Prefered MIME name */
	/* Czech national collation */
	COLLATION("CS_CZ", NULL, CC_CZECH, CS_ISO8859_2, 1, ISO88592_c1_init, TEXTTYPE_ATTR_PAD_SPACE)
	/* Hungarian collation aligned with PXW_HUN */
	COLLATION("ISO_HUN", NULL, CC_HUNGARY, CS_ISO8859_2, 2, ISO88592_c2_init, TEXTTYPE_ATTR_PAD_SPACE)
	/* Polish national collation */
	COLLATION("ISO_PLK", NULL, CC_POLAND, CS_ISO8859_2, 3, ISO88592_c3_init, TEXTTYPE_ATTR_PAD_SPACE)
END_CHARSET

CHARSET("ISO8859_3", CS_ISO8859_3, 0, 1, 256, CS_iso_ISO8859_3, ISO88593_cp_init, TEXTTYPE_ATTR_PAD_SPACE)
	CSALIAS("ISO8859_3", CS_ISO8859_3)
	CSALIAS("ISO88593", CS_ISO8859_3)
	CSALIAS("LATIN3", CS_ISO8859_3)
	CSALIAS("ISO-8859-3", CS_ISO8859_3)	/* Prefered MIME name */
END_CHARSET

CHARSET("ISO8859_4", CS_ISO8859_4, 0, 1, 256, CS_iso_ISO8859_4, ISO88594_cp_init, TEXTTYPE_ATTR_PAD_SPACE)
	CSALIAS("ISO8859_4", CS_ISO8859_4)
	CSALIAS("ISO88594", CS_ISO8859_4)
	CSALIAS("LATIN4", CS_ISO8859_4)
	CSALIAS("ISO-8859-4", CS_ISO8859_4)	/* Prefered MIME name */
END_CHARSET

CHARSET("ISO8859_5", CS_ISO8859_5, 0, 1, 256, CS_iso_ISO8859_5, ISO88595_cp_init, TEXTTYPE_ATTR_PAD_SPACE)
	CSALIAS("ISO8859_5", CS_ISO8859_5)
	CSALIAS("ISO88595", CS_ISO8859_5)
	CSALIAS("ISO-8859-5", CS_ISO8859_5)	/* Prefered MIME name */
END_CHARSET

CHARSET("ISO8859_6", CS_ISO8859_6, 0, 1, 256, CS_iso_ISO8859_6, ISO88596_cp_init, TEXTTYPE_ATTR_PAD_SPACE)
	CSALIAS("ISO8859_6", CS_ISO8859_6)
	CSALIAS("ISO88596", CS_ISO8859_6)
	CSALIAS("ISO-8859-6", CS_ISO8859_6)	/* Prefered MIME name */
END_CHARSET

CHARSET("ISO8859_7", CS_ISO8859_7, 0, 1, 256, CS_iso_ISO8859_7, ISO88597_cp_init, TEXTTYPE_ATTR_PAD_SPACE)
	CSALIAS("ISO8859_7", CS_ISO8859_7)
	CSALIAS("ISO88597", CS_ISO8859_7)
	CSALIAS("ISO-8859-7", CS_ISO8859_7)	/* Prefered MIME name */
END_CHARSET

CHARSET("ISO8859_8", CS_ISO8859_8, 0, 1, 256, CS_iso_ISO8859_8, ISO88598_cp_init, TEXTTYPE_ATTR_PAD_SPACE)
	CSALIAS("ISO8859_8", CS_ISO8859_8)
	CSALIAS("ISO88598", CS_ISO8859_8)
	CSALIAS("ISO-8859-8", CS_ISO8859_8)	/* Prefered MIME name */
END_CHARSET

CHARSET("ISO8859_9", CS_ISO8859_9, 0, 1, 256, CS_iso_ISO8859_9, ISO88599_cp_init, TEXTTYPE_ATTR_PAD_SPACE)
	CSALIAS("ISO8859_9", CS_ISO8859_9)
	CSALIAS("ISO88599", CS_ISO8859_9)
	CSALIAS("LATIN5", CS_ISO8859_9)
	CSALIAS("ISO-8859-9", CS_ISO8859_9)	/* Prefered MIME name */
END_CHARSET

CHARSET("ISO8859_13", CS_ISO8859_13, 0, 1, 256, CS_iso_ISO8859_13, ISO885913_cp_init, TEXTTYPE_ATTR_PAD_SPACE)
	CSALIAS("ISO8859_13", CS_ISO8859_13)
	CSALIAS("ISO885913", CS_ISO8859_13)
	CSALIAS("LATIN7", CS_ISO8859_13)
	CSALIAS("ISO-8859-13", CS_ISO8859_13)	/* Prefered MIME name */
	/* Lithuanian national collation */
	COLLATION("LT_LT", NULL, CC_LITHUANIA, CS_ISO8859_13, 1, ISO885913_c1_init, TEXTTYPE_ATTR_PAD_SPACE)
END_CHARSET

CHARSET("DOS852", CS_DOS_852, 0, 1, 256, CS_dos_852, DOS852_c0_init, TEXTTYPE_ATTR_PAD_SPACE)
	CSALIAS("DOS_852", CS_DOS_852)
	COLLATION("DB_CSY", NULL, CC_CZECH, CS_DOS_852, 1, DOS852_c1_init, TEXTTYPE_ATTR_PAD_SPACE)
	COLLATION("DB_PLK", NULL, CC_POLAND, CS_DOS_852, 2, DOS852_c2_init, TEXTTYPE_ATTR_PAD_SPACE)
	COLLATION("DB_SLO", NULL, CC_YUGOSLAVIA, CS_DOS_852, 4, DOS852_c4_init, TEXTTYPE_ATTR_PAD_SPACE)
	COLLATION("PDOX_CSY", NULL, CC_CZECH, CS_DOS_852, 5, DOS852_c5_init, TEXTTYPE_ATTR_PAD_SPACE)
	COLLATION("PDOX_PLK", NULL, CC_POLAND, CS_DOS_852, 6, DOS852_c6_init, TEXTTYPE_ATTR_PAD_SPACE)
	COLLATION("PDOX_HUN", NULL, CC_HUNGARY, CS_DOS_852, 7, DOS852_c7_init, TEXTTYPE_ATTR_PAD_SPACE)
	COLLATION("PDOX_SLO", NULL, CC_YUGOSLAVIA, CS_DOS_852, 8, DOS852_c8_init, TEXTTYPE_ATTR_PAD_SPACE)
END_CHARSET

CHARSET("DOS857", CS_DOS_857, 0, 1, 256, CS_dos_857, DOS857_c0_init, TEXTTYPE_ATTR_PAD_SPACE)
	CSALIAS("DOS_857", CS_DOS_857)
	COLLATION("DB_TRK", NULL, CC_TURKEY, CS_DOS_857, 1, DOS857_c1_init, TEXTTYPE_ATTR_PAD_SPACE)
END_CHARSET

CHARSET("DOS860", CS_DOS_860, 0, 1, 256, CS_dos_860, DOS860_c0_init, TEXTTYPE_ATTR_PAD_SPACE)
	CSALIAS("DOS_860", CS_DOS_860)
	COLLATION("DB_PTG860", NULL, CC_PORTUGAL, CS_DOS_860, 1, DOS860_c1_init, TEXTTYPE_ATTR_PAD_SPACE)
END_CHARSET

CHARSET("DOS861", CS_DOS_861, 0, 1, 256, CS_dos_861, DOS861_c0_init, TEXTTYPE_ATTR_PAD_SPACE)
	CSALIAS("DOS_861", CS_DOS_861)
	COLLATION("PDOX_ISL", NULL, CC_ICELAND, CS_DOS_861, 1, DOS861_c1_init, TEXTTYPE_ATTR_PAD_SPACE)
END_CHARSET

CHARSET("DOS863", CS_DOS_863, 0, 1, 256, CS_dos_863, DOS863_c0_init, TEXTTYPE_ATTR_PAD_SPACE)
	CSALIAS("DOS_863", CS_DOS_863)
	COLLATION("DB_FRC863", NULL, CC_FRENCHCAN, CS_DOS_863, 1, DOS863_c1_init, TEXTTYPE_ATTR_PAD_SPACE)
END_CHARSET

CHARSET("CYRL", CS_CYRL, 0, 1, 256, CS_cyrl, CYRL_c0_init, TEXTTYPE_ATTR_PAD_SPACE)
	COLLATION("DB_RUS", NULL, CC_RUSSIA, CS_CYRL, 1, CYRL_c1_init, TEXTTYPE_ATTR_PAD_SPACE)
	COLLATION("PDOX_CYRL", NULL, CC_RUSSIA, CS_CYRL, 2, CYRL_c2_init, TEXTTYPE_ATTR_PAD_SPACE)
END_CHARSET

CHARSET("DOS737", CS_DOS_737, 0, 1, 256, CS_dos_737, DOS737_c0_init, TEXTTYPE_ATTR_PAD_SPACE)
	CSALIAS("DOS_737", CS_DOS_737)
END_CHARSET

CHARSET("DOS775", CS_DOS_775, 0, 1, 256, CS_dos_775, DOS775_c0_init, TEXTTYPE_ATTR_PAD_SPACE)
	CSALIAS("DOS_775", CS_DOS_775)
END_CHARSET

CHARSET("DOS858", CS_DOS_858, 0, 1, 256, CS_dos_858, DOS858_c0_init, TEXTTYPE_ATTR_PAD_SPACE)
	CSALIAS("DOS_858", CS_DOS_858)
END_CHARSET

CHARSET("DOS862", CS_DOS_862, 0, 1, 256, CS_dos_862, DOS862_c0_init, TEXTTYPE_ATTR_PAD_SPACE)
	CSALIAS("DOS_862", CS_DOS_862)
END_CHARSET

CHARSET("DOS864", CS_DOS_864, 0, 1, 256, CS_dos_864, DOS864_c0_init, TEXTTYPE_ATTR_PAD_SPACE)
	CSALIAS("DOS_864", CS_DOS_864)
END_CHARSET

CHARSET("DOS866", CS_DOS_866, 0, 1, 256, CS_dos_866, DOS866_c0_init, TEXTTYPE_ATTR_PAD_SPACE)
	CSALIAS("DOS_866", CS_DOS_866)
END_CHARSET

CHARSET("DOS869", CS_DOS_869, 0, 1, 256, CS_dos_869, DOS869_c0_init, TEXTTYPE_ATTR_PAD_SPACE)
	CSALIAS("DOS_869", CS_DOS_869)
END_CHARSET

CHARSET("WIN1250", CS_WIN1250, 0, 1, 256, CS_win1250, WIN1250_c0_init, TEXTTYPE_ATTR_PAD_SPACE)
	CSALIAS("WIN_1250", CS_WIN1250)
	COLLATION("PXW_CSY", NULL, CC_CZECH, CS_WIN1250, 1, WIN1250_c1_init, TEXTTYPE_ATTR_PAD_SPACE)
	COLLATION("PXW_HUNDC", NULL, CC_HUNGARY, CS_WIN1250, 2, WIN1250_c2_init, TEXTTYPE_ATTR_PAD_SPACE)
	COLLATION("PXW_PLK", NULL, CC_POLAND, CS_WIN1250, 3, WIN1250_c3_init, TEXTTYPE_ATTR_PAD_SPACE)
	COLLATION("PXW_SLOV", NULL, CC_YUGOSLAVIA, CS_WIN1250, 4, WIN1250_c4_init, TEXTTYPE_ATTR_PAD_SPACE)
	COLLATION("PXW_HUN", NULL, CC_HUNGARY, CS_WIN1250, 5, WIN1250_c5_init, TEXTTYPE_ATTR_PAD_SPACE)
	COLLATION("BS_BA", NULL, CC_YUGOSLAVIA, CS_WIN1250, 6, WIN1250_c6_init, TEXTTYPE_ATTR_PAD_SPACE)
	COLLATION("WIN_CZ", NULL, CC_CZECH, CS_WIN1250, 7, WIN1250_c7_init, TEXTTYPE_ATTR_PAD_SPACE | TEXTTYPE_ATTR_CASE_INSENSITIVE)
	COLLATION("WIN_CZ_CI_AI", NULL, CC_CZECH, CS_WIN1250, 8, WIN1250_c8_init, TEXTTYPE_ATTR_PAD_SPACE | TEXTTYPE_ATTR_CASE_INSENSITIVE | TEXTTYPE_ATTR_ACCENT_INSENSITIVE)
END_CHARSET

CHARSET("WIN1251", CS_WIN1251, 0, 1, 256, CS_win1251, WIN1251_c0_init, TEXTTYPE_ATTR_PAD_SPACE)
	CSALIAS("WIN_1251", CS_WIN1251)
	COLLATION("PXW_CYRL", NULL, CC_RUSSIA, CS_WIN1251, 1, WIN1251_c1_init, TEXTTYPE_ATTR_PAD_SPACE)
	COLLATION("WIN1251_UA", NULL, CC_RUSSIA, CS_WIN1251, 2, WIN1251_c2_init, TEXTTYPE_ATTR_PAD_SPACE)
END_CHARSET

CHARSET("WIN1252", CS_WIN1252, 0, 1, 256, CS_win1252, WIN1252_c0_init, TEXTTYPE_ATTR_PAD_SPACE)
	CSALIAS("WIN_1252", CS_WIN1252)
	COLLATION("PXW_INTL", NULL, CC_INTL, CS_WIN1252, 1, WIN1252_c1_init, TEXTTYPE_ATTR_PAD_SPACE)
	COLLATION("PXW_INTL850", NULL, CC_INTL, CS_WIN1252, 2, WIN1252_c2_init, TEXTTYPE_ATTR_PAD_SPACE)
	COLLATION("PXW_NORDAN4", NULL, CC_NORDAN, CS_WIN1252, 3, WIN1252_c3_init, TEXTTYPE_ATTR_PAD_SPACE)
	COLLATION("PXW_SPAN", NULL, CC_SPAIN, CS_WIN1252, 4, WIN1252_c4_init, TEXTTYPE_ATTR_PAD_SPACE)
	COLLATION("PXW_SWEDFIN", NULL, CC_SWEDFIN, CS_WIN1252, 5, WIN1252_c5_init, TEXTTYPE_ATTR_PAD_SPACE)
	COLLATION("WIN_PTBR", NULL, CC_BRAZIL, CS_WIN1252, 6, WIN1252_c6_init, TEXTTYPE_ATTR_PAD_SPACE | TEXTTYPE_ATTR_CASE_INSENSITIVE | TEXTTYPE_ATTR_ACCENT_INSENSITIVE)
END_CHARSET

CHARSET("WIN1253", CS_WIN1253, 0, 1, 256, CS_win1253, WIN1253_c0_init, TEXTTYPE_ATTR_PAD_SPACE)
	CSALIAS("WIN_1253", CS_WIN1253)
	COLLATION("PXW_GREEK", NULL, CC_GREECE, CS_WIN1253, 1, WIN1253_c1_init, TEXTTYPE_ATTR_PAD_SPACE)
END_CHARSET

CHARSET("WIN1254", CS_WIN1254, 0, 1, 256, CS_win1254, WIN1254_c0_init, TEXTTYPE_ATTR_PAD_SPACE)
	CSALIAS("WIN_1254", CS_WIN1254)
	COLLATION("PXW_TURK", NULL, CC_TURKEY, CS_WIN1254, 1, WIN1254_c1_init, TEXTTYPE_ATTR_PAD_SPACE)
END_CHARSET

CHARSET("NEXT", CS_NEXT, 0, 1, 256, CS_next, NEXT_c0_init, TEXTTYPE_ATTR_PAD_SPACE)
	/* V3 SUB_TYPE 180 */
	COLLATION("NXT_US", NULL, CC_US, CS_NEXT, 1, NEXT_c1_init, TEXTTYPE_ATTR_PAD_SPACE)
	/* V3 SUB_TYPE 181 */
	COLLATION("NXT_DEU", NULL, CC_GERMANY, CS_NEXT, 2, NEXT_c2_init, TEXTTYPE_ATTR_PAD_SPACE)
	/* V3 SUB_TYPE 182 */
	COLLATION("NXT_FRA", NULL, CC_FRANCE, CS_NEXT, 3, NEXT_c3_init, TEXTTYPE_ATTR_PAD_SPACE)
	/* V3 SUB_TYPE 183 */
	COLLATION("NXT_ITA", NULL, CC_ITALY, CS_NEXT, 4, NEXT_c4_init, TEXTTYPE_ATTR_PAD_SPACE)
	/* V3 SUB_TYPE 184 */
	COLLATION("NXT_ESP", NULL, CC_SPAIN, CS_NEXT, 5, NEXT_c0_init, TEXTTYPE_ATTR_PAD_SPACE)
END_CHARSET

CHARSET("WIN1255", CS_WIN1255, 0, 1, 256, CS_win1255, WIN1255_c0_init, TEXTTYPE_ATTR_PAD_SPACE)
	CSALIAS("WIN_1255", CS_WIN1255)
END_CHARSET

CHARSET("WIN1256", CS_WIN1256, 0, 1, 256, CS_win1256, WIN1256_c0_init, TEXTTYPE_ATTR_PAD_SPACE)
	CSALIAS("WIN_1256", CS_WIN1256)
END_CHARSET

CHARSET("WIN1257", CS_WIN1257, 0, 1, 256, CS_win1257, WIN1257_c0_init, TEXTTYPE_ATTR_PAD_SPACE)
	CSALIAS("WIN_1257", CS_WIN1257)
	COLLATION("WIN1257_EE", NULL, CC_INTL, CS_WIN1257, 1, WIN1257_c1_init, TEXTTYPE_ATTR_PAD_SPACE)
	COLLATION("WIN1257_LT", NULL, CC_INTL, CS_WIN1257, 2, WIN1257_c2_init, TEXTTYPE_ATTR_PAD_SPACE)
	COLLATION("WIN1257_LV", NULL, CC_INTL, CS_WIN1257, 3, WIN1257_c3_init, TEXTTYPE_ATTR_PAD_SPACE)
END_CHARSET

CHARSET("KSC_5601", CS_KSC5601, 0, 2, 4888, CS_ksc_5601, KSC_5601_init, TEXTTYPE_ATTR_PAD_SPACE)
	CSALIAS("KSC5601", CS_KSC5601)
	CSALIAS("DOS_949", CS_KSC5601)
	CSALIAS("WIN_949", CS_KSC5601)
	COLLATION("KSC_DICTIONARY", NULL, CC_KOREA, CS_KSC5601, 1, ksc_5601_dict_init, TEXTTYPE_ATTR_PAD_SPACE)
END_CHARSET

CHARSET("BIG_5", CS_BIG5, 0, 2, 13481, CS_big_5, BIG5_init, TEXTTYPE_ATTR_PAD_SPACE)
	CSALIAS("BIG5", CS_BIG5)
	CSALIAS("DOS_950", CS_BIG5)
	CSALIAS("WIN_950", CS_BIG5)
END_CHARSET

CHARSET("GB_2312", CS_GB2312, 0, 2, 6763, CS_gb_2312, GB_2312_init, TEXTTYPE_ATTR_PAD_SPACE)
	CSALIAS("GB2312", CS_GB2312)
	CSALIAS("DOS_936", CS_GB2312)
	CSALIAS("WIN_936", CS_GB2312)
END_CHARSET

CHARSET("KOI8R", CS_KOI8R, 0, 1, 256, CS_koi8r, KOI8R_c0_init, TEXTTYPE_ATTR_PAD_SPACE)
	COLLATION("KOI8R_RU", NULL, CC_RUSSIA, CS_KOI8R, 1, KOI8R_c1_init, TEXTTYPE_ATTR_PAD_SPACE)
END_CHARSET

CHARSET("KOI8U", CS_KOI8U, 0, 1, 256, CS_koi8u, KOI8U_c0_init, TEXTTYPE_ATTR_PAD_SPACE)
	COLLATION("KOI8U_UA", NULL, CC_INTL, CS_KOI8U, 1, KOI8U_c1_init, TEXTTYPE_ATTR_PAD_SPACE)
END_CHARSET

CHARSET("WIN1258", CS_WIN1258, 0, 1, 256, CS_win1258, WIN1258_c0_init, TEXTTYPE_ATTR_PAD_SPACE)
END_CHARSET

CHARSET("TIS620", CS_TIS620, 0, 1, 256, NULL, NULL, TEXTTYPE_ATTR_PAD_SPACE)
	COLLATION("TIS620_UNICODE", NULL, CC_INTL, CS_TIS620, 1, NULL, TEXTTYPE_ATTR_PAD_SPACE)
END_CHARSET

CHARSET("GBK", CS_GBK, 0, 2, 21688, NULL, NULL, TEXTTYPE_ATTR_PAD_SPACE)
	COLLATION("GBK_UNICODE", NULL, CC_INTL, CS_GBK, 1, NULL, TEXTTYPE_ATTR_PAD_SPACE)
END_CHARSET
