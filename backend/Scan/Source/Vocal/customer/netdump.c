
/* ************************************************************************* */
/*
 *	pppdump.c
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
 *	Module:		Customer
 *
 *	This file contains the network dump functions.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.2.6.2  2009/04/28 19:09:22  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#include "system/system.h"
#include "lansend/global.h"

#include <ctype.h>

#include "net/net.h"
#include "sys/sys.h"
#include "dev/dev.h"

#include "ip/local.h"
#include "wan/local.h"
#include "trace/local.h"

#include "support/support.h"

#include "../bsm/bsm_SerialPort.h"

#include "customer/local.h"

#define SERIAL_BUF_SIZE 250

char serial_buf[SERIAL_BUF_SIZE + 1];
char format_buf[SERIAL_BUF_SIZE + 1];
int buf_offset = 0;

LOCAL void
print_buffered_string (bool now, char *str)
{
	int len = strlen(str);

	if (now || ((len + buf_offset) >= SERIAL_BUF_SIZE)) {
		if (buf_offset > 0) {
			bsm_SDWrite (serial_buf, buf_offset);
			serial_buf [0] = 0;
			buf_offset = 0;
		}
		bsm_SDWrite (str, len);
	}
	else {
		generic_safe_strcat(serial_buf, str, SERIAL_BUF_SIZE);
		buf_offset += len;
	}
}

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */

ENTRY void
ip_dump (struct iface *ifp, FILE *fp, struct mbuf **bpp, int check)
{
	struct ip ip;
	uint16 ip_len;
	uint16 length;
	uint16 csum;

	if (bpp == NULLBUFP || *bpp == NULLBUF)
		return;

	print_buffered_string (FALSE, "IP:");
	/* Sneak peek at IP header and find length */
	ip_len = ((*bpp)->data[0] & 0xf) << 2;
	if (ip_len < IPHDRLEN) {
		print_buffered_string (TRUE, " bad header\n\r");
		return;
	}
	if (check)
		csum = cksum (NULLHEADER, *bpp, ip_len);
	else
		csum = 0;

	ntohip(&ip,bpp);	/* Can't fail, we've already checked ihl */

	/* Trim data segment if necessary. */
	length = ip.length - ip_len;	/* Length of data portion */
	trim_mbuf (bpp, length);
	generic_sprintf(format_buf, " len %u",ip.length);
	print_buffered_string (FALSE, format_buf);

	generic_sprintf(format_buf, " %s",snhtoa(&ip.source));
	print_buffered_string (FALSE, format_buf);
	generic_sprintf(format_buf, "->%s ihl %u ttl %u", snhtoa (&ip.dest), ip_len, uchar (ip.ttl));
	print_buffered_string (FALSE, format_buf);

	if (ip.tos != 0) {
		generic_sprintf(format_buf, " tos %u",uchar(ip.tos));
		print_buffered_string (FALSE, format_buf);
	}

	if (ip.offset != 0 || ip.flags.mf) {
		generic_sprintf(format_buf, " id %u offs %u",ip.id,ip.offset);
		print_buffered_string (FALSE, format_buf);
	}

	if (ip.flags.df) {
		print_buffered_string (FALSE, " DF");
	}

	if (ip.flags.mf) {
		print_buffered_string (FALSE, " MF");
		check = 0;	/* Bypass host-level checksum verify */
	}

	if (ip.flags.congest) {
		print_buffered_string (FALSE, " CE");
	}

	if (csum != 0) {
		generic_sprintf(format_buf, " CHECKSUM ERROR (%u)",csum);
		print_buffered_string (FALSE, format_buf);
	}

	if (ip.offset != 0) {
		print_buffered_string (TRUE, "\n\r");
		return;
	}
	switch (uchar (ip.protocol)) {
	case IP_PTCL:
		print_buffered_string (TRUE, " prot IP\n\r");
		ip_dump (ifp, fp, bpp, check);
		break;
	case TCP_PTCL:
		print_buffered_string (TRUE, " prot TCP\n\r");
		tcp_dump (fp, bpp, ip.source.sin_address, ip.dest.sin_address, check);
		break;
	case UDP_PTCL:
		print_buffered_string (TRUE, " prot UDP\n\r");
		udp_dump (fp, bpp, ip.source.sin_address, ip.dest.sin_address, check);
		break;
	case ICMP_PTCL:
		print_buffered_string (TRUE, " prot ICMP\n\r");
		icmp_dump (ifp, fp, bpp, ip.source.sin_address, ip.dest.sin_address, check);
		break;
	default:
		generic_sprintf(format_buf, " prot %u\n\r", uchar(ip.protocol));
		print_buffered_string (TRUE, format_buf);
		break;
	}
}

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */

/* Dump an ICMP header */
ENTRY void
icmp_dump (struct iface *ifp, FILE *fp, struct mbuf **bpp, sint31 source, sint31 dest, int check)
{
	struct icmp icmp;
	uint16 csum;

	if (bpp == NULLBUFP || *bpp == NULLBUF)
		return;
	csum = cksum (NULLHEADER, *bpp, len_p (*bpp));

	ntohicmp (&icmp, bpp);

	generic_sprintf(format_buf, "ICMP: type %s",smsg(Icmptypes,ICMP_TYPES,uchar(icmp.type)));
	print_buffered_string (FALSE, format_buf);

	switch (uchar (icmp.type)) {
	case ICMP_DEST_UNREACH:
		generic_sprintf(format_buf, " code %s",smsg(Unreach,NUNREACH,uchar(icmp.code)));
		print_buffered_string (FALSE, format_buf);
		break;
	case ICMP_REDIRECT:
		generic_sprintf(format_buf, " code %s new gateway %s", smsg(Redirect,NREDIRECT,uchar(icmp.code)), inet_ntoa(icmp.args.address));
		print_buffered_string (FALSE, format_buf);
		break;
	case ICMP_TIME_EXCEED:
		generic_sprintf(format_buf, " code %s",smsg(Exceed,NEXCEED,uchar(icmp.code)));
		print_buffered_string (FALSE, format_buf);
		break;
	case ICMP_PARAM_PROB:
		generic_sprintf(format_buf, " pointer %u",icmp.args.pointer);
		print_buffered_string (FALSE, format_buf);
		break;
	case ICMP_ECHO:
	case ICMP_ECHO_REPLY:
	case ICMP_INFO_RQST:
	case ICMP_INFO_REPLY:
	case ICMP_TIMESTAMP:
	case ICMP_TIME_REPLY:
		generic_sprintf(format_buf, " id %u seq %u",icmp.args.echo.id,icmp.args.echo.seq);
		print_buffered_string (FALSE, format_buf);
		break;
	}
	if (check && csum != 0) {
		generic_sprintf(format_buf, " CHECKSUM ERROR (%u)",csum);
		print_buffered_string (FALSE, format_buf);
	}
	print_buffered_string (TRUE, "\n\r");

	/* Dump the offending IP header, if any */
	switch (icmp.type) {
	case ICMP_DEST_UNREACH:
	case ICMP_TIME_EXCEED:
	case ICMP_PARAM_PROB:
	case ICMP_QUENCH:
	case ICMP_REDIRECT:
		print_buffered_string (FALSE, "Returned ");
		ip_dump (ifp, fp, bpp, 0);
	}
}

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */

/* TCP segment header flags */
static char *Tcpflags[] = {
	"FIN",	/* 0x01 */
	"SYN",	/* 0x02 */
	"RST",	/* 0x04 */
	"PSH",	/* 0x08 */
	"ACK",	/* 0x10 */
	"URG",	/* 0x20 */
	"ECE",	/* 0x40 */
	"CWR"	/* 0x80 */
};

/* Dump a TCP segment header. Assumed to be in network byte order */
ENTRY void
tcp_dump (FILE *fp, struct mbuf **bpp, sint31 source, sint31 dest, int check)
{
	struct tcp seg;
	struct pseudo_header ph;
	uint16 csum;
	uint16 dlen;

	if (bpp == NULLBUFP || *bpp == NULLBUF)
		return;

	/* Verify checksum */
	ph.source = source;
	ph.dest = dest;
	ph.protocol = TCP_PTCL;
	ph.length = len_p (*bpp);
	csum = cksum (&ph, *bpp, ph.length);

	ntohtcp (&seg, bpp);

	generic_sprintf(format_buf, "TCP: %u->%u Seq x%lx",seg.source,seg.dest, (long) seg.seq);
	print_buffered_string (FALSE, format_buf);

	if (seg.flags.ack) {
		generic_sprintf(format_buf, " Ack x%lx",(long) seg.ack);
		print_buffered_string (FALSE, format_buf);
	}
	generic_sprintf(format_buf, " %s",Tcpflags[6]);
	print_buffered_string (FALSE, format_buf);

	if (seg.flags.cwr) {
		generic_sprintf(format_buf, " %s",Tcpflags[7]);
		print_buffered_string (FALSE, format_buf);
	}

	if (seg.flags.ece) {
		generic_sprintf(format_buf, " %s",Tcpflags[6]);
		print_buffered_string (FALSE, format_buf);
	}

	if (seg.flags.urg) {
		generic_sprintf(format_buf, " %s",Tcpflags[5]);
		print_buffered_string (FALSE, format_buf);
	}

	if (seg.flags.ack) {
		generic_sprintf(format_buf, " %s",Tcpflags[4]);
		print_buffered_string (FALSE, format_buf);
	}

	if (seg.flags.psh) {
		generic_sprintf(format_buf, " %s",Tcpflags[3]);
		print_buffered_string (FALSE, format_buf);
	}

	if (seg.flags.rst) {
		generic_sprintf(format_buf, " %s",Tcpflags[2]);
		print_buffered_string (FALSE, format_buf);
	}

	if (seg.flags.syn) {
		generic_sprintf(format_buf, " %s",Tcpflags[1]);
		print_buffered_string (FALSE, format_buf);
	}

	if (seg.flags.fin) {
		generic_sprintf(format_buf, " %s",Tcpflags[0]);
		print_buffered_string (FALSE, format_buf);
	}

	generic_sprintf(format_buf, " Wnd %u",seg.wnd);
	print_buffered_string (FALSE, format_buf);

	if (seg.flags.urg) {
		generic_sprintf(format_buf, " UP x%x",seg.up);
		print_buffered_string (FALSE, format_buf);
	}
	/* Print options, if any */
	if (seg.mss != 0) {
		generic_sprintf(format_buf, " MSS %u",seg.mss);
		print_buffered_string (FALSE, format_buf);
	}

	if ((dlen = len_p (*bpp)) != 0) {
		generic_sprintf(format_buf, " Data %u",dlen);
		print_buffered_string (FALSE, format_buf);
	}

	if (check && csum != 0) {
		generic_sprintf(format_buf, " CHECKSUM ERROR (%u)",csum);
		print_buffered_string (FALSE, format_buf);
	}

	print_buffered_string (TRUE, "\n\r");
}

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */

/* Dump a UDP header */
ENTRY void
udp_dump (FILE *fp, struct mbuf **bpp, sint31 source, sint31 dest, int check)
{
	struct udp udp;
	struct pseudo_header ph;
	uint16 csum;

	if (bpp == NULLBUFP || *bpp == NULLBUF)
		return;

	print_buffered_string (FALSE, "UDP:");

	/* Compute checksum */
	ph.source = source;
	ph.dest = dest;
	ph.protocol = UDP_PTCL;
	ph.length = len_p (*bpp);
	if ((csum = cksum (&ph, *bpp, ph.length)) == 0)
		check = 0;	/* No checksum error */

	ntohudp (&udp, bpp);

		generic_sprintf(format_buf, " len %u %u->%u",udp.length,udp.source,udp.dest);
		print_buffered_string (FALSE, format_buf);

	if (udp.length > UDPHDR) {
		generic_sprintf(format_buf, " Data %u",udp.length - UDPHDR);
		print_buffered_string (FALSE, format_buf);
	}

	if (udp.checksum == 0)
		check = 0;
	if (check) {
		generic_sprintf(format_buf, " CHECKSUM ERROR (%u)",csum);
		print_buffered_string (FALSE, format_buf);
	}

	print_buffered_string (TRUE, "\n\r");

	switch (udp.dest) {
#if DO_LANSEND_IP_RIP
		case IPPORT_RIP:
		rip_dump (fp, bpp);
#endif /* DO_LANSEND_IP_RIP */
	}

}

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */

/* dump the PPP FSM packet header */
ENTRY void
ppp_fsm_dump (FILE *fp, struct mbuf **bpp, int unused)
{
	struct config_hdr hdr;

	if (ntohcnf(&hdr, bpp) != 0) {
		print_buffered_string (FALSE, "*** header too short!\n\r");
	}

	generic_sprintf(format_buf, "#%03d length:%6d ", hdr.identifier, hdr.length);
	print_buffered_string (FALSE, format_buf);

	if (hdr.code >= CONFIG_REQ
	  && hdr.code <= DISCARD_REQ) {
		generic_sprintf(format_buf, "%s\n\r",fsmCodes[hdr.code]);
		print_buffered_string (TRUE, format_buf);
	} else {
		generic_sprintf(format_buf, "unknown code %03d\n\r",hdr.code);
		print_buffered_string (TRUE, format_buf);
	}
}

/* ************************************************************************* */

