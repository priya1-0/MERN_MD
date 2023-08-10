
/* ************************************************************************* */
/*
 *	af.h
 *
 *	(C) 1994 - 2006 VOCAL Technologies, Ltd.
 *
 *	ALL RIGHTS RESERVED.  PROPRIETARY AND CONFIDENTIAL.
 *
 *	VOCAL Technologies, Ltd.
 *	90A John Muir Drive.
 *	Buffalo, NY  14228
 *
 *	Product:	LANsEND
 *
 *	Module:		NET
 *
 *	This file contains the global declarations for the NET module.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.24.1  2009/04/28 20:31:57  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _NET_AF_H
#define _NET_AF_H

#define inet_hostmatch(sa1,sa2) (((sa1)->sin_address == (sa2)->sin_address) && \
				((sa1)->sa_family == (sa2)->sa_family))
#define inet_hostsame(sa1,sa2) ((sa1)->sin_address == (sa2)->sin_address)

#define novell_netmatch(sa1,sa2) (((sa1)->sns_network == (sa2)->sns_network) && \
				 ((sa1)->sa_family == (sa2)->sa_family))
#define novell_netsame(sa1,sa2) ((sa1)->sns_network == (sa2)->sns_network)

#endif /* _NET_AF_H */
