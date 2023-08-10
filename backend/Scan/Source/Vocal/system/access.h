
/* ************************************************************************* */
/*
 *	access.h
 *
 *	(C) 1994 - 2006 VOCAL Technologies, Ltd.
 *
 *	ALL RIGHTS RESERVED.  PROPRIETARY AND CONFIDENTIAL.
 *
 *	VOCAL Technologies, Ltd.
 *	90A John Muir Drive.
 *	Buffalo, NY  14228
 *
 *	Product:	MODEM 101
 *
 *	Module:		SYSTEM
 *
 *	This file contains macro define inter-process access procedures.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.1  2009/04/28 20:47:21  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _SYSTEM_ACCESS_H
#define _SYSTEM_ACCESS_H

/* ************************************************************************* */

/* ************************************************************************* */

#define access_app_omc_set_event(A)					set_event (A)
#define access_app_omc_dm_rd(A,B)					B = A
#define access_app_omc_dm_offset_rd(A,B,C)			C = A[B]
#define access_app_omc_dm_wr(A,B)					A = B
#define access_app_omc_dm_offset_wr(A,B,C)			A[B] = C
#define access_app_omc_dm_wr_direct(A,B)			A = B
#define access_app_omc_offset_dm_wr_direct(A,B,C)	A[B] = C

#define access_app_omc_dm_rd_array(A,B,C)	\
{											\
	uint16 i;								\
											\
	for (i = 0; i < C; i++) {				\
		B [i] = A [i];						\
	}										\
}

#define access_app_omc_dm_wr_array(A,B,C)	\
{											\
	uint16 i;								\
											\
	for (i = 0; i < C; i++) {				\
		A [i] = B [i];						\
	}										\
}

#define access_app_omc_dm_wr_stringz(A,B)	\
{											\
	uint16 length;							\
	uint16 i;								\
											\
	length = strlen (B);			\
	for (i = 0; i < length; i++) {			\
		A [i] = B [i];						\
	}										\
}

#define access_app_omc_dm_rd_string(A,B,C)	\
{											\
	uint16 i;								\
											\
	for (i = 0; i < C; i++) {				\
		B [i] = A [i];						\
	}										\
}

#define access_app_omc_dm_wr_string(A,B,C)	\
{											\
	uint16 i;								\
											\
	for (i = 0; i < C; i++) {				\
		A [i] = B [i];						\
	}										\
}

#define access_app_pump_set_event(A)				set_event (A)
#define access_app_pump_dm_rd(A,B)					B = A
#define access_app_pump_dm_offset_rd(A,B,C)			C = A[B]
#define access_app_pump_dm_wr(A,B)					A = B
#define access_app_pump_dm_offset_wr(A,B,C)			A[B] = C
#define access_app_pump_dm_wr_direct(A,B)			A = B
#define access_app_pump_offset_dm_wr_direct(A,B,C)	A[B] = C
#define access_app_pump_dm_rd_array(A,B,C)	\
{											\
	uint16 i;								\
											\
	for (i = 0; i < C; i++) {				\
		B [i] = A [i];						\
	}										\
}

#define access_app_pump_dm_wr_array(A,B,C)	\
{											\
	uint16 i;								\
											\
	for (i = 0; i < C; i++) {				\
		A [i] = B [i];						\
	}										\
}

#define access_app_pump_dm_wr_stringz(A,B)	\
{											\
	uint16 length;							\
	uint16 i;								\
											\
	length = strlen (B);			\
	for (i = 0; i < length; i++) {			\
		A [i] = B [i];						\
	}										\
}

#define access_app_pump_dm_rd_string(A,B,C)	\
{											\
	uint16 i;								\
											\
	for (i = 0; i < C; i++) {				\
		B [i] = A [i];						\
	}										\
}

#define access_app_pump_dm_wr_string(A,B,C)	\
{											\
	uint16 i;								\
											\
	for (i = 0; i < C; i++) {				\
		A [i] = B [i];						\
	}										\
}

#define access_csc_omc_set_event(A)					set_event (A)
#define access_csc_omc_dm_rd(A,B)					B = A
#define access_csc_omc_dm_offset_rd(A,B,C)			C = A[B]
#define access_csc_omc_dm_wr(A,B)					A = B
#define access_csc_omc_dm_offset_wr(A,B,C)			A[B] = C
#define access_csc_omc_dm_wr_direct(A,B)			A = B
#define access_csc_omc_offset_dm_wr_direct(A,B,C)	A[B] = C

#define access_csc_omc_dm_rd_array(A,B,C)	\
{											\
	uint16 i;								\
											\
	for (i = 0; i < C; i++) {				\
		B [i] = A [i];						\
	}										\
}