/* dump a PPP packet */
ENTRY void
ppp_dump (struct iface *ifp, FILE *fp, struct mbuf **bpp, int unused)
{
	struct ppp_hdr hdr;
	struct mbuf *tbp;

	generic_sprintf(format_buf, "PPP: len %3u\t", len_p(*bpp));
	print_buffered_string (FALSE, format_buf);

	if (ifp->d_type != IFD_PACKET) {
		/* HDLC address and control fields may be compressed out */
		if ((uint8)(*bpp)->data[0] != HDLC_ALL_ADDR) {
			generic_sprintf(format_buf, "(compressed ALL/UI)\t");
			print_buffered_string (FALSE, format_buf);
		} else if ((uint8)(*bpp)->data[1] != HDLC_UI) {
			generic_sprintf(format_buf, "(missing UI!)\t");
			print_buffered_string (FALSE, format_buf);
		} else {
			/* skip address/control fields */
			pull16(bpp);
		}
	}

	/* Initialize the expected header */
	hdr.addr = HDLC_ALL_ADDR;
	hdr.control = HDLC_UI;
	hdr.protocol = PULLCHAR(bpp);

	/* First byte of PPP protocol field may be compressed out */
	if (hdr.protocol & 0x01) {
		print_buffered_string (FALSE, "compressed ");
	} else {
		hdr.protocol = (hdr.protocol << 8) | PULLCHAR(bpp);

		/* Second byte of PPP protocol field must be odd */
		if (!(hdr.protocol & 0x01)) {
			print_buffered_string (FALSE, "(*not* odd!) ");
		}
	}

	print_buffered_string (FALSE, "protocol: ");

	switch (hdr.protocol) {
	case PPP_IP_PROTOCOL:
		print_buffered_string (TRUE, "IP\n\r");
		ip_dump(ifp, fp,bpp,1);
		break;
	case PPP_VJCH_PROTOCOL:
		print_buffered_string (TRUE, "VJ Compressed TCP/IP\n\r");
		vjcomp_dump(fp,bpp,0);
		break;
	case PPP_VJUCH_PROTOCOL:
		print_buffered_string (TRUE, "VJ Uncompressed TCP/IP\n\r");
		/* Get our own copy so we can mess with the data */
		if ((tbp = copy_p(*bpp, len_p(*bpp))) == NULLBUF)
			return;

		generic_sprintf(format_buf, "\tconnection 0x%02x\n\r", tbp->data[9]);
		print_buffered_string (TRUE, format_buf);
		/* Restore the bytes used with Uncompressed TCP */
		tbp->data[9] = TCP_PTCL;
		ip_dump(ifp, fp,&tbp,1);
		free_p(tbp);
		break;
	case PPP_OSINL_PROTOCOL:
		print_buffered_string (TRUE, "OSI Network Layer\n\r");
		break;
	case PPP_XNS_PROTOCOL:
		print_buffered_string (TRUE, "Xerox NS IDP\n\r");
		break;
	case PPP_DN4_PROTOCOL:
		print_buffered_string (TRUE, "DECnet Phase IV\n\r");
		break;
	case PPP_AT_PROTOCOL:
		print_buffered_string (TRUE, "Appletalk\n\r");
		break;
	case PPP_IPX_PROTOCOL:
		print_buffered_string (TRUE, "Novell IPX\n\r");
		break;
	case PPP_BPDU_PROTOCOL:
		print_buffered_string (TRUE, "Bridging PDU\n\r");
		break;
	case PPP_ST2_PROTOCOL:
		print_buffered_string (TRUE, "Stream Protocol (ST-II)\n\r");
		break;
	case PPP_BV_PROTOCOL:
		print_buffered_string (TRUE, "Banyan Vines\n\r");
		break;
	case PPP_8021D_PROTOCOL:
		print_buffered_string (TRUE, "802.1d Hello Packets\n\r");
		break;
	case PPP_LUXCOM_PROTOCOL:
		print_buffered_string (TRUE, "Luxcom\n\r");
		break;
	case PPP_SIGMA_PROTOCOL:
		print_buffered_string (TRUE, "Sigma Network Systems\n\r");
		break;
	case PPP_IPCP_PROTOCOL:
		print_buffered_string(TRUE, "IPCP\n\r");
		ppp_fsm_dump(fp,bpp,unused);
		break;
	case PPP_OSINLCP_PROTOCOL:
		print_buffered_string (TRUE, "OSI Network Layer Control Protocol\n\r");
		ppp_fsm_dump(fp,bpp,unused);
		break;
	case PPP_XNSCP_PROTOCOL:
		print_buffered_string (TRUE, "Xerox NS IDP Control Protocol\n\r");
		ppp_fsm_dump(fp,bpp,unused);
		break;
	case PPP_DN4CP_PROTOCOL:
		print_buffered_string (TRUE, "DECnet Phase IV Control Protocol\n\r");
		ppp_fsm_dump(fp,bpp,unused);
		break;
	case PPP_ATCP_PROTOCOL:
		print_buffered_string (TRUE, "Appletalk Control Protocol\n\r");
		ppp_fsm_dump(fp,bpp,unused);
		break;
	case PPP_IPXCP_PROTOCOL:
		print_buffered_string (TRUE, "Novell IPX Control Protocol\n\r");
		ppp_fsm_dump(fp,bpp,unused);
		break;
	case PPP_BNCP_PROTOCOL:
		print_buffered_string (TRUE, "Bridging NCP\n\r");
		ppp_fsm_dump(fp,bpp,unused);
		break;
	case PPP_ST2CP_PROTOCOL:
		print_buffered_string (TRUE, "Stream Protocol Control Protocol\n\r");
		ppp_fsm_dump(fp,bpp,unused);
		break;
	case PPP_BVCP_PROTOCOL:
		print_buffered_string (TRUE, "Banyan Vines Control Protocol\n\r");
		ppp_fsm_dump(fp,bpp,unused);
		break;
	case PPP_LCP_PROTOCOL:
		print_buffered_string (TRUE, "LCP\n\r");
		ppp_fsm_dump(fp,bpp,unused);
		break;
	case PPP_LQR_PROTOCOL:
		print_buffered_string (TRUE, "LQR\n\r");
		break;
	case PPP_PAP_PROTOCOL:
		print_buffered_string (TRUE, "PAP\n\r");
		break;
	case PPP_CHAP_PROTOCOL:
		print_buffered_string (TRUE, "CHAP\n\r");
		break;
	default:
		generic_sprintf(format_buf, "unknown 0x%04x\n\r",hdr.protocol);
		print_buffered_string (TRUE, format_buf);
		break;
	};
}

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */

LOCAL uint16
decodeint (struct mbuf **bpp)
{
	char tmpbuf[2];

	pullup(bpp,tmpbuf,1);
	if (tmpbuf[0] == 0)
		pullup(bpp,tmpbuf,2);
	else {
	 	tmpbuf[1] = tmpbuf[0];
		tmpbuf[0] = 0;
	}
	return(get16(tmpbuf));
}

ENTRY void
vjcomp_dump (FILE *fp, struct mbuf **bpp, int unused)
{
	char changes;
	char tmpbuf[2];

	if (bpp == NULLBUFP || *bpp == NULLBUF)
		return;

	/* Dump compressed TCP/IP header */
	changes = pullchar(bpp);
	generic_sprintf(format_buf, "\tchanges: 0x%02x",uchar(changes));
	print_buffered_string (FALSE, format_buf);

	if (changes & NEW_C) {
		pullup(bpp,tmpbuf,1);
		generic_sprintf(format_buf, "   connection: 0x%02x",uchar(tmpbuf[0]));
		print_buffered_string (FALSE, format_buf);
	}
	pullup(bpp,tmpbuf,2);
	generic_sprintf(format_buf, "   TCP checksum: 0x%04x",get16(tmpbuf));
	print_buffered_string (FALSE, format_buf);

	if (changes & TCP_PUSH_BIT) {
		print_buffered_string (FALSE, "   PUSH");
	}

	print_buffered_string (FALSE, "\n\r");

	switch (changes & SPECIALS_MASK) {
	case SPECIAL_I:
		print_buffered_string (FALSE, "\tdelta ACK and delta SEQ implied by length of data\n\r");
		break;

	case SPECIAL_D:
		print_buffered_string (FALSE, "\tdelta SEQ implied by length of data\n\r");
		break;

	default:
		if (changes & NEW_U) {
			generic_sprintf(format_buf, "\tUrgent pointer: 0x%02x",decodeint(bpp));
			print_buffered_string (TRUE, format_buf);
		}
		if (changes & NEW_W) {
			generic_sprintf(format_buf, "\tdelta WINDOW: 0x%02x",decodeint(bpp));
			print_buffered_string (TRUE, format_buf);
		}

		if (changes & NEW_A) {
			generic_sprintf(format_buf, "\tdelta ACK: 0x%02x",decodeint(bpp));
			print_buffered_string (TRUE, format_buf);
		}

		if (changes & NEW_S) {
			generic_sprintf(format_buf, "\tdelta SEQ: 0x%02x",decodeint(bpp));
			print_buffered_string (TRUE, format_buf);
		}

		break;
	};
	if (changes & NEW_I) {
		generic_sprintf(format_buf, "\tdelta ID: 0x%02x\n\r",decodeint(bpp));
		print_buffered_string (TRUE, format_buf);
	} else {
		print_buffered_string (TRUE, "\tincrement ID\n\r");
	}
}

/* dump serial line IP packet; may have Van Jacobson TCP header compression */
ENTRY void
sl_dump (struct iface *ifp, FILE *fp, struct mbuf **bpp, int unused)
{
	struct mbuf *bp, *tbp;
	uint8 c;
	int len;

	bp = *bpp;
	c = bp->data[0];
	if (c & SL_TYPE_COMPRESSED_TCP) {
		generic_sprintf(format_buf, "serial line VJ Compressed TCP: len %3u\n\r", len_p(*bpp));
		print_buffered_string (FALSE, format_buf);
		vjcomp_dump(fp,bpp,0);
	}
	else if (c >= SL_TYPE_UNCOMPRESSED_TCP) {
		generic_sprintf(format_buf, "serial line VJ Uncompressed TCP: len %3u\n\r", len = len_p(bp));
		print_buffered_string (FALSE, format_buf);

		/* Get our own copy so we can mess with the data */
		if ((tbp = copy_p(bp, len)) == NULLBUF)
			return;

		generic_sprintf(format_buf, "\tconnection ID = %d\n\r", uchar(tbp->data[9]));
		print_buffered_string (FALSE, format_buf);

		/* Restore the bytes used with Uncompressed TCP */
		tbp->data[0] &= 0x4f;
		tbp->data[9] = TCP_PTCL;
		/* Dump contents as a regular IP packet */
		ip_dump(ifp, fp,&tbp,1);
		free_p(tbp);
	} else {
		generic_sprintf(format_buf, "serial line IP: len: %3u\n\r",len_p(*bpp));
		print_buffered_string (FALSE, format_buf);
		ip_dump(ifp, fp,bpp,1);
	}
}

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* ************************************************************************* */

/* Redefined here so that programs calling dump in the library won't pull
 * in the rest of the package
 */
