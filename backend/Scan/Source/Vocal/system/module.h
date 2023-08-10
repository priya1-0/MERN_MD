
/* ************************************************************************* */
/*
 *	module.h
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
 *	This file defines the module groupings.
 *
 *	Revision Number:	$Revision$
 *	Revision Status:	$State$
 *	Last Modified:		$Date$
 *	Identification:		$Id$
 *
 *	Revision History:	$Log$
 *	Revision History:	Revision 1.1.6.2  2009/04/28 20:47:21  zhangn1
 *	Revision History:	SCR #173564. 2490H Vocal upgrade to Rev 4.56C
 *	Revision History:	
 *
 */
/* ************************************************************************* */

#ifndef _SYSTEM_MODULE_H
#define _SYSTEM_MODULE_H

/* ************************************************************************* */

/* ************************************************************************* */

/* ************************************************************************* */
/*
 *	ATA Module Group uses parm__net_debug_level_ata
 */

/* ATA */
#ifdef ata_module
#define ATA_MODULE
#endif /* ata_module */

#ifdef atarom_module
#define ATA_MODULE
#endif /* atarom_module */

#ifdef ataweb_module
#define ATA_MODULE
#endif /* ataweb_module */

#ifdef vidrom_module
#define ATA_MODULE
#endif /* vidrom_module */

/* DPBX */
#ifdef dpbx_module
#define DPBX_MODULE
#endif /* dpbx_module */

/* IPBX */
#ifdef ipbx_module
#define IPBX_MODULE
#endif /* ipbx_module */

#ifdef region_module
#define IPBX_MODULE
#endif /* region_module */

#ifdef oomaif_module
#define APPLICATION_MODULE
#endif /* oomaif_module */

#ifdef wcli_module
#define APPLICATION_MODULE
#endif /* wcli_module */

#if defined (ATA_MODULE) || defined (DPBX_MODULE) || defined (IPBX_MODULE) || defined (APPLICATION_MODULE)
#define ATA_MODULE_GROUP
#endif

/* ************************************************************************* */

/* ************************************************************************* */
/*
 *	SYS Module Group uses
 */

/* SYS */
#ifdef support_module
#define SYS_MODULE
#endif /* support_module */

#ifdef vsock_module
#define SYS_MODULE
#endif /* vsock_module */

/* APP */
#ifdef demo1_module
#define APP_MODULE
#endif /* demo1_module */

#ifdef demo2_module
#define APP_MODULE
#endif /* demo2_module */

#ifdef demo3_module
#define APP_MODULE
#endif /* demo3_module */

#ifdef dtam_module
#define APP_MODULE
#endif /* dtam_module */

#ifdef fxapp_module
#define APP_MODULE
#endif /* fxapp_module */

#ifdef phone_module
#define APP_MODULE
#endif /* phone_module */

#ifdef rspmon_module
#define APP_MODULE
#endif /* rspmon_module */

#ifdef spapp_module
#define APP_MODULE
#endif /* spapp_module */

#ifdef srdev_module
#define APP_MODULE
#endif /* srdev_module */

#ifdef svapp_module
#define APP_MODULE
#endif /* svapp_module */

#ifdef tapp_module
#define APP_MODULE
#endif /* tapp_module */

#ifdef vcapp_module
#define APP_MODULE
#endif /* vcapp_module */

#ifdef bigno_module
#define BIGNO_MODULE
#endif /* bigno_module */

#ifdef rsa_module
#define RSA_MODULE
#endif /* rsa_module */

#if defined (SYS_MODULE) || defined (APP_MODULE)
#define SYS_MODULE_GROUP
#endif

/* ************************************************************************* */

/* ************************************************************************* */
/*
 *	MGCP Module Group uses parm__net_debug_level_mgcp
 */

/* MGCP_MGCP */
#ifdef mgcp_module
#define MGCP_MODULE_GROUP
#endif /* mgcp_module */

/* ************************************************************************* */
/*
 *	SIP Module Group uses parm__net_debug_level_sip
 */