#define access_csc_omc_dm_wr_array(A,B,C)	\
{											\
	uint16 i;								\
											\
	for (i = 0; i < C; i++) {				\
		A [i] = B [i];						\
	}										\
}

#define access_csc_omc_dm_wr_stringz(A,B)	\
{											\
	uint16 length;							\
	uint16 i;								\
											\
	length = strlen (B);			\
	for (i = 0; i < length; i++) {			\
		A [i] = B [i];						\
	}										\
}

#define access_csc_omc_dm_rd_string(A,B,C)	\
{											\
	uint16 i;								\
											\
	for (i = 0; i < C; i++) {				\
		B [i] = A [i];						\
	}										\
}

#define access_csc_omc_dm_wr_string(A,B,C)	\
{											\
	uint16 i;								\
											\
	for (i = 0; i < C; i++) {				\
		A [i] = B [i];						\
	}										\
}

#define access_csc_pump_set_event(A)				set_event (A)
#define access_csc_pump_dm_rd(A,B)					B = A
#define access_csc_pump_dm_offset_rd(A,B,C)			C = A[B]
#define access_csc_pump_dm_wr(A,B)					A = B
#define access_csc_pump_dm_offset_wr(A,B,C)			A[B] = C
#define access_csc_pump_dm_wr_direct(A,B)			A = B
#define access_csc_pump_dm_offset_wr_direct(A,B,C)	A[B] = C

#define access_csc_pump_dm_rd_array(A,B,C)	\
{											\
	uint16 i;								\
											\
	for (i = 0; i < C; i++) {				\
		B [i] = A [i];						\
	}										\
}

#define access_csc_pump_dm_wr_array(A,B,C)	\
{											\
	uint16 i;								\
											\
	for (i = 0; i < C; i++) {				\
		A [i] = B [i];						\
	}										\
}

#define access_csc_pump_dm_wr_stringz(A,B)	\
{											\
	uint16 length;							\
	uint16 i;								\
											\
	length = strlen (B);			\
	for (i = 0; i < length; i++) {			\
		A [i] = B [i];						\
	}										\
}

#define access_csc_pump_dm_rd_string(A,B,C)	\
{											\
	uint16 i;								\
											\
	for (i = 0; i < C; i++) {				\
		B [i] = A [i];						\
	}										\
}

#define access_csc_pump_dm_wr_string(A,B,C)	\
{											\
	uint16 i;								\
											\
	for (i = 0; i < C; i++) {				\
		A [i] = B [i];						\
	}										\
}

#define access_omc_pump_set_event(A)				set_event (A)
#define access_omc_pump_dm_rd(A,B)					B = A
#define access_omc_pump_dm_offset_rd(A,B,C)			C = A[B]
#define access_omc_pump_dm_wr(A,B)					A = B
#define access_omc_pump_dm_offset_wr(A,B,C)			A[B] = C
#define access_omc_pump_dm_wr_direct(A,B)			A = B
#define access_omc_pump_dm_offset_wr_direct(A,B,C)	A[B] = C

#define access_omc_pump_dm_rd_array(A,B,C)	\
{											\
	uint16 i;								\
											\
	for (i = 0; i < C; i++) {				\
		B [i] = A [i];						\
	}										\
}

#define access_omc_pump_dm_wr_array(A,B,C)	\
{											\
	uint16 i;								\
											\
	for (i = 0; i < C; i++) {				\
		A [i] = B [i];						\
	}										\
}

#define access_omc_pump_dm_wr_stringz(A,B)	\
{											\
	uint16 length;							\
	uint16 i;								\
											\
	length = strlen (B);			\
	for (i = 0; i < length; i++) {			\
		A [i] = B [i];						\
	}										\
}

#define access_omc_pump_dm_rd_string(A,B,C)	\
{											\
	uint16 i;								\
											\
	for (i = 0; i < C; i++) {				\
		B [i] = A [i];						\
	}										\
}

#define access_omc_pump_dm_wr_string(A,B,C)	\
{											\
	uint16 i;								\
											\
	for (i = 0; i < C; i++) {				\
		A [i] = B [i];						\
	}										\
}

#define access_csc_omc_set_event(A)											\
	set_event (A)

#define access_csc_omc_dm_rd(A,B)											\
	B = A

#define access_csc_omc_dm_offset_rd(A,B,C)									\
	C = A[B]

#define access_csc_omc_dm_wr(A,B)											\
	A = B

#define access_csc_omc_dm_offset_wr(A,B,C)									\
	A[B] = C

#define access_csc_omc_dm_wr_direct(A,B)									\
	A = B

#define access_csc_omc_offset_dm_wr_direct(A,B,C)							\
	A[B] = C

