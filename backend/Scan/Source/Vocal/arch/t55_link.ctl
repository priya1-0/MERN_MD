/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* Include the file list */

"link/mdm/main.obj"
"link/mdm/mdm.obj"
"link/support/support.obj"
"link/support/print.obj"
"link/support/serial.obj"
"link/support/time.obj"
"link/general/random.obj"
"link/general/divide.obj"
"link/general/precsine.obj"
"link/general/biquad.obj"
"link/general/sqroot.obj"
"link/general/log.obj"
"link/general/alog.obj"
"link/general/db_conv.obj"
"link/general/inttwo.obj"
"link/general/arctan.obj"
"link/general/dsp.obj"
"link/general/longmult.obj"
"link/general/clearbuf.obj"
"link/general/exponent.obj"
"link/sys/timer.obj"
"link/dspbios/plxcfg_c.obj"
"link/dspbios/plxcfg.o"
"link/pump/ti55xdrv.obj"
"link/pump/interrpt.obj"
"link/pump/tiint.obj"
"link/pump/boot.obj"
"link/pump/fgmain.obj"
"link/pump/init.obj"
"link/pump/cleanup.obj"
"link/pump/hwinit.obj"
"link/pump/initscal.obj"
"link/pump/initcnst.obj"
"link/pump/initparm.obj"
"link/pump/mgmain.obj"
"link/kernel/fgtimers.obj"
"link/kernel/fgstates.obj"
"link/kernel/fgthread.obj"
"link/kernel/fgthrpkd.obj"
"link/kernel/fginit.obj"
"link/state/main.obj"
"link/state/v14v54.obj"
"link/state/ph2.obj"
"link/lib/pcmcnv!.obj"
"link/lib/pcmcnv.obj"
"link/lib/ratecnv!.obj"
"link/lib/ratecnv.obj"
"link/lib/ratestub.obj"
"link/lib/bit8inv.obj"
"link/lib/bit8inv!.obj"
"link/lib/smplcnt!.obj"
"link/lib/smplcnt.obj"
"link/lib/power!.obj"
"link/lib/power.obj"
"link/sart/baud!.obj"
"link/sart/lineif!.obj"
"link/sart/lineif.obj"
"link/sart/hdlc.obj"
"link/sart/v14.obj"
"link/customer/cx077a.obj"
"link/customer/cx077b.obj"
"link/customer/netdump.obj"
"link/dteif/dte5501.obj"
"link/libauto/txtone.obj"
"link/libauto/txtone!.obj"
"link/libauto/tonedt.obj"
"link/libauto/tonedt!.obj"
"link/lib/v24.obj"
"link/lib34n/v34init.obj"
"link/lib34n/in_ph12.obj"
"link/lib34n/frames@.obj"
"link/lib34n/v34n@.obj"
"link/state/v34aaa.obj"
"link/state/v34ooo.obj"
"link/lib/infilt!.obj"
"link/lib/infilt.obj"
"link/lib/agcup.obj"
"link/lib/btrec.obj"
"link/lib/clamps.obj"
"link/lib/clamps!.obj"
"link/lib/clock.obj"
"link/lib/clock!.obj"
"link/lib34/dcd!.obj"
"link/lib34/dcd.obj"
"link/lib34/sart!.obj"
"link/lib34/sart.obj"
"link/state/rlsd.obj"
"link/lib32/v32dsc!.obj"
"link/lib32/v32dsc.obj"
"link/lib32/v32scr!.obj"
"link/lib32/v32scr.obj"
"link/lib/vxxout.obj"
"link/lib/agcup!.obj"
"link/lib/btrec!.obj"
"link/lib/dec4!.obj"
"link/lib/dec4.obj"
"link/lib/difdec!.obj"
"link/lib/difdec.obj"
"link/lib/difenc!.obj"
"link/lib/difenc.obj"
"link/lib/equal!.obj"
"link/lib/equal.obj"
"link/lib/ptloop!.obj"
"link/lib/ptloop.obj"
"link/lib/rxintp!.obj"
"link/lib/rxintp.obj"
"link/lib/seqgen!.obj"
"link/lib/seqgen.obj"
"link/lib/trod!.obj"
"link/lib/trod.obj"
"link/lib/txmask!.obj"
"link/lib/txmask.obj"
"link/lib/vxxdem!.obj"
"link/lib/vxxdem.obj"
"link/lib/vxxmod!.obj"
"link/lib/vxxmod.obj"
"link/lib/vxxmod@.obj"
"link/lib/vxxsta.obj"
"link/lib/vxxsta!.obj"
"link/lib32/notch!.obj"
"link/lib32/notch.obj"
"link/lib32/seqdet!.obj"
"link/lib32/seqdet.obj"
"link/libfsk/fskdec!.obj"
"link/libfsk/fskdec.obj"
"link/libfsk/fskdem!.obj"
"link/libfsk/fskdem.obj"
"link/libfsk/fskmap!.obj"
"link/libfsk/fskmap.obj"
"link/libfsk/fskmod!.obj"
"link/libfsk/fskmod.obj"
"link/libfsk/fskout.obj"
"link/libfsk/fskout!.obj"
"link/libfsk/ansdet!.obj"
"link/libfsk/ansdet.obj"
"link/sart/v8frame!.obj"
"link/sart/v8frame.obj"
"link/sart/v8_v14!.obj"
"link/sart/v8_v14.obj"
"link/state/ph1.obj"
"link/statefsk/v8org.obj"
"link/libph2/ph2btrk!.obj"
"link/libph2/ph2btrk.obj"
"link/libph2/ph2cnv!.obj"
"link/libph2/ph2cnv.obj"
"link/libph2/ph2dec!.obj"
"link/libph2/ph2dec.obj"
"link/libph2/ph2dem!.obj"
"link/libph2/ph2dem.obj"
"link/libph2/ph2eye!.obj"
"link/libph2/ph2eye.obj"
"link/libph2/ph2inf!.obj"
"link/libph2/ph2inf.obj"
"link/libph2/ph2mod!.obj"
"link/libph2/ph2mod.obj"
"link/libph2/ph2out!.obj"
"link/libph2/ph2out.obj"
"link/libph2/ph2rxbb!.obj"
"link/libph2/ph2rxbb.obj"
"link/libph2/ph2txbb!.obj"
"link/libph2/ph2txbb.obj"
"link/libph2p/ph2anal@.obj"
"link/libph2p/ph2bg.obj"
"link/libph2p/ph2fefo!.obj"
"link/libph2p/ph2fefo.obj"
"link/libph2p/ph2fefop.obj"
"link/libph2p/ph2freq.obj"
"link/libph2p/ph2p!.obj"
"link/libph2p/ph2post.obj"
"link/libph2p/ph2powr!.obj"
"link/libph2p/ph2powr.obj"
"link/libph2p/ph2powrp.obj"
"link/libph2p/ph2rate.obj"
"link/libph2p/ph2thd.obj"
"link/lib34n/ph2info!.obj"
"link/lib34n/ph2info.obj"
"link/lib34n/v34ph2.obj"
"link/lib34n/v34ph2@.obj"
"link/staph2/ph2org.obj"
"link/staph2/helper.obj"
"link/staph2/probtest.obj"
"link/lib34/agcup!.obj"
"link/lib34/btrec!.obj"
"link/lib34/equal!.obj"
"link/lib34/equal.obj"
"link/lib34/ptloop!.obj"
"link/lib34/ptloop.obj"
"link/lib34/rxintp!.obj"
"link/lib34/rxintp.obj"
"link/lib34/seqgen!.obj"
"link/lib34/seqgen.obj"
"link/lib34/vxxdem!.obj"
"link/lib34/vxxdem.obj"
"link/lib34/vxxmod!.obj"
"link/lib34/vxxmod.obj"
"link/lib34/vxxout!.obj"
"link/lib34/vxxout.obj"
"link/lib34n/ph4mp!.obj"
"link/lib34n/ph4mp.obj"
"link/lib34n/ph4mp@.obj"
"link/lib34n/v34data.obj"
"link/lib34n/v34ph3.obj"
"link/lib34n/v34ph3@.obj"
"link/lib34l/bulk!.obj"
"link/lib34l/bulk.obj"
"link/lib34l/conver!.obj"
"link/lib34l/conver.obj"
"link/lib34l/echoup!.obj"
"link/lib34l/echoup.obj"
"link/lib34l/notch!.obj"
"link/lib34l/notch.obj"
"link/lib34l/preeq!.obj"
"link/lib34l/preeq.obj"
"link/lib34l/ratdet!.obj"
"link/lib34l/ratdet.obj"
"link/lib34l/seqdet!.obj"
"link/lib34l/seqdet.obj"
"link/lib34l/v34dsc!.obj"
"link/lib34l/v34dsc.obj"
"link/lib34l/v34ftr!.obj"
"link/lib34l/v34ftr.obj"
"link/lib34l/v34l!.obj"
"link/lib34l/v34map!.obj"
"link/lib34l/v34map.obj"
"link/lib34l/v34ren!.obj"
"link/lib34l/v34ren.obj"
"link/lib34l/v34ret!.obj"
"link/lib34l/v34ret.obj"
"link/lib34l/v34scr!.obj"
"link/lib34l/v34scr.obj"
"link/lib34l/v34syn!.obj"
"link/lib34l/v34syn.obj"
"link/lib34l/v34syn@.obj"
"link/lib34l/v34trn!.obj"
"link/lib34l/v34trn.obj"
"link/lib34h/v34anl.obj"
"link/lib34h/v34dec.obj"
"link/lib34h/v34dic.obj"
"link/lib34h/v34enc.obj"
"link/lib34h/v34eye.obj"
"link/lib34h/v34h!.obj"
"link/lib34h/v34h@.obj"
"link/lib34h/v34param.obj"
"link/lib34h/v34parse.obj"
"link/lib34h/v34shape.obj"
"link/lib34h/v34shell.obj"
"link/lib34h/v34trde.obj"
"link/lib34h/v34tren.obj"
"link/lib34n/v34ph4.obj"
"link/lib34l/phroll!.obj"
"link/lib34/testmse.obj"
"link/sta34/v34ans.obj"
"link/sta34/v34org.obj"
"link/sta34/v34agc.obj"
"link/sta34/v34btr.obj"
"link/sta34/v34ecc.obj"
"link/sta34/v34eqc.obj"
"link/sta34/v34mse.obj"
"link/sta34/v34mse@.obj"
"link/sta34/v34trn2.obj"
"link/sta34/v34trn2@.obj"
"link/sta34/v34run.obj"
"link/libtel/cpstate.obj"
"link/libtel/cptable.obj"
"link/libtel/cpsubs.obj"
"link/libtel/cpdet.obj"
"link/libtel/cpdet!.obj"
"link/libtel/dtmfgen.obj"
"link/libtel/dtmfgen!.obj"
"link/libtel/ringdet.obj"
"link/libtel/ringdet!.obj"
"link/state/callprog.obj"
"link/dteif/dteif.obj"
"link/dteif/process.obj"
"link/bind/bindstd.obj"
"link/v24/v24.obj"
"link/csc/csc.obj"
"link/csc/dte.obj"
"link/csc/response.obj"
"link/csc/command.obj"
"link/csc/action.obj"
"link/csc/dial.obj"
"link/csc/dmdp.obj"
"link/csc/hook.obj"
"link/csc/misc.obj"
"link/csc/shutdown.obj"
"link/csc/fc.obj"
"link/csc/monitor.obj"
"link/csc/itel.obj"
"link/csp/ctl_list.obj"
"link/csp/csp.obj"
"link/csp/dispatch.obj"
"link/csp/process.obj"
"link/csp/t_std.obj"
"link/csp/m_std.obj"
"link/csp/m_sreg.obj"
"link/csp/ampr_v.obj"
"link/omc/common.obj"
"link/omc/dial.obj"
"link/omc/dp.obj"
"link/omc/omc.obj"
"link/omc/monitor.obj"
"link/line/line.obj"
"link/dp/dp.obj"
"link/dp/linkage.obj"
"link/direct/bg.obj"
"link/direct/routines.obj"
"link/line/direct.obj"
"link/buffered/bg.obj"
"link/buffered/buffer.obj"
"link/buffered/routines.obj"
"link/buffered/init.obj"
"link/line/buffer.obj"
"link/lapm/evt_srv.obj"
"link/lapm/bg.obj"
"link/lapm/pkt_brk.obj"
"link/lapm/pkt_ctl.obj"
"link/lapm/fg.obj"
"link/lapm/routines.obj"
"link/lapm/line.obj"
"link/lapm/library.obj"
"link/lapm/queues.obj"
"link/lapm/pkt_rej.obj"
"link/lapm/pkt_rx.obj"
"link/lapm/evt_tbl.obj"
"link/lapm/evt_exec.obj"
"link/lapm/timers.obj"
"link/lapm/pkt_tst.obj"
"link/lapm/pkt_tx.obj"
"link/lapm/pkt_xid.obj"
"link/line/lapmsync.obj"
"link/mnp/bg.obj"
"link/mnp/back_xfr.obj"
"link/mnp/fg.obj"
"link/mnp/interrup.obj"
"link/mnp/line.obj"
"link/mnp/library.obj"
"link/mnp/pkt_la.obj"
"link/mnp/pkt_ld.obj"
"link/mnp/pkt_lna.obj"
"link/mnp/pkt_ln.obj"
"link/mnp/pkt_lr.obj"
"link/mnp/pkt_lt.obj"
"link/mnp/queue_rx.obj"
"link/mnp/queue_tx.obj"
"link/mnp/routines.obj"
"link/mnp/timers.obj"
"link/mnp5/init.obj"
"link/mnp5/subs.obj"
"link/mnp5/encode.obj"
"link/mnp5/decode.obj"
"link/line/mnpasync.obj"
"link/line/mnpcrc16.obj"
"link/line/mnpsync.obj"
"link/detect/routines.obj"
"link/detect/bg.obj"
"link/detect/rx_state.obj"
"link/detect/interrup.obj"
"link/line/detect.obj"
"link/btlz/init.obj"
"link/btlz/subs.obj"
"link/btlz/enc_opt.obj"
"link/btlz/dec_opt.obj"
"link/kernel/event.obj"
"link/kernel/init.obj"
"link/kernel/status.obj"
"link/kernel/bgstates.obj"
"link/kernel/bgtimers.obj"
"link/kernel/bgtasks.obj"
"link/kernel/bginit.obj"
"link/crypto/md5c.obj"
"link/dev/dev.obj"
"link/dev/devcmd.obj"
"link/dev/devparam.obj"
"link/dev/iface.obj"
"link/dev/devmdm.obj"
"link/dev/mdmcmd.obj"
"link/ip/ip.obj"
"link/ip/iphdr.obj"
"link/ip/ipcmd.obj"
"link/ip/domain.obj"
"link/ip/domhdr.obj"
"link/ip/icmp.obj"
"link/ip/icmpcmd.obj"
"link/ip/icmphdr.obj"
"link/ip/icmpmsg.obj"
"link/ip/iproute.obj"
"link/ip/ipsock.obj"
"link/ip/tcpcmd.obj"
"link/ip/tcphdr.obj"
"link/ip/tcpin.obj"
"link/ip/tcpout.obj"
"link/ip/tcpsock.obj"
"link/ip/tcpsubr.obj"
"link/ip/tcptimer.obj"
"link/ip/tcpuser.obj"
"link/ip/udp.obj"
"link/ip/udpcmd.obj"
"link/ip/udphdr.obj"
"link/ip/udpsock.obj"
"link/lansend/account.obj"
"link/lansend/commands.obj"
"link/lansend/debug.obj"
"link/lansend/test.obj"
"link/lansend/config.obj"
"link/lansend/main.obj"
"link/lansend/view.obj"
"link/net/net.obj"
"link/net/af.obj"
"link/net/locsock.obj"
"link/net/netuser.obj"
"link/net/route.obj"
"link/net/sockcmd.obj"
"link/net/socket.obj"
"link/net/sockuser.obj"
"link/net/sockutil.obj"
"link/sys/sys.obj"
"link/sys/alloc.obj"
"link/sys/cmdparse.obj"
"link/sys/serial.obj"
"link/support/network.obj"
"link/sys/files.obj"
"link/sys/filesys.obj"
"link/sys/pathname.obj"
"link/sys/getopt.obj"
"link/sys/kernel.obj"
"link/sys/ksubr.obj"
"link/sys/mbuf.obj"
"link/sys/misc.obj"
"link/sys/ti.obj"
"link/sys/session.obj"
"link/sys/stdio.obj"
"link/sys/string.obj"
"link/sys/ttydrvr.obj"
"link/term/term.obj"
"link/utils/utils.obj"
"link/utils/ping.obj"
"link/utils/httpcli.obj"
"link/wan/wan.obj"
"link/wan/ppp.obj"
"link/wan/pppchap.obj"
"link/wan/pppcmd.obj"
"link/wan/pppfsm.obj"
"link/wan/pppipcp.obj"
"link/wan/ppplcp.obj"
"link/wan/ppppap.obj"
"link/wan/slhc.obj"