/* SIP_SIP */
#ifdef sip_module
#define SIP_MODULE_GROUP
#endif /* sip_module */

/* ************************************************************************* */

/* ************************************************************************* */
/*
 *	VOIP Module Group uses parm__net_debug_level_net
 */

/* VOIP_SDP */
#ifdef sdp_module
#define VOIP_SDP_MODULE
#endif /* sdp_module */

/* VOIP_RTP */
#ifdef rtmsc_module
#define VOIP_RTP_MODULE
#endif /* rtmsc_module */

#ifdef rtp_module
#define VOIP_RTP_MODULE
#endif /* rtp_module */

#ifdef rtpint_module
#define VOIP_RTP_MODULE
#endif /* rtpint_module */

/* VOIP_H323 */
#ifdef asn_1_module
#define VOIP_H323_MODULE
#endif /* asn_1_module */

#ifdef h225_module
#define VOIP_H323_MODULE
#endif /* h225_module */

#ifdef h225ras_module
#define VOIP_H323_MODULE
#endif /* h225ras_module */

#ifdef h245_module
#define VOIP_H323_MODULE
#endif /* h245_module */

#ifdef h323_module
#define VOIP_H323_MODULE
#endif /* h323_module */

#ifdef h323app_module
#define VOIP_H323_MODULE
#endif /* h323app_module */

#ifdef ccsrl_module
#define VOIP_H323_MODULE
#endif /* ccsrl_module */

#ifdef realtmrs_module
#define VOIP_H323_MODULE
#endif /* realtmrs_module */

#ifdef socket_module
#define VOIP_H323_MODULE
#endif /* socket_module */

#if defined (VOIP_SDP_MODULE) || defined (VOIP_RTP_MODULE) || defined (VOIP_H323_MODULE)
#define VOIP_MODULE_GROUP
#endif

/* VOIP_VOIP */
#ifdef voip_module
#define VOIP_MODULE_GROUP
#endif /* voip_module */

/* ************************************************************************* */

/* ************************************************************************* */
/*
 *	VIDEO Module Group uses parm__net_debug_level_video (midground)
 */

/* VIDEO */
#ifdef video_module
#define VIDEO_MG_MODULE
#endif /* video_module */

#ifdef jpeg_module
#define VIDEO_MG_MODULE
#endif /* jpeg_module */

#ifdef mpeg2_module
#define VIDEO_MG_MODULE
#endif /* mpeg2_module */

#ifdef mpeg4_module
#define VIDEO_MG_MODULE
#endif /* mpeg4_module */

/* RTSP */
#ifdef rtsp_module
#define VIDEO_MODULE
#endif /* rtsp_module */

#if defined (VIDEO_MG_MODULE) || defined (VIDEO_MODULE)
#define VIDEO_MODULE_GROUP
#endif

/* ************************************************************************* */

/* ************************************************************************* */
/*
 *	VPPN Module Group uses parm__net_debug_level_vppn
 */

/* VPPN */
#ifdef vppn_module
#define VPPN_MODULE
#endif /* vppn_module */

#ifdef VPPN_MODULE
#define VPPN_MODULE_GROUP
#endif /* VPPN_MODULE */

/* ************************************************************************* */
/*
 *	NET Module Group uses parm__net_debug_level_net
 */

/* NET_LANSEND */
#ifdef lansend_module
#define NET_LANSEND_MODULE
#endif /* lansend_module */

#ifdef net_module
#define NET_LANSEND_MODULE
#endif /* net_module */

#ifdef test_module
#define NET_LANSEND_MODULE
#endif /* test_module */

#ifdef trace_module
#define NET_LANSEND_MODULE
#endif /* trace_module */

#ifdef startup_module
#define NET_LANSEND_MODULE
#endif /* startup_module */

#ifdef sys_module
#define NET_LANSEND_MODULE
#endif /* sys_module */

/* NET_IP */
#ifdef ip_module
#define NET_IP_MODULE
#endif /* ip_module */

