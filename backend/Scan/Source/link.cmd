/************************************************************************
*
* MODULE: link.cmd.c
*
* OWNER: 
*
* $Revision$
*
* $Date$
*
* $RCSfile$
*
* DESCRIPTION: This file controls the linking process.
*
*************************************************************************/

/* PLEXUS ADDED */
/* include CDB-generated link command file */
-l "2490Gcfg.cmd"
/* END PLEXUS ADDED - note: more additions below */

/* ************************************************************************* */

"Vocal/objects/mdm/main.obj"
"Vocal/objects/mdm/mdm.obj"
"Vocal/objects/support/print.obj"
"Vocal/objects/support/support.obj"
"Vocal/objects/support/serial.obj"
"Vocal/objects/support/time.obj"
"Vocal/objects/general/random.obj"
"Vocal/objects/general/divide.obj"
"Vocal/objects/general/precsine.obj"
"Vocal/objects/general/biquad.obj"
"Vocal/objects/general/sqroot.obj"
"Vocal/objects/general/log.obj"
"Vocal/objects/general/alog.obj"
"Vocal/objects/general/db_conv.obj"
"Vocal/objects/general/inttwo.obj"
"Vocal/objects/general/arctan.obj"
"Vocal/objects/general/dsp.obj"
"Vocal/objects/general/longmult.obj"
"Vocal/objects/general/clearbuf.obj"
"Vocal/objects/general/exponent.obj"
"Vocal/objects/sys/timer.obj"
"Vocal/objects/pump/ti55xdrv.obj"
"Vocal/objects/pump/interrpt.obj"
"Vocal/objects/pump/tiint.obj"
"Vocal/objects/pump/boot.obj"
"Vocal/objects/pump/fgmain.obj"
"Vocal/objects/pump/init.obj"
"Vocal/objects/pump/cleanup.obj"
"Vocal/objects/pump/hwinit.obj"
"Vocal/objects/pump/initscal.obj"
"Vocal/objects/pump/initcnst.obj"
"Vocal/objects/pump/initparm.obj"
"Vocal/objects/pump/mgmain.obj"
"Vocal/objects/kernel/fgtimers.obj"
"Vocal/objects/kernel/fgstates.obj"
"Vocal/objects/kernel/fgthread.obj"
"Vocal/objects/kernel/fgthrpkd.obj"
"Vocal/objects/kernel/fginit.obj"
"Vocal/objects/state/main.obj"
"Vocal/objects/state/v14v54.obj"
"Vocal/objects/state/ph2.obj"
"Vocal/objects/lib/ratecnv!.obj"
"Vocal/objects/lib/ratecnv.obj"
"Vocal/objects/lib/ratestub.obj"
"Vocal/objects/lib/bit8inv.obj"
"Vocal/objects/lib/bit8inv!.obj"
"Vocal/objects/lib/smplcnt!.obj"
"Vocal/objects/lib/smplcnt.obj"
"Vocal/objects/lib/power!.obj"
"Vocal/objects/lib/power.obj"
"Vocal/objects/sart/baud!.obj"
"Vocal/objects/sart/lineif!.obj"
"Vocal/objects/sart/lineif.obj"
"Vocal/objects/sart/hdlc.obj"
"Vocal/objects/sart/v14.obj"
"Vocal/objects/customer/cx077a.obj"
"Vocal/objects/customer/netdump.obj"
"Vocal/objects/dteif/dte5501.obj" 
"Vocal/objects/libauto/txtone.obj"
"Vocal/objects/libauto/txtone!.obj"
"Vocal/objects/libauto/tonedt.obj"
"Vocal/objects/libauto/tonedt!.obj"
"Vocal/objects/lib/v24.obj"
"Vocal/objects/lib34n/v34init.obj"
"Vocal/objects/lib34n/in_ph12.obj"
"Vocal/objects/lib34n/frames@.obj"
"Vocal/objects/lib34n/v34n@.obj"
"Vocal/objects/state/v34aaa.obj"
"Vocal/objects/state/v34ooo.obj"
"Vocal/objects/lib/infilt!.obj"
"Vocal/objects/lib/infilt.obj"
"Vocal/objects/lib/agcup.obj"
"Vocal/objects/lib/btrec.obj"
"Vocal/objects/lib/clamps.obj"
"Vocal/objects/lib/clamps!.obj"
"Vocal/objects/lib/clock.obj"
"Vocal/objects/lib/clock!.obj"
"Vocal/objects/lib34/dcd!.obj"
"Vocal/objects/lib34/dcd.obj"
"Vocal/objects/lib34/sart!.obj"
"Vocal/objects/lib34/sart.obj"
"Vocal/objects/state/rlsd.obj"
"Vocal/objects/lib32/v32dsc!.obj"
"Vocal/objects/lib32/v32dsc.obj"
"Vocal/objects/lib32/v32scr!.obj"
"Vocal/objects/lib32/v32scr.obj"
"Vocal/objects/lib/vxxout.obj"
"Vocal/objects/lib/agcup!.obj"
"Vocal/objects/lib/btrec!.obj"
"Vocal/objects/lib/dec4!.obj"
"Vocal/objects/lib/dec4.obj"
"Vocal/objects/lib/difdec!.obj"
"Vocal/objects/lib/difdec.obj"
"Vocal/objects/lib/difenc!.obj"
"Vocal/objects/lib/difenc.obj"
"Vocal/objects/lib/equal!.obj"
"Vocal/objects/lib/equal.obj"
"Vocal/objects/lib/ptloop!.obj"
"Vocal/objects/lib/ptloop.obj"
"Vocal/objects/lib/rxintp!.obj"
"Vocal/objects/lib/rxintp.obj"
"Vocal/objects/lib/seqgen!.obj"
"Vocal/objects/lib/seqgen.obj"
"Vocal/objects/lib/trod!.obj"
"Vocal/objects/lib/trod.obj"
"Vocal/objects/lib/txmask!.obj"
"Vocal/objects/lib/txmask.obj"
"Vocal/objects/lib/vxxdem!.obj"
"Vocal/objects/lib/vxxdem.obj"
"Vocal/objects/lib/vxxmod!.obj"
"Vocal/objects/lib/vxxmod.obj"
"Vocal/objects/lib/vxxmod@.obj"
"Vocal/objects/lib/vxxsta.obj"
"Vocal/objects/lib/vxxsta!.obj"
"Vocal/objects/lib32/notch!.obj"
"Vocal/objects/lib32/notch.obj"
"Vocal/objects/lib32/seqdet!.obj"
"Vocal/objects/lib32/seqdet.obj"
"Vocal/objects/libfsk/fskdec!.obj"
"Vocal/objects/libfsk/fskdec.obj"
"Vocal/objects/libfsk/fskdem!.obj"
"Vocal/objects/libfsk/fskdem.obj"
"Vocal/objects/libfsk/fskmap!.obj"
"Vocal/objects/libfsk/fskmap.obj"
"Vocal/objects/libfsk/fskmod!.obj"
"Vocal/objects/libfsk/fskmod.obj"
"Vocal/objects/libfsk/fskout.obj"
"Vocal/objects/libfsk/fskout!.obj"
"Vocal/objects/libfsk/ansdet!.obj"
"Vocal/objects/libfsk/ansdet.obj"
"Vocal/objects/sart/v8frame!.obj"
"Vocal/objects/sart/v8frame.obj"
"Vocal/objects/sart/v8_v14!.obj"
"Vocal/objects/sart/v8_v14.obj"
"Vocal/objects/state/ph1.obj"
"Vocal/objects/statefsk/v8org.obj"
"Vocal/objects/libph2/ph2btrk!.obj"
"Vocal/objects/libph2/ph2btrk.obj"
"Vocal/objects/libph2/ph2cnv!.obj"
"Vocal/objects/libph2/ph2cnv.obj"
"Vocal/objects/libph2/ph2dec!.obj"
"Vocal/objects/libph2/ph2dec.obj"
"Vocal/objects/libph2/ph2dem!.obj"
"Vocal/objects/libph2/ph2dem.obj"
"Vocal/objects/libph2/ph2eye!.obj"
"Vocal/objects/libph2/ph2eye.obj"
"Vocal/objects/libph2/ph2inf!.obj"
"Vocal/objects/libph2/ph2inf.obj"
"Vocal/objects/libph2/ph2mod!.obj"
"Vocal/objects/libph2/ph2mod.obj"
"Vocal/objects/libph2/ph2out!.obj"
"Vocal/objects/libph2/ph2out.obj"
"Vocal/objects/libph2/ph2rxbb!.obj"
"Vocal/objects/libph2/ph2rxbb.obj"
"Vocal/objects/libph2/ph2txbb!.obj"
"Vocal/objects/libph2/ph2txbb.obj"
"Vocal/objects/libph2p/ph2anal@.obj"
"Vocal/objects/libph2p/ph2bg.obj"
"Vocal/objects/libph2p/ph2fefo!.obj"
"Vocal/objects/libph2p/ph2fefo.obj"
"Vocal/objects/libph2p/ph2fefop.obj"
"Vocal/objects/libph2p/ph2freq.obj"
"Vocal/objects/libph2p/ph2p!.obj"
"Vocal/objects/libph2p/ph2post.obj"
"Vocal/objects/libph2p/ph2powr!.obj"
"Vocal/objects/libph2p/ph2powr.obj"
"Vocal/objects/libph2p/ph2powrp.obj"
"Vocal/objects/libph2p/ph2rate.obj"
"Vocal/objects/libph2p/ph2thd.obj"
"Vocal/objects/lib34n/ph2info!.obj"
"Vocal/objects/lib34n/ph2info.obj"
"Vocal/objects/lib34n/v34ph2.obj"
"Vocal/objects/lib34n/v34ph2@.obj"
"Vocal/objects/staph2/ph2org.obj"
"Vocal/objects/staph2/helper.obj"
"Vocal/objects/staph2/probtest.obj"
"Vocal/objects/lib34/agcup!.obj"
"Vocal/objects/lib34/btrec!.obj"
"Vocal/objects/lib34/equal!.obj"
"Vocal/objects/lib34/equal.obj"
"Vocal/objects/lib34/ptloop!.obj"
"Vocal/objects/lib34/ptloop.obj"
"Vocal/objects/lib34/rxintp!.obj"
"Vocal/objects/lib34/rxintp.obj"
"Vocal/objects/lib34/seqgen!.obj"
"Vocal/objects/lib34/seqgen.obj"
"Vocal/objects/lib34/vxxdem!.obj"
"Vocal/objects/lib34/vxxdem.obj"
"Vocal/objects/lib34/vxxmod!.obj"
"Vocal/objects/lib34/vxxmod.obj"
"Vocal/objects/lib34/vxxout!.obj"
"Vocal/objects/lib34/vxxout.obj"
"Vocal/objects/lib34n/ph4mp!.obj"
"Vocal/objects/lib34n/ph4mp.obj"
"Vocal/objects/lib34n/ph4mp@.obj"
"Vocal/objects/lib34n/v34data.obj"
"Vocal/objects/lib34n/v34ph3.obj"
"Vocal/objects/lib34n/v34ph3@.obj"
"Vocal/objects/lib34l/bulk!.obj"
"Vocal/objects/lib34l/bulk.obj"
"Vocal/objects/lib34l/conver!.obj"
"Vocal/objects/lib34l/conver.obj"
"Vocal/objects/lib34l/echoup!.obj"
"Vocal/objects/lib34l/echoup.obj"
"Vocal/objects/lib34l/notch!.obj"
"Vocal/objects/lib34l/notch.obj"
"Vocal/objects/lib34l/preeq!.obj"
"Vocal/objects/lib34l/preeq.obj"
"Vocal/objects/lib34l/ratdet!.obj"
"Vocal/objects/lib34l/ratdet.obj"
"Vocal/objects/lib34l/seqdet!.obj"
"Vocal/objects/lib34l/seqdet.obj"
"Vocal/objects/lib34l/v34dsc!.obj"
"Vocal/objects/lib34l/v34dsc.obj"
"Vocal/objects/lib34l/v34ftr!.obj"
"Vocal/objects/lib34l/v34ftr.obj"
"Vocal/objects/lib34l/v34l!.obj"
"Vocal/objects/lib34l/v34map!.obj"
"Vocal/objects/lib34l/v34map.obj"
"Vocal/objects/lib34l/v34ren!.obj"
"Vocal/objects/lib34l/v34ren.obj"
"Vocal/objects/lib34l/v34ret!.obj"
"Vocal/objects/lib34l/v34ret.obj"
"Vocal/objects/lib34l/v34scr!.obj"
"Vocal/objects/lib34l/v34scr.obj"
"Vocal/objects/lib34l/v34syn!.obj"
"Vocal/objects/lib34l/v34syn.obj"
"Vocal/objects/lib34l/v34syn@.obj"
"Vocal/objects/lib34l/v34trn!.obj"
"Vocal/objects/lib34l/v34trn.obj"
"Vocal/objects/lib34h/v34anl.obj"
"Vocal/objects/lib34h/v34dec.obj"
"Vocal/objects/lib34h/v34dic.obj"
"Vocal/objects/lib34h/v34enc.obj"
"Vocal/objects/lib34h/v34eye.obj"
"Vocal/objects/lib34h/v34h!.obj"
"Vocal/objects/lib34h/v34h@.obj"
"Vocal/objects/lib34h/v34param.obj"
"Vocal/objects/lib34h/v34parse.obj"
"Vocal/objects/lib34h/v34shape.obj"
"Vocal/objects/lib34h/v34shell.obj"
"Vocal/objects/lib34h/v34trde.obj"
"Vocal/objects/lib34h/v34tren.obj"
"Vocal/objects/lib34n/v34ph4.obj"
"Vocal/objects/lib34l/phroll!.obj"
"Vocal/objects/lib34/testmse.obj"
"Vocal/objects/sta34/v34ans.obj"
"Vocal/objects/sta34/v34org.obj"
"Vocal/objects/sta34/v34agc.obj"
"Vocal/objects/sta34/v34btr.obj"
"Vocal/objects/sta34/v34ecc.obj"
"Vocal/objects/sta34/v34eqc.obj"
"Vocal/objects/sta34/v34mse.obj"
"Vocal/objects/sta34/v34mse@.obj"
"Vocal/objects/sta34/v34trn2.obj"
"Vocal/objects/sta34/v34trn2@.obj"
"Vocal/objects/sta34/v34run.obj"
"Vocal/objects/libtel/cpstate.obj"
"Vocal/objects/libtel/cptable.obj"
"Vocal/objects/libtel/cpsubs.obj"
"Vocal/objects/libtel/cpdet.obj"
"Vocal/objects/libtel/cpdet!.obj"
"Vocal/objects/libtel/dtmfgen.obj"
"Vocal/objects/libtel/dtmfgen!.obj"
"Vocal/objects/libtel/ringdet.obj"
"Vocal/objects/libtel/ringdet!.obj"
"Vocal/objects/state/callprog.obj"
"Vocal/objects/dteif/dteif.obj"
"Vocal/objects/dteif/process.obj"
"Vocal/objects/bind/bindstd.obj"
"Vocal/objects/v24/v24.obj"
"Vocal/objects/csc/csc.obj"
"Vocal/objects/csc/dte.obj"
"Vocal/objects/csc/response.obj"
"Vocal/objects/csc/command.obj"
"Vocal/objects/csc/action.obj"
"Vocal/objects/csc/dial.obj"
"Vocal/objects/csc/dmdp.obj"
"Vocal/objects/csc/hook.obj"
"Vocal/objects/csc/misc.obj"
"Vocal/objects/csc/shutdown.obj"
"Vocal/objects/csc/fc.obj"
"Vocal/objects/csc/monitor.obj"
"Vocal/objects/csc/itel.obj"
"Vocal/objects/csp/ctl_list.obj"
"Vocal/objects/csp/csp.obj"
"Vocal/objects/csp/dispatch.obj"
"Vocal/objects/csp/process.obj"
"Vocal/objects/csp/t_std.obj"
"Vocal/objects/csp/m_std.obj"
"Vocal/objects/csp/m_sreg.obj"
"Vocal/objects/csp/ampr_v.obj"
"Vocal/objects/omc/common.obj"
"Vocal/objects/omc/dial.obj"
"Vocal/objects/omc/dp.obj"
"Vocal/objects/omc/omc.obj"
"Vocal/objects/omc/monitor.obj"
"Vocal/objects/line/line.obj"
"Vocal/objects/dp/dp.obj"
"Vocal/objects/dp/linkage.obj"
"Vocal/objects/direct/bg.obj"
"Vocal/objects/direct/routines.obj"
"Vocal/objects/line/direct.obj"
"Vocal/objects/buffered/bg.obj"
"Vocal/objects/buffered/buffer.obj"
"Vocal/objects/buffered/routines.obj"
"Vocal/objects/buffered/init.obj"
"Vocal/objects/line/buffer.obj"
"Vocal/objects/lapm/evt_srv.obj"
"Vocal/objects/lapm/bg.obj"
"Vocal/objects/lapm/pkt_brk.obj"
"Vocal/objects/lapm/pkt_ctl.obj"
"Vocal/objects/lapm/fg.obj"
"Vocal/objects/lapm/routines.obj"
"Vocal/objects/lapm/line.obj"
"Vocal/objects/lapm/library.obj"
"Vocal/objects/lapm/queues.obj"
"Vocal/objects/lapm/pkt_rej.obj"
"Vocal/objects/lapm/pkt_rx.obj"
"Vocal/objects/lapm/evt_tbl.obj"
"Vocal/objects/lapm/evt_exec.obj"
"Vocal/objects/lapm/timers.obj"
"Vocal/objects/lapm/pkt_tst.obj"
"Vocal/objects/lapm/pkt_tx.obj"
"Vocal/objects/lapm/pkt_xid.obj"
"Vocal/objects/line/lapmsync.obj"
"Vocal/objects/mnp/bg.obj"
"Vocal/objects/mnp/back_xfr.obj"
"Vocal/objects/mnp/fg.obj"
"Vocal/objects/mnp/interrup.obj"
"Vocal/objects/mnp/line.obj"
"Vocal/objects/mnp/library.obj"
"Vocal/objects/mnp/pkt_la.obj"
"Vocal/objects/mnp/pkt_ld.obj"
"Vocal/objects/mnp/pkt_lna.obj"
"Vocal/objects/mnp/pkt_ln.obj"
"Vocal/objects/mnp/pkt_lr.obj"
"Vocal/objects/mnp/pkt_lt.obj"
"Vocal/objects/mnp/queue_rx.obj"
"Vocal/objects/mnp/queue_tx.obj"
"Vocal/objects/mnp/routines.obj"
"Vocal/objects/mnp/timers.obj"
"Vocal/objects/mnp5/init.obj"
"Vocal/objects/mnp5/subs.obj"
"Vocal/objects/mnp5/encode.obj"
"Vocal/objects/mnp5/decode.obj"
"Vocal/objects/line/mnpasync.obj"
"Vocal/objects/line/mnpcrc16.obj"
"Vocal/objects/line/mnpsync.obj"
"Vocal/objects/detect/routines.obj"
"Vocal/objects/detect/bg.obj"
"Vocal/objects/detect/rx_state.obj"
"Vocal/objects/detect/interrup.obj"
"Vocal/objects/line/detect.obj"
"Vocal/objects/btlz/init.obj"
"Vocal/objects/btlz/subs.obj"
"Vocal/objects/btlz/enc_opt.obj"
"Vocal/objects/btlz/dec_opt.obj"
"Vocal/objects/kernel/event.obj"
"Vocal/objects/kernel/init.obj"
"Vocal/objects/kernel/status.obj"
"Vocal/objects/kernel/bgstates.obj"
"Vocal/objects/kernel/bgtimers.obj"
"Vocal/objects/kernel/bgtasks.obj"
"Vocal/objects/kernel/bginit.obj"
"Vocal/objects/crypto/md5c.obj"
"Vocal/objects/dev/dev.obj"
"Vocal/objects/dev/devcmd.obj"
"Vocal/objects/dev/devparam.obj"
"Vocal/objects/dev/iface.obj"
"Vocal/objects/dev/devmdm.obj"
"Vocal/objects/dev/mdmcmd.obj"
"Vocal/objects/ip/ip.obj"
"Vocal/objects/ip/iphdr.obj"
"Vocal/objects/ip/ipcmd.obj"
"Vocal/objects/ip/domain.obj"
"Vocal/objects/ip/domhdr.obj"
"Vocal/objects/ip/icmp.obj"
"Vocal/objects/ip/icmpcmd.obj"
"Vocal/objects/ip/icmphdr.obj"
"Vocal/objects/ip/icmpmsg.obj"
"Vocal/objects/ip/iproute.obj"
"Vocal/objects/ip/ipsock.obj"
"Vocal/objects/ip/tcpcmd.obj"
"Vocal/objects/ip/tcphdr.obj"
"Vocal/objects/ip/tcpin.obj"
"Vocal/objects/ip/tcpout.obj"
"Vocal/objects/ip/tcpsock.obj"
"Vocal/objects/ip/tcpsubr.obj"
"Vocal/objects/ip/tcptimer.obj"
"Vocal/objects/ip/tcpuser.obj"
"Vocal/objects/ip/udp.obj"
"Vocal/objects/ip/udpcmd.obj"
"Vocal/objects/ip/udphdr.obj"
"Vocal/objects/ip/udpsock.obj"
"Vocal/objects/lansend/account.obj"
"Vocal/objects/lansend/commands.obj"
"Vocal/objects/lansend/debug.obj"
"Vocal/objects/lansend/test.obj"
"Vocal/objects/lansend/config.obj"
"Vocal/objects/lansend/main.obj"
"Vocal/objects/lansend/view.obj"
"Vocal/objects/net/net.obj"
"Vocal/objects/net/af.obj"
"Vocal/objects/net/locsock.obj"
"Vocal/objects/net/netuser.obj"
"Vocal/objects/net/route.obj"
"Vocal/objects/net/sockcmd.obj"
"Vocal/objects/net/socket.obj"
"Vocal/objects/net/sockuser.obj"
"Vocal/objects/net/sockutil.obj"
"Vocal/objects/sys/sys.obj"
"Vocal/objects/sys/alloc.obj"
"Vocal/objects/sys/cmdparse.obj"
"Vocal/objects/sys/serial.obj"
"Vocal/objects/support/network.obj"
"Vocal/objects/sys/files.obj"
"Vocal/objects/sys/filesys.obj"
"Vocal/objects/sys/pathname.obj"
"Vocal/objects/sys/getopt.obj"
"Vocal/objects/sys/kernel.obj"
"Vocal/objects/sys/ksubr.obj"
"Vocal/objects/sys/mbuf.obj"
"Vocal/objects/sys/misc.obj"
"Vocal/objects/sys/ti.obj"
"Vocal/objects/sys/session.obj"
"Vocal/objects/sys/stdio.obj"
"Vocal/objects/sys/string.obj"
"Vocal/objects/sys/ttydrvr.obj"
"Vocal/objects/term/term.obj"
"Vocal/objects/utils/utils.obj"
"Vocal/objects/utils/ping.obj"
"Vocal/objects/utils/httpcli.obj"
"Vocal/objects/wan/wan.obj"
"Vocal/objects/wan/ppp.obj"
"Vocal/objects/wan/pppchap.obj"
"Vocal/objects/wan/pppcmd.obj"
"Vocal/objects/wan/pppfsm.obj"
"Vocal/objects/wan/pppipcp.obj"
"Vocal/objects/wan/ppplcp.obj"
"Vocal/objects/wan/ppppap.obj"
"Vocal/objects/wan/slhc.obj"