/* ************************************************************************* */


/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* Include the proper libraries */

-lcsl5502x.lib





/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */





/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* SPECIFY THE SECTIONS ALLOCATION INTO MEMORY */

SECTIONS
{

/* ************************************************************************* *
 *																			 *
 *	Internal Memory Allocation - Mostly										 *
 *																			 *
 * ************************************************************************* */

/* ************************************************************************* */



/* ************************************************************************* */

        .sect_bulk_int > SDRAM_5 PAGE 0, align 0x2000

/* ************************************************************************* */





/* ************************************************************************* */



/* ************************************************************************* */

        .isr_code: load = SDRAM, run = DARAM_VOC, align (4),
                                LOAD_START(_isr_code_load_addr),
                                RUN_START(_isr_code_run_addr),
                                SIZE(_isr_code_size)

/* ************************************************************************* */


/* ************************************************************************* */


/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* MINIMUM INTERNAL MEMORY USE */
        .text_int > DARAM PAGE 0
        {
                "link/dteif/dte5501.obj"(.text)
        }

        .trellis_code load = SDRAM, run = DARAM_VOC, align (4),
                LOAD_START(_trellis_code_load_addr),
                RUN_START(_trellis_code_run_addr),
                SIZE(_trellis_code_size)
        {
                "link/lib34h/v34trde.obj" (.text)
        }

        .vocal_data_store > VOC_STORE align(4)

        .vocal_uninit_int > DARAM_VOC align(4),
                LOAD_START(_vocal_uninit_int_load_start),
                SIZE(_vocal_uninit_int_size)
        {
                "link/mdm/main.obj" (.sys_shared)
                "link/mdm/main.obj" (.dteif_local)
                "link/mdm/main.obj" (.cmn_vars)
                "link/mdm/main.obj" (.cmn_const)
                "link/mdm/main.obj" (.cmn_debug)
                "link/mdm/main.obj" (.cmn_fast)
                "link/mdm/main.obj" (.mod_vars)
                "link/mdm/main.obj" (.mod_fast)
                "link/mdm/main.obj" (.tel_debug)
        }

        .vocal_const_int RUN = DARAM_VOC, LOAD = SDRAM_5, align(4),
                LOAD_START(_vocal_const_int_load_start),
                RUN_START(_vocal_const_int_run_start),
                SIZE(_vocal_const_int_size)
        {
                "link/general/alog.obj"(.const)
                "link/general/arctan.obj"(.const)
                "link/general/log.obj"(.const)
                "link/lib34h/v34tren.obj"(.const)
                "link/lib34l/v34map.obj"(.const)
                "link/lib34h/v34h@.obj"(.const)
                "link/libph2p/ph2post.obj"(.const)
                "link/libph2/ph2inf!.obj"(.const)
                "link/libph2/ph2cnv.obj"(.const)
                "link/libph2p/ph2rate.obj"(.const)
                "link/libph2/ph2out.obj"(.const)
                "link/libph2/ph2mod.obj"(.const)
                "link/libph2p/ph2powr.obj"(.const)
                "link/libph2/ph2dem.obj"(.const)
                "link/libph2p/ph2fefop.obj"(.const)
                "link/lib34l/v34syn@.obj"(.const)
        }

        .rate_conv_coefs > DARAM PAGE 0
        .sect_sine_table > DARAM PAGE 0
        .bit_rev > DARAM PAGE 0

        .internal_routines > DARAM PAGE 0
        .bss_btlz > SDRAM PAGE 0
        .reset_code > DARAM PAGE 0

        .sect_mbuf > SDRAM_4 PAGE 0
        .sect_fblk > SDRAM_10 PAGE 0

/* ************************************************************************* */

        UNION > DARAM_VOC
        {
                GROUP {
                        .ph2_vars
                        .ph2_local
                }
                GROUP {
                        .tel_vars
                        .tel_fast
                }
                GROUP
                {
                        .v34_vars
                        .v34_fast
                        { "link/lib34h/v34h!.obj"(.bss) }
                }
        }

        .v34_bss > DARAM PAGE 0 /* Global & static vars */
        {
                *(.cmn_parms)
                *(.omc_parms)
        }

GROUP : run > TREL_SECT
        {
          .sect_arrays2D: {
                  "link\mdm\main.obj"(.trellis_2Darray0)
                  "link\mdm\main.obj"(.trellis_2Darray1)
                  "link\mdm\main.obj"(.trellis_old_scores)
                  "link\mdm\main.obj"(.trellis_4Darray)
          }
          .trellis_symbols: {"link\lib34h\v34trde.obj"(.bss)}
        }

/* ************************************************************************* *
 *																			 *
 *	External Memory Allocation - Mostly										 *
 *																			 *
 * ************************************************************************* */

        .const > SDRAM_1 PAGE 0
        .sect_state > SDRAM_1 PAGE 0
        .bss >> SDRAM_1 |
                                                                SDRAM_2 |
                                                                SDRAM_4 |
                                                                SDRAM_5 |
                                                                SDRAM_6 |
                                                                SDRAM_7 |
                                                                SDRAM_8

        .switch > SDRAM PAGE 0 /* Switch statement tables */
        .cinit > SDRAM_9 PAGE 0 /* Auto-initialization tables */
        .pinit > SDRAM PAGE 0 /* Initialization fn tables */
        .text > SDRAM PAGE 0 /* Code */

/* ************************************************************************* */


/* ************************************************************************* */


/* ************************************************************************* */

        .ioport > 0x0000 PAGE 1
}