/* NET_IPX */
#ifdef ipx_module
#define NET_IPX_MODULE
#endif /* ipx_module */

/* NET_DEV */
#ifdef dev_module
#define NET_DEV_MODULE
#endif /* dev_module */

#ifdef wan_module
#define NET_DEV_MODULE
#endif /* wan_module */

/* NET_SNMP */
#ifdef snmp_module
#define NET_SNMP_MODULE
#endif /* snmp_module */

/* NET_UTIL */
#ifdef nat_module
#define NET_UTIL_MODULE
#endif /* nat_module */

#ifdef natmap_module
#define NET_UTIL_MODULE
#endif /* natmap_module */

#ifdef term_module
#define NET_UTIL_MODULE
#endif /* term_module */

#ifdef crypto_module
#define NET_UTIL_MODULE
#endif /* crypto_module */

#ifdef utils_module
#define NET_UTIL_MODULE
#endif /* utils_module */

/* NET_SSL */
#ifdef aes_module
#define NET_SSL_MODULE
#endif /* aes_module */

#ifdef openssl_module
#define NET_SSL_MODULE
#endif /* openssl_module */

#ifdef sha_module
#define NET_SSL_MODULE
#endif /* sha_module */

#ifdef ssl_module
#define NET_SSL_MODULE
#endif /* ssl_module */

#ifdef sslasn1_module
#define NET_SSL_MODULE
#endif /* sslasn1_module */

#ifdef sslbio_module
#define NET_SSL_MODULE
#endif /* sslbio_module */

#ifdef sslbuf_module
#define NET_SSL_MODULE
#endif /* sslbuf_module */

#ifdef ssldata_module
#define NET_SSL_MODULE
#endif /* ssldata_module */

#ifdef sslerr_module
#define NET_SSL_MODULE
#endif /* sslerr_module */

#ifdef sslevp_module
#define NET_SSL_MODULE
#endif /* sslevp_module */

#ifdef sslhmac_module
#define NET_SSL_MODULE
#endif /* sslhmac_module */

#ifdef ssllhash_module
#define NET_SSL_MODULE
#endif /* ssllhash_module */

#ifdef sslobj_module
#define NET_SSL_MODULE
#endif /* sslobj_module */

#ifdef sslpem_module
#define NET_SSL_MODULE
#endif /* sslpem_module */

#ifdef sslrand_module
#define NET_SSL_MODULE
#endif /* sslrand_module */

#ifdef sslstack_module
#define NET_SSL_MODULE
#endif /* sslstack_module */

#ifdef x509_module
#define NET_SSL_MODULE
#endif /* x509_module */

#if defined (NET_LANSEND_MODULE) || defined (NET_IP_MODULE) || defined (NET_IPX_MODULE) || defined (NET_DEV_MODULE) || defined (NET_SNMP_MODULE) || defined (NET_UTIL_MODULE) || defined (NET_SSL_MODULE)
#define NET_MODULE_GROUP
#endif

/* ************************************************************************* */
/*
 *	MDM Module Group uses parm__net_debug_level_omc
 */

/* MDM_BG */
#ifdef bgkernel_module
#define MDM_BG_MODULE
#endif /* bgkernel_module */

#ifdef line_module
#define MDM_BG_MODULE
#endif /* line_module */

#ifdef clock_module
#define MDM_BG_MODULE
#endif /* clock_module */

#ifdef mdm_BG_module
#define MDM_BG_MODULE
#endif /* mdm_BG_module */

#ifdef ipsim_module
#define MDM_BG_MODULE
#endif /* ipsim_module */

#ifdef load_module
#define MDM_BG_MODULE
#endif /* load_module */

#ifdef nvm_module
#define MDM_BG_MODULE
#endif /* nvm_module */

#ifdef nvmdrv_module
#define MDM_BG_MODULE
#endif /* nvmdrv_module */

#ifdef nvm_w95_module
#define MDM_BG_MODULE
#endif /* nvm_w95_module */