#define access_csc_omc_dm_rd_array(A,B,C)									\
{																			\
	uint16 i;																\
																			\
	for (i = 0; i < C; i++) {												\
		B [i] = A [i];														\
	}																		\
}

#define access_csc_omc_dm_wr_array(A,B,C)									\
{																			\
	uint16 i;																\
																			\
	for (i = 0; i < C; i++) {												\
		A [i] = B [i];														\
	}																		\
}

#define access_csc_omc_dm_wr_stringz(A,B)									\
{																			\
	uint16 length;															\
	uint16 i;																\
																			\
	length = strlen (B);											\
	for (i = 0; i < length; i++) {											\
		A [i] = B [i];														\
	}																		\
}

#define access_csc_omc_dm_rd_string(A,B,C)									\
{																			\
	uint16 i;																\
																			\
	for (i = 0; i < C; i++) {												\
		B [i] = A [i];														\
	}																		\
}

#define access_csc_omc_dm_wr_string(A,B,C)									\
{																			\
	uint16 i;																\
																			\
	for (i = 0; i < C; i++) {												\
		A [i] = B [i];														\
	}																		\
}

/* ************************************************************************* */

#define access_csc_pump_set_event(A)										\
	set_event (A)

#define access_csc_pump_dm_rd(A,B)											\
	B = A

#define access_csc_pump_dm_offset_rd(A,B,C)									\
	C = A[B]

#define access_csc_pump_dm_wr(A,B)											\
	A = B

#define access_csc_pump_dm_offset_wr(A,B,C)									\
	A[B] = C

#define access_csc_pump_dm_wr_direct(A,B)									\
	A = B

#define access_csc_pump_dm_offset_wr_direct(A,B,C)							\
	A[B] = C

#define access_csc_pump_dm_rd_array(A,B,C)									\
{																			\
	uint16 i;																\
																			\
	for (i = 0; i < C; i++) {												\
		B [i] = A [i];														\
	}																		\
}

#define access_csc_pump_dm_wr_array(A,B,C)									\
{																			\
	uint16 i;																\
																			\
	for (i = 0; i < C; i++) {												\
		A [i] = B [i];														\
	}																		\
}

#define access_csc_pump_dm_wr_stringz(A,B)									\
{																			\
	uint16 length;															\
	uint16 i;																\
																			\
	length = strlen (B);											\
	for (i = 0; i < length; i++) {											\
		A [i] = B [i];														\
	}																		\
}

#define access_csc_pump_dm_rd_string(A,B,C)									\
{																			\
	uint16 i;																\
																			\
	for (i = 0; i < C; i++) {												\
		B [i] = A [i];														\
	}																		\
}

#define access_csc_pump_dm_wr_string(A,B,C)									\
{																			\
	uint16 i;																\
																			\
	for (i = 0; i < C; i++) {												\
		A [i] = B [i];														\
	}																		\
}

/* ************************************************************************* */

#define access_omc_pump_set_event(A)										\
	set_event (A)

#define access_omc_pump_dm_rd(A,B)											\
	B = A

#define access_omc_pump_dm_offset_rd(A,B,C)									\
	C = A[B]

#define access_omc_pump_dm_wr(A,B)											\
	A = B

#define access_omc_pump_dm_offset_wr(A,B,C)									\
	A[B] = C

#define access_omc_pump_dm_wr_direct(A,B)									\
	A = B

#define access_omc_pump_dm_offset_wr_direct(A,B,C)							\
	A[B] = C

#define access_omc_pump_dm_rd_array(A,B,C)									\
{																			\
	uint16 i;																\
																			\
	for (i = 0; i < C; i++) {												\
		B [i] = A [i];														\
	}																		\
}

#define access_omc_pump_dm_wr_array(A,B,C)									\
{																			\
	uint16 i;																\
																			\
	for (i = 0; i < C; i++) {												\
		A [i] = B [i];														\
	}																		\
}

#define access_omc_pump_dm_wr_stringz(A,B)									\
{																			\
	uint16 length;															\
	uint16 i;																\
																			\
	length = strlen (B);											\
	for (i = 0; i < length; i++) {											\
		A [i] = B [i];														\
	}																		\
}

#define access_omc_pump_dm_rd_string(A,B,C)									\
{																			\
	uint16 i;																\
																			\
	for (i = 0; i < C; i++) {												\
		B [i] = A [i];														\
	}																		\
}

#define access_omc_pump_dm_wr_string(A,B,C)									\
{																			\
	uint16 i;																\
																			\
	for (i = 0; i < C; i++) {												\
		A [i] = B [i];														\
	}																		\
}

/* ************************************************************************* */

#endif /* SYSTEM_ACCESS_H */
