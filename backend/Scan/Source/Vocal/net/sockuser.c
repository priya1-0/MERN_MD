
/* ************************************************************************* */
/*
 *	sockuser.c
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
 *	This file contains the higher level user functions built on top of the socket primitives.
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

#include "system/system.h"
#include "lansend/global.h"

#include "net/local.h"

#include "dev/dev.h"
#include "sys/sys.h"

#include "ip/ip.h"

#include "net/local.h"

/* Higher-level receive routine, intended for connection-oriented sockets.
 * Can be used with datagram sockets, although the sender id is lost.
 */
ENTRY int
recv (int s, char *buf, int len, int flags)
{
	struct mbuf *bp;
	int cnt;

	if (len == 0)
		return 0;	/* Otherwise would be interp as "all" */

	cnt = recv_mbuf (s, &bp, len, flags, NULLCHAR, (int *) NULL);
	if (cnt > 0) {
		cnt = min (cnt, len);
		pullup (&bp, buf, (uint16) cnt);
		free_p (bp);
	}
	return cnt;
}
/* Higher level receive routine, intended for datagram sockets. Can also
 * be used for connection - oriented sockets, although from and fromlen are
 * ignored.
 */
ENTRY int
recvfrom (int s, char *buf, int len, int flags, char *from, int *fromlen)
{
	struct mbuf *bp;
	register int cnt;

	cnt = recv_mbuf (s, &bp, len, flags, from, fromlen);
	if (cnt > 0) {
		cnt = min (cnt, len);
		pullup (&bp, buf, (uint16) cnt);
		free_p (bp);
	}
	return cnt;
}
/* High level send routine */
ENTRY int
send (int s, char *buf, int len, int flags)
{
	register struct mbuf *bp;
	char sock[SOCKSIZE];
	int i = SOCKSIZE;

	if (getpeername (s, sock, &i) == -1)
		return -1;
	bp = qdata (buf, (uint16) len);
	return send_mbuf (s, bp, flags, sock, i);
}
/* High level send routine, intended for datagram sockets. Can be used on
 * connection-oriented sockets, but "to" and "tolen" are ignored.
 */
ENTRY int
sendto (int s, char *buf, int len, int flags, char *to, int tolen)
{
	register struct mbuf *bp;

	bp = qdata (buf, (uint16) len);
	return send_mbuf (s, bp, flags, to, tolen);
}