#ifdef omc_module
#define MDM_BG_MODULE
#endif /* omc_module */

#ifdef overlay_module
#define MDM_BG_MODULE
#endif /* overlay_module */

#ifdef platform_module
#define MDM_BG_MODULE
#endif /* platform_module */

#ifdef sigma_module
#define MDM_BG_MODULE
#endif /* sigma_module */

#ifdef snoop_module
#define MDM_BG_MODULE
#endif /* snoop_module */

#ifdef v24_module
#define MDM_BG_MODULE
#endif /* v24_module */

#ifdef win31_module
#define MDM_BG_MODULE
#endif /* win31_module */

#ifdef win95_module
#define MDM_BG_MODULE
#endif /* win95_module */

#ifdef xy_module
#define MDM_BG_MODULE
#endif /* xy_module */

/* MDM_DP */
#ifdef btlz_module
#define MDM_DP_MODULE
#endif /* btlz_module */

#ifdef buffered_module
#define MDM_DP_MODULE
#endif /* buffered_module */

#ifdef detect_module
#define MDM_DP_MODULE
#endif /* detect_module */

#ifdef direct_module
#define MDM_DP_MODULE
#endif /* direct_module */

#ifdef dp_module
#define MDM_DP_MODULE
#endif /* dp_module */

#ifdef lapf_module
#define MDM_DP_MODULE
#endif /* lapf_module */

#ifdef lapm_module
#define MDM_DP_MODULE
#endif /* lapm_module */

#ifdef mnp_module
#define MDM_DP_MODULE
#endif /* mnp_module */

#ifdef mnp5_module
#define MDM_DP_MODULE
#endif /* mnp5_module */

#ifdef v120_module
#define MDM_DP_MODULE
#endif /* v120_module */

#ifdef v44_module
#define MDM_DP_MODULE
#endif /* v44_module */

/* MDM_FX */
#ifdef ecm_module
#define MDM_FX_MODULE
#endif /* ecm_module */

#ifdef fx1_module
#define MDM_FX_MODULE
#endif /* fx1_module */

#ifdef t4_module
#define MDM_FX_MODULE
#endif /* t4_module */

#ifdef t30_module
#define MDM_FX_MODULE
#endif /* t30_module */

#ifdef t30line_module
#define MDM_FX_MODULE
#endif /* t30line_module */

#ifdef t38_module
#define MDM_FX_MODULE
#endif /* t38_module */

/* MDM_CSC */
#ifdef bind_module
#define MDM_CSC_MODULE
#endif /* bind_module */

#ifdef cs602_module
#define MDM_CSC_MODULE
#endif /* cs602_module */

#ifdef csc_module
#define MDM_CSC_MODULE
#endif /* csc_module */

#ifdef cscsim_module
#define MDM_CSC_MODULE
#endif /* cscsim_module */

#ifdef csfax1_module
#define MDM_CSC_MODULE
#endif /* csfax1_module */

#ifdef csfax2_module
#define MDM_CSC_MODULE
#endif /* csfax2_module */

#ifdef csp_module
#define MDM_CSC_MODULE
#endif /* csp_module */

#ifdef cssim_module
#define MDM_CSC_MODULE
#endif /* cssim_module */

#ifdef csstd_module
#define MDM_CSC_MODULE
#endif /* csstd_module */

#ifdef csv25t_module
#define MDM_CSC_MODULE
#endif /* csv25t_module */

#ifdef parse_module
#define MDM_CSC_MODULE
#endif /* parse_module */

/* MDM_DTE */
#ifdef dte_module
#define MDM_DTE_MODULE
#endif /* dte_module */

#ifdef dteif_module
#define MDM_DTE_MODULE
#endif /* dteif_module */

#ifdef serial1_module
#define MDM_DTE_MODULE
#endif /* serial1_module */

/* MDM_TEL */
#ifdef scc_module
#define MDM_TEL_MODULE
#endif /* scc_module */

#ifdef tssc_module
#define MDM_TEL_MODULE
#endif /* tssc_module */