#define nospace Nospace

/* Table of trace subcommands */
typedef struct tracecmd_s {
	char *name;					/* Name of trace subcommand */
	uint32 val;					/* New setting for these bits */
	uint32 mask;				/* Mask of bits affected in trace word */
} tracecmd_t;

/* ************************************************************************* */

static const tracecmd_t Tracecmd[] =
{
	"input", IF_TRACE_IN, IF_TRACE_IN,
	"-input", 0, IF_TRACE_IN,
	"output", IF_TRACE_OUT, IF_TRACE_OUT,
	"-output", 0, IF_TRACE_OUT,
	"broadcast", 0, IF_TRACE_NOBC,
	"-broadcast", IF_TRACE_NOBC, IF_TRACE_NOBC,
	"raw", IF_TRACE_RAW, IF_TRACE_RAW,
	"-raw", 0, IF_TRACE_RAW,
	"ascii", IF_TRACE_ASCII, IF_TRACE_ASCII | IF_TRACE_HEX,
	"-ascii", 0, IF_TRACE_ASCII | IF_TRACE_HEX,
	"hex", IF_TRACE_HEX, IF_TRACE_ASCII | IF_TRACE_HEX,
	"-hex", IF_TRACE_ASCII, IF_TRACE_ASCII | IF_TRACE_HEX,
	"off", 0, 0xffff,
	NULLCHAR, 0, 0
};

/* ************************************************************************* */
/*
 *  Function: ctohex
 *
 *  Convert byte to two ASCII characters
 *
 *  Parameters:
 *    "buf" is the buffer to receive the ASCII characters
 *    "c" is the byte to convert to ASCII
 *
 *  Returns: (none)
 *
 */
static const char hex[] = "0123456789abcdef";

LOCAL void
ctohex (char *buf, uint16 c)
{
	*buf++= hex[hinibble (c) ];
	*buf = hex[lonibble (c) ];
}

/* ************************************************************************* */
/*
 *  Function: fmtline
 *
 *  Print a buffer up to 16 bytes long in formatted hex with ascii translation.
 *
 *  0000: 30 31 32 33 34 35 36 37 38 39 3a 3b 3c 3d 3e 3f  0123456789:; <= > ?
 *
 *  Parameters:
 *    "fp" is the file pointer
 *    "addr" is the address to print
 *    "buf" is the pointer to the bytes of data to print
 *    "len" is the number of data bytes to print
 *
 *  Returns: (none)
 *
 */
LOCAL void
fmtline (FILE *fp, uint16 addr, char *buf, uint16 len)
{
	char line[80];
	register char *aptr, *cptr;
	register char c;

	if (buf_offset > 0) {
		bsm_SDWrite (serial_buf, buf_offset);
		serial_buf [0] = 0;
		buf_offset = 0;
	}

	memset (line, ' ', sizeof (line));
	ctohex (line, (uint16) hibyte (addr));
	ctohex (line + 2, (uint16) lobyte (addr));
	aptr = &line[6];
	cptr = &line[55];
	while (len-- != 0) {
		c = *buf++;
		ctohex (aptr, (uint16) uchar (c));
		aptr += 3;
		c &= 0x7f;
		*cptr++= isprint (uchar (c)) ? c : '.';
	}
	*cptr++= '\n';
	*cptr++= '\r';
	*cptr = '\0';
	print_buffered_string (TRUE, line);
}

/* ************************************************************************* */
/*
 *  Function: hex_dump
 *
 *  Display packet in hex.
 *
 *  Parameters:
 *    "fp" is the file pointer
 *    "bpp" is the pointer to the pointer to the packet
 *
 *  Returns: (none)
 *
 */
LOCAL void
hex_dump (FILE *fp, struct mbuf **bpp)
{
	uint16 n;
	uint16 address;
	char buf[16];

	if (bpp == NULLBUFP || *bpp == NULLBUF || fp == NULLFILE)
		return;

	address = 0;
	while ((n = pullup (bpp, buf, sizeof (buf))) != 0) {
		fmtline (fp, address, buf, n);
		address += n;
	}
}

/* ************************************************************************* */
/*
 *  Function: ascii_dump
 *
 *  Display packet data in ASCII.
 *
 *  Parameters:
 *    "fp" is the file pointer
 *    "bp" is the pointer to the pointer to the packet
 *
 *  Returns: (none)
 *
 */
LOCAL void
ascii_dump (FILE *fp, struct mbuf **bpp)
{
	int c;
	register uint16 tot;

	if (bpp == NULLBUFP || *bpp == NULLBUF || fp == NULLFILE)
		return;

	tot = 0;
	while ((c = PULLCHAR (bpp)) != -1) {
		if ((tot % 64) == 0) {
			generic_sprintf(format_buf, "%04x  ", tot);
			print_buffered_string (FALSE, format_buf);
		}

		generic_sprintf(format_buf, "%c", isprint (uchar (c)) ? c : '.');
		print_buffered_string (FALSE, format_buf);

		if ((++tot % 64) == 0) {
			print_buffered_string (TRUE, "\n\r");
		}
	}

	if ((tot % 64) != 0) {
		print_buffered_string (TRUE, "\n\r");
	}
}

