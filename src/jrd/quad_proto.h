/*************  history ************
*
*       COMPONENT: JRD  MODULE: QUAD_PROTO.H
*       generated by Marion V2.5     2/6/90
*       from dev              db        on 6-DEC-1993
*****************************************************************
*
*       0       katz    6-DEC-1993
*       history begins
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
 *      PROGRAM:        JRD Access Method
 *      MODULE:         quad_proto.h
 *      DESCRIPTION:    Prototype header file for quad.cpp
 *
 * copyright (c) 1993 by Borland International
 */

#ifndef JRD_QUAD_PROTO_H
#define JRD_QUAD_PROTO_H

#ifdef __cplusplus
extern "C" {
#endif

SQUAD	QUAD_add(const SQUAD*, const SQUAD*, FPTR_ERROR);
SSHORT	QUAD_compare(const SQUAD*, const SQUAD*);
SQUAD	QUAD_from_double(const double*, FPTR_ERROR);
SQUAD	QUAD_multiply(const SQUAD*, const SQUAD*, FPTR_ERROR);
SQUAD	QUAD_negate(const SQUAD*, FPTR_ERROR);
SQUAD	QUAD_subtract(const SQUAD*, const SQUAD*, FPTR_ERROR);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif // JRD_QUAD_PROTO_H