/* Include the proper libraries */
-lcsl5502x.lib

SECTIONS  
{
	/* PLEXUS START*/	
	.coeffs :  		{} > DARAM3 PAGE 0  /* Must be different than .tbmData! (shared union below)*/
	.tbmExtData:    {} > SDRAM  PAGE 0
	.tbmExtCode:	{} > SDRAM  PAGE 0
		
	/*
	** This union exists to allow DARAM to be shared amongst
	** modules that are active at different, distinct points
	** in time.
	*/	
	UNION  run = /*>*/ DARAM2 PAGE 0
	{
		/* Telemetry A Rx Code/Data */
		GROUP 
		{			
			.tam_rx_text:
			LOAD_START(_load_start_of_tacode), RUN_START(_run_start_of_tacode),
			SIZE(_size_of_tacode), load = SDRAM, align(2)  
			{
				tam_ReceiveCommon.obj(.tam_rx_text)
			}
			
			.tam_rx_data:
			RUN_START(_run_start_of_tadata),
			SIZE(_size_of_tadat) 
			{
				tam_ReceiveCommon.obj(.tam_rx_data)
			}
		}		

		/* Telemetry B Code/Constants/Data */
		GROUP 
		{
			.tbmCode: 		 
			LOAD_START(_load_start_of_tbcode), RUN_START(_run_start_of_tbcode), 
			SIZE(_size_of_tbcode), load = SDRAM, align(4)			 
			{ 
				fir2.obj(.text)
				tbm_rx.obj(.text)
				tbm_rcv.obj(.text)
				tbm_tx.obj(.text)
				tbm_trx.obj(.text)
				craw.obj(.text)
				maxvec.obj(.text)
				tbm_timer.obj(.text)
				tbm_events.obj(.text)
				tbm_queue.obj(.text)
				tbm_fsm.obj(.text)
				tbm_channel.obj(.text)
			} 
			
			.tbmConst:
			LOAD_START(_load_start_of_tbconst), RUN_START(_run_start_of_tbconst), 
			SIZE(_size_of_tbconst), load = SDRAM, align(4) 
			{				
				tbm_trx.obj(.const)
				tbm_rcv.obj(.const)
				tbm_tx.obj(.const)	
				tbm_fsm.obj(.const)
			}
			
			/* Telemetry B Data */
			.tbmData: 
			RUN_START(_run_start_of_tbdata), SIZE(_size_of_tbdata) 
			{
				tbm_main.obj(.bss)
				tbm_trx.obj(.bss)
				tbm_rcv.obj(.bss)
				tbm_events.obj(.bss) 
				tbm_timer.obj(.bss)
				tbm_handler.obj(.bss)
			} 			
		}	

		/* SDRAM Test Code */
		GROUP 
		{	
			.sdram_test_text:
			LOAD_START(_load_start_of_sdramtest), RUN_START(_run_start_of_sdramtest),
			SIZE(_size_of_sdramtest), load = SDRAM, align(2) /*DARAM*/
			{
				dbg_TestExternalRam.obj(.sdram_test_code)
			}
		}
	
		/* VOCAL START */
		/* VOCAL GROUP */
		GROUP 
		{
			.isr_code:	load = SDRAM, align (4),
						LOAD_START(_isr_code_load_addr),
						RUN_START(_isr_code_run_addr),
						SIZE(_isr_code_size)
			{
				"Vocal/objects/dteif/dte5501.obj"(.text)
			}
						
			
			.vocal_uninit_int:
						LOAD_START(_vocal_uninit_int_load_start),
						SIZE(_vocal_uninit_int_size) 
			{
				"Vocal/objects/mdm/main.obj" (.sys_shared)
				"Vocal/objects/mdm/main.obj" (.dteif_local)
				"Vocal/objects/mdm/main.obj" (.dteif_dteif)
				"Vocal/objects/mdm/main.obj" (.cmn_vars)
				"Vocal/objects/mdm/main.obj" (.cmn_debug)
 				"Vocal/objects/mdm/main.obj" (.cmn_fast)
 				"Vocal/objects/mdm/main.obj" (.cmn_const)
				"Vocal/objects/mdm/main.obj" (.mod_vars)
 				"Vocal/objects/mdm/main.obj" (.mod_fast)
				"Vocal/objects/mdm/main.obj" (.tel_debug)
			}
			
			.vocal_const_int: 
						LOAD = SDRAM , align(4),
						LOAD_START(_vocal_const_int_load_start),
						RUN_START(_vocal_const_int_run_start),
						SIZE(_vocal_const_int_size)
			{
				"Vocal/objects/general/alog.obj"(.const)
				"Vocal/objects/general/arctan.obj"(.const)
				"Vocal/objects/general/log.obj"(.const)
				"Vocal/objects/lib34h/v34tren.obj"(.const)
				"Vocal/objects/lib34l/v34map.obj"(.const)
				"Vocal/objects/lib34h/v34h@.obj"(.const)
				"Vocal/objects/libph2p/ph2post.obj"(.const)
				"Vocal/objects/libph2/ph2inf!.obj"(.const)
				"Vocal/objects/libph2/ph2cnv.obj"(.const)
				"Vocal/objects/libph2p/ph2rate.obj"(.const)
				"Vocal/objects/libph2/ph2out.obj"(.const)
				"Vocal/objects/libph2/ph2mod.obj"(.const)
				"Vocal/objects/libph2p/ph2powr.obj"(.const)
				"Vocal/objects/libph2/ph2dem.obj"(.const)
				"Vocal/objects/libph2p/ph2fefop.obj"(.const)
				"Vocal/objects/lib34h/v34parse.obj" (.const)
				"Vocal/objects/lib34h/v34shape.obj" (.const)
				"Vocal/objects/lib34l/v34ftr.obj" (.const)
				"Vocal/objects/lib34l/v34syn@.obj"(.const)
				*(.rate_conv_coefs)
				*(.sect_sine_table)
				*(.bit_rev)

			}
			
			.trellis_code:
						LOAD = SDRAM, align (4),
						LOAD_START(_trellis_code_load_addr),
						RUN_START(_trellis_code_run_addr),
						SIZE(_trellis_code_size)
			{
				"Vocal/objects/lib34h/v34trde.obj" (.text)
			}

	
			UNION	
			{		
				GROUP 
				{
					.ph2_vars
					.ph2_local
				}
		
				GROUP
				{
					.v34_vars
					.v34_fast
					.v34_stats
					.v34_local
					{ "Vocal/objects/lib34h/v34h!.obj"(.bss) }
				}
			}

			.v34_bss
			{
					*(.cmn_parms)
					*(.omc_parms)
			}
				
			.sect_arrays2D: {
                  "Vocal/objects/mdm/main.obj"(.trellis_2Darray0)
                  "Vocal/objects/mdm/main.obj"(.trellis_2Darray1)
                  "Vocal/objects/mdm/main.obj"(.trellis_old_scores)
                  "Vocal/objects/mdm/main.obj"(.trellis_4Darray)
			}
			.trellis_symbols: {"Vocal/objects/lib34h/v34trde.obj"(.bss)}
		}  /* End Vocal Group */
	} /* End UNION*/

	.circ_v34_tx_decor_buffer > DARAM2 PAGE 0, align (64)
	.tel_vars  > DARAM2 PAGE 0
	.v34_debug > SDRAM	PAGE 0

	.mod_cnst >	DARAM2	PAGE 0 
	{
		"Vocal/objects/libfsk/fskdem.obj"(.const)
		"Vocal/objects/libtel/cpdet.obj"(.const)
	}
	
	.vocal_data_store > SDRAM_9, align(4)	
	/* VOCAL END */
	
	/* Telemetry B External Data */
	.tbmExtData2: 
	RUN_START(_run_start_of_tbextdata), SIZE(_size_of_tbextdata), align(4) 
	{
		tbm_autoid.obj(.bss)
		tbm_channel.obj(.bss)
		tbm_fsm.obj(.bss)
		tbm_queue.obj(.bss)
		tbm_rx.obj(.bss)
		tbm_tctl.obj(.bss)
		tbm_tx.obj(.bss)
	} > SDRAM

	RamDiskBlock0 :> SDRAM_4
	RamDiskBlock1 :> SDRAM_4
	RamDiskBlock2 :> SDRAM_5
	RamDiskBlock3 :> SDRAM_5
	RamDiskBlock4 :> SDRAM_6
	RamDiskBlock5 :> SDRAM_6

	
	.nwm_file00   :> SDRAM_NWM_FILE00  PAGE 0
	.nwm_file01   :> SDRAM_NWM_FILE01  PAGE 0
	.nwm_file02   :> SDRAM_NWM_FILE02  PAGE 0
	.nwm_file03   :> SDRAM_NWM_FILE03  PAGE 0
	.nwm_file04   :> SDRAM_NWM_FILE04  PAGE 0
	.nwm_file05   :> SDRAM_NWM_FILE05  PAGE 0
	.nwm_file06   :> SDRAM_NWM_FILE06  PAGE 0
	.nwm_file07   :> SDRAM_NWM_FILE07  PAGE 0
	.nwm_file08   :> SDRAM_NWM_FILE08  PAGE 0
	.nwm_file09   :> SDRAM_NWM_FILE09  PAGE 0
	.nwm_file10   :> SDRAM_NWM_FILE10  PAGE 0
	.nwm_file11   :> SDRAM_NWM_FILE11  PAGE 0
	.nwm_file12   :> SDRAM_NWM_FILE12  PAGE 0
	.nwm_file13   :> SDRAM_NWM_FILE13  PAGE 0
	.nwm_file14   :> SDRAM_NWM_FILE14  PAGE 0
	.nwm_file15   :> SDRAM_NWM_FILE15  PAGE 0
	
	.repeatbuffer :> SDRAM_REPEATBUFFER
	.reset_code	  :> DARAM			PAGE 0 /*Matt Bivans said this is removable */
	
	/* DSP/BIOS sections */
    .bss_btlz > SDRAM PAGE 0
	
	.sect_mbuf				>	SDRAM_11	PAGE 0
	.sect_fblk				>	SDRAM_12	PAGE 0		
	
	.const			:> SDRAM_1	PAGE 0
	.sect_state		:> SDRAM_13	PAGE 0
	.bss			>> SDRAM_1 |
				       SDRAM_2 | 	/* bss in external memory */
				       SDRAM_3 | 	/* bss in external memory */
				       SDRAM_4 | 	/* bss in external memory */
				       SDRAM_5 | 	/* bss in external memory */
				       SDRAM_6 | 	/* bss in external memory */
				       SDRAM_7 | 	/* bss in external memory */
				       SDRAM_8 | 	/* bss in external memory */	
				       SDRAM_9 | 	/* bss in external memory */	
				       SDRAM_10 PAGE 0	/* bss in external memory */	

	egmdata			>> SDRAM_1 |
				       SDRAM_2 | 	/* bss in external memory */
				       SDRAM_3 | 	/* bss in external memory */
				       SDRAM_4 | 	/* bss in external memory */
				       SDRAM_5 | 	/* bss in external memory */
				       SDRAM_6 | 	/* bss in external memory */
				       SDRAM_7 | 	/* bss in external memory */
				       SDRAM_8 | 	/* bss in external memory */
				       SDRAM_9 | 	/* bss in external memory */	
				       SDRAM_10 PAGE 0	/* bss in external memory */	


	.switch			:> SDRAM	PAGE 0	/* Switch statement tables */
	.cinit			:> SDRAM	PAGE 0	/* Auto-initialization tables */
	.pinit			:> SDRAM	PAGE 0	/* Initialization fn tables */
	.text			:> SDRAM	PAGE 0	/* Code */
	
    .crc			:> Flash_CRC        /* CRC of the Application Flash */

	.ioport			:> 0x0000		PAGE 1
}

								 																