/* ************************************************************************* */
/*
 *  Function: dump
 *
 *  Display packet according to packet information following trace options.
 *
 *  Parameters:
 *    "ifp" is the interface pointer
 *    "direction" is the direction of the packet
 *    "bp" is the pointer to the packet
 *
 *  Returns: (none)
 *
 */
ENTRY void
dump (struct iface *ifp, int direction, struct mbuf *bp)
{
	struct mbuf *tbp;
	uint16 size;
	time_t timer;
	char *cp;
	const struct iftype *ift;
	FILE *fp;

	if (ifp == NULL || (ifp->trace & direction) == 0
		|| (fp = ifp->trfp) == NULLFILE)
		return;					/* Nothing to trace */

	if (buf_offset > 0) {
		bsm_SDWrite (serial_buf, buf_offset);
		serial_buf [0] = 0;
		buf_offset = 0;
	}

	ift = ifp->iftype;
	switch (direction) {
	case IF_TRACE_IN:
		if ((ifp->trace & IF_TRACE_NOBC) && ift != NULLIFT
			&& (ift->addrtest != NULLFP) && (*ift->addrtest) (ifp, bp) == 0)
			return;				/* broadcasts are suppressed */
		time (&timer);
		cp = ctime (&timer);
		cp[24] = '\0';
		generic_sprintf(format_buf,  "\n\r%s - %s recv:\n\r", cp, ifp->name);
		print_buffered_string (TRUE, format_buf);
		break;
	case IF_TRACE_OUT:
		time (&timer);
		cp = ctime (&timer);
		cp[24] = '\0';
		generic_sprintf(format_buf,  "\n\r%s - %s sent:\n\r", cp, ifp->name);
		print_buffered_string (TRUE, format_buf);
		break;
	}
	if (bp == NULLBUF || (size = len_p (bp)) == 0) {
		print_buffered_string (TRUE, "empty packet!!\n\r");
		return;
	}
	dup_p (&tbp, bp, 0, size);
	if (tbp == NULLBUF) {
		print_buffered_string (TRUE, (char *) nospace);
		return;
	}
	if (ift != NULLIFT && ift->trace != NULLVFP) {
		(*ift->trace) (ifp, fp, &tbp, 1);
	}

	if (ifp->trace & IF_TRACE_HEX) {
		/* Dump entire packet in hex/ascii */
		free_p (tbp);
		dup_p (&tbp, bp, 0, len_p (bp));
		if (tbp != NULLBUF) {
			hex_dump (fp, &tbp);
		}
		else {
			print_buffered_string (TRUE, (char *) nospace);
		}
	}
	else if (ifp->trace & IF_TRACE_ASCII) {
		/* Dump only data portion of packet in ascii */
		ascii_dump (fp, &tbp);
	}
	free_p (tbp);

}

/* ************************************************************************* */
/*
 *  Function: raw_dump
 *
 *  Display packet in raw format following trace options.
 *
 *  Parameters:
 *    "ifp" is the interface pointer
 *    "direction" is the direction of the packet
 *    "bp" is the pointer to the packet
 *
 *  Returns: (none)
 *
 */
ENTRY void
raw_dump (struct iface *ifp, int direction, struct mbuf *bp)
{
	struct mbuf *tbp;
	FILE *fp;

	if ((fp = ifp->trfp) == NULLFILE) {
		return;
	}

	generic_sprintf(format_buf,  "\n\r******* raw packet dump (%s %s)\n\r", ((direction & IF_TRACE_OUT) ? "send" : "recv"), ifp->name);
	print_buffered_string (TRUE, format_buf);

	dup_p (&tbp, bp, 0, len_p (bp));
	if (tbp != NULLBUF) {
		hex_dump (fp, &tbp);
	}
	else {
		print_buffered_string (TRUE, (char *) nospace);
	}

	print_buffered_string (TRUE, "*******\n\r");
	free_p (tbp);
}

/* ************************************************************************* */
/*
 *  Function: show_trace
 *
 *  Display trace flags for a particular interface.
 *
 *  Parameters:
 *    "ifp" is the interface pointer
 *
 *  Returns: (none)
 *
 */