#if defined (MDM_BG_MODULE) || defined (MDM_DP_MODULE) || defined (MDM_FX_MODULE) || defined (MDM_CSC_MODULE) || defined (MDM_DTE_MODULE) || defined (MDM_TEL_MODULE)
#define MDM_MODULE_GROUP
#endif

/* ************************************************************************* */
/*
 *	PUMP Module Group uses parm__net_debug_level_pmp (foreground)
 */

/* PMP_FG */
#ifdef dspmbx_module
#define PMP_FG_MODULE
#endif /* dspmbx_module */

#ifdef fract_module
#define PMP_FG_MODULE
#endif /* fract_module */

#ifdef general_module
#define PMP_FG_MODULE
#endif /* general_module */

#ifdef kernel_module
#define PMP_FG_MODULE
#endif /* kernel_module */

#ifdef lib_module
#define PMP_FG_MODULE
#endif /* lib_module */

#ifdef pump_module
#define PMP_FG_MODULE
#endif /* pump_module */

#ifdef state_module
#define PMP_FG_MODULE
#endif /* state_module */

/* PMP_DM */
#ifdef lib22_module
#define PMP_DM_MODULE
#endif /* lib22_module */

#ifdef lib32_module
#define PMP_DM_MODULE
#endif /* lib32_module */

#ifdef lib34_module
#define PMP_DM_MODULE
#endif /* lib34_module */

#ifdef lib34f_module
#define PMP_DM_MODULE
#endif /* lib34f_module */

#ifdef lib34h_module
#define PMP_DM_MODULE
#endif /* lib34h_module */

#ifdef lib34l_module
#define PMP_DM_MODULE
#endif /* lib34l_module */

#ifdef lib34n_module
#define PMP_DM_MODULE
#endif /* lib34n_module */

#ifdef lib90_module
#define PMP_DM_MODULE
#endif /* lib90_module */

#ifdef lib90c_module
#define PMP_DM_MODULE
#endif /* lib90c_module */

#ifdef lib90l_module
#define PMP_DM_MODULE
#endif /* lib90l_module */

#ifdef lib90s_module
#define PMP_DM_MODULE
#endif /* lib90s_module */

#ifdef lib92_module
#define PMP_DM_MODULE
#endif /* lib92_module */

#ifdef lib92l_module
#define PMP_DM_MODULE
#endif /* lib92l_module */

#ifdef lib92s_module
#define PMP_DM_MODULE
#endif /* lib92s_module */

#ifdef libfsk_module
#define PMP_DM_MODULE
#endif /* libfsk_module */

#ifdef libpcm_module
#define PMP_DM_MODULE
#endif /* libpcm_module */

#ifdef libph2_module
#define PMP_DM_MODULE
#endif /* libph2_module */

#ifdef libph2p_module
#define PMP_DM_MODULE
#endif /* libph2p_module */

#ifdef sta34_module
#define PMP_DM_MODULE
#endif /* sta34_module */

#ifdef sta34f_module
#define PMP_DM_MODULE
#endif /* sta34f_module */

#ifdef staph2_module
#define PMP_DM_MODULE
#endif /* staph2_module */

#ifdef state22_module
#define PMP_DM_MODULE
#endif /* state22_module */

#ifdef state32_module
#define PMP_DM_MODULE
#endif /* state32_module */

#ifdef state90_module
#define PMP_DM_MODULE
#endif /* state90_module */

#ifdef state92_module
#define PMP_DM_MODULE
#endif /* state92_module */

#ifdef statefsk_module
#define PMP_DM_MODULE
#endif /* statefsk_module */

#ifdef trellis_module
#define PMP_DM_MODULE
#endif /* trellis_module */

/* PMP_FM */
#ifdef lib17_module
#define PMP_FM_MODULE
#endif /* lib17_module */

#ifdef libfax_module
#define PMP_FM_MODULE
#endif /* libfax_module */

#ifdef state17_module
#define PMP_FM_MODULE
#endif /* state17_module */