LOCAL void
show_trace (struct iface *ifp)
{
	char *cp;

	if (ifp == NULLIF) {
		return;
	}

	print_buffered_string (FALSE, ifp->name);

	if (ifp->trace &(IF_TRACE_IN | IF_TRACE_OUT | IF_TRACE_RAW)) {
		if (ifp->trace & IF_TRACE_IN) {
			print_buffered_string (FALSE, " input");
		}

		if (ifp->trace & IF_TRACE_OUT) {
			print_buffered_string (FALSE, " ouput");
		}

		if (ifp->trace & IF_TRACE_NOBC) {
			print_buffered_string (FALSE, " - no broadcasts");
		}

		if (ifp->trace & IF_TRACE_HEX) {
			print_buffered_string (FALSE, " (Hex/ASCII dump)");
		}
		else if (ifp->trace & IF_TRACE_ASCII) {
			print_buffered_string (FALSE, " (ASCII dump)");
		}
		else {
			print_buffered_string (FALSE, " (headers only)");
		}

		if (ifp->trace & IF_TRACE_RAW) {
			print_buffered_string (FALSE, " Raw output");
		}
		if (ifp->trfp != NULLFILE && (cp = fpname (ifp->trfp)) != NULLCHAR) {
			generic_sprintf(format_buf,  " trace file: %s", cp);
			print_buffered_string (FALSE, format_buf);
		}
		print_buffered_string (TRUE, "\n\r");
	}
	else {
		print_buffered_string (TRUE, " tracing off\n\r");
	}
}

/* ************************************************************************* */
/*
 *  Function: dotrace
 *
 *  Modify or display interface trace flags
 *
 *  Parameters:
 *    "argc" is the command line argument count
 *    "argv" is the list of command tokens
 *    "p" is an unused pointer
 *
 *  Command Line: trace [[dev|cir] option]
 *
 *  Returns: 0 for success
 *           else error
 *
 */
ENTRY int
dotrace (int argc, char *argv[], void *p)
{
	struct iface *ifp;
	const tracecmd_t *tp;

	if (argc < 2) {
		for (ifp = Ifaces; ifp != NULLIF; ifp = ifp->next)
			show_trace (ifp);
		return 0;
	}
	if (atoiface_err (argv[1], &ifp))
		return 1;

	if (argc == 2) {
		show_trace (ifp);
		return 0;
	}
	/* MODIFY THIS TO HANDLE MULTIPLE OPTIONS */
	if (argc >= 3) {
		for (tp = Tracecmd; tp->name != NULLCHAR; tp++)
			if (strncmp (tp->name, argv[2], strlen (argv[2])) == 0)
				break;
		if (tp->name != NULLCHAR)
			ifp->trace = (ifp->trace & ~tp->mask) | tp->val;
		else {
			if (atoi16u_err (argv[2], &ifp->trace))
				return 1;
		}
	}
	if (ifp->trfp != NULLFILE) {
		/* Close existing trace file */
		fclose (ifp->trfp);
		ifp->trfp = NULLFILE;
	}

	if (argc >= 4) {
		if ((ifp->trfp = fopen (argv[3], APPEND_TEXT)) == NULLFILE) {
			generic_sprintf(format_buf,  "Can't write to %s\n\r", argv[3]);
			print_buffered_string (TRUE, format_buf);
		}
	}
	else {
		ifp->trfp = fdup (stdout);
	}

	return 0;
}

/* ************************************************************************* */
/*
 *  Function: shuttrace
 *
 *  Close all open trace files
 *
 *  Parameters: (none)
 *
 *  Returns: (none)
 *
 */
ENTRY void
shuttrace (void)
{
	struct iface *ifp;

	for (ifp = Ifaces; ifp != NULLIF; ifp = ifp->next) {
		fclose (ifp->trfp);
		ifp->trfp = NULLFILE;
	}
}

/* ************************************************************************* */
/*
 *  Function: trace_log
 *
 *  Log messages in the log file of the form
 *
 *  Tue Jan 31 00:00:00 1987 44.64.0.7:1003 open FTP
 *
 *  Parameters:
 *    "ifp" is the interface pointer
 *    "fmt" is the format string pointer
 *    followed by variable argument list
 *
 *  Returns: (none)
 *
 */
ENTRY void
trace_log (struct iface *ifp, char *fmt, ...)
{
	va_list ap;
	char *cp;
	time_t t;
	FILE *fp;

	if ((fp = ifp->trfp) == NULLFILE)
		return;
	time (&t);
	cp = ctime (&t);
	rip (cp);

	print_buffered_string (FALSE, cp);
	print_buffered_string (FALSE, " - ");
	va_start (ap, fmt);
	generic_sprintf(format_buf, fmt, ap);
	print_buffered_string (FALSE, format_buf);

	va_end (ap);
	print_buffered_string (TRUE, "\n\r");
}

/* ************************************************************************* */
/*
 *  Function: tprint
 *
 *  Print messages in the log file.
 *
 *  Parameters:
 *    "ifp" is the interface pointer
 *    "fmt" is the format string pointer
 *    followed by variable argument list
 *
 *  Returns: 0 if successful
 *           -1 if error
 *
 */
ENTRY int
tprintf (struct iface *ifp, char *fmt, ...)
{
	va_list ap;
	int ret = 0;

	if (ifp->trfp == NULLFILE)
		return -1;
	va_start (ap, fmt);

	generic_sprintf(format_buf,  fmt, ap);
	print_buffered_string (FALSE, format_buf);

	va_end (ap);
	return ret;
}

/* ************************************************************************* */