#ifdef statefax_module
#define PMP_FM_MODULE
#endif /* statefax_module */

/* PMP_AUTO */
#ifdef libauto_module
#define PMP_AUTO_MODULE
#endif /* libauto_module */

#ifdef stateaut_module
#define PMP_AUTO_MODULE
#endif /* stateaut_module */

/* PMP_TEL */
#ifdef g168_module
#define PMP_TEL_MODULE
#endif /* g168_module */

#ifdef libspk_module
#define PMP_TEL_MODULE
#endif /* libspk_module */

#ifdef libtel_module
#define PMP_TEL_MODULE
#endif /* libtel_module */

/* PMP_SPCH */
#ifdef g711_module
#define PMP_SPCH_MODULE
#endif /* g711_module */

#ifdef g722_module
#define PMP_SPCH_MODULE
#endif /* g722_module */

#ifdef g723_module
#define PMP_SPCH_MODULE
#endif /* g723_module */

#ifdef g726_module
#define PMP_SPCH_MODULE
#endif /* g726_module */

#ifdef g729ab_module
#define PMP_SPCH_MODULE
#endif /* g729ab_module */

#ifdef ilbc_module
#define PMP_SPCH_MODULE
#endif /* ilbc_module */

#ifdef libspch_module
#define PMP_SPCH_MODULE
#endif /* libspch_module */

#ifdef melp_module
#define PMP_SPCH_MODULE
#endif /* melp_module */

#ifdef melp54_module
#define PMP_SPCH_MODULE
#endif /* melp54_module */

#ifdef melp55_module
#define PMP_SPCH_MODULE
#endif /* melp55_module */

#ifdef melp64_module
#define PMP_SPCH_MODULE
#endif /* melp64_module */

#ifdef statespc_module
#define PMP_SPCH_MODULE
#endif /* statespc_module */

/* PMP_DATA */
#ifdef libisdn_module
#define PMP_DATA_MODULE
#endif /* libisdn_module */

#ifdef sart_module
#define PMP_DATA_MODULE
#endif /* sart_module */

/* PMP_DBG */
#ifdef debug_module
#define PMP_DBG_MODULE
#endif /* debug_module */

#ifdef dint_module
#define PMP_DBG_MODULE
#endif /* dint_module */

#ifdef dspbios_module
#define PMP_DBG_MODULE
#endif /* dspbios_module */

/* PMP_MISC */
#ifdef customer_module
#define PMP_MISC_MODULE
#endif /* customer_module */

#ifdef hw_module
#define PMP_MISC_MODULE
#endif /* hw_module */

#ifdef hw_dspic_module
#define PMP_MISC_MODULE
#endif /* hw_dspic_module */

#ifdef linux_module
#define PMP_MISC_MODULE
#endif /* linux_module */

#ifdef radio_module
#define PMP_MISC_MODULE
#endif /* radio_module */

#ifdef radiofsk_module
#define PMP_MISC_MODULE
#endif /* radiofsk_module */

#ifdef radiofm_module
#define PMP_MISC_MODULE
#endif /* radiofm_module */

#if defined (PMP_FG_MODULE) || defined (PMP_DM_MODULE) || defined (PMP_FM_MODULE) || defined (PMP_AUTO_MODULE) || defined (PMP_TEL_MODULE) || defined (PMP_SPCH_MODULE) || defined (PMP_DATA_MODULE) || defined (PMP_DBG_MODULE) || defined (PMP_MISC_MODULE)
#define PMP_MODULE_GROUP
#endif

/* ************************************************************************* */
/*
 *	SPECIAL Module Group has no assignments
 */

/* SPECIAL */
#ifdef boot_module
#endif /* boot_module */

#ifdef data_module
#endif /* data_module */

#ifdef flash_module
#endif /* flash_module */

#ifdef include_module
#endif /* include_module */

#ifdef symbol_module
#endif /* symbol_module */

#ifdef system_module
#endif /* system_module */

/* ************************************************************************* */

#endif /* _SYSTEM_MODULE_H */
