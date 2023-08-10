
/* Include the main linker setup file */
-l "link.cmd"			
			
/* Now group the Tachy B application's uninitialized variable sections. */
/* In com_MainTask(), the start and size are used to zero out uninitialized
/* variables as ANSI C specifies. */


SECTIONS {
		.appUninitializedVars: 		 
			RUN_START(_run_start_of_appUninitializedVars), 
			SIZE(_size_of_appUninitializedVars), load = SDRAM, align(4)			 
			{ 
			
				/* For each app, put the aim, fsm, uim files here */ 
				
				
				/* TACHYB */
				
				aim_7230.obj(.bss)
				aim_7232.obj(.bss)
				aim_7274.obj(.bss)
				aim_7274episodes.obj(.bss)
				aim_7277.obj(.bss)
				aim_7278.obj(.bss)
				aim_isp.obj(.bss)
				aim_mi3.obj(.bss)
									
				/* AIM */
															
				aim_deviceLog.obj(.bss)
				aim_gem.obj(.bss)
				aim_general.obj(.bss)
				aim_stdb.obj(.bss)
				aim_tachylog.obj(.bss)
				
				/* FSM */
				
				fsm_7274episodes.obj(.bss)
				fsm_7277.obj(.bss)		
				fsm_encrypt.obj(.bss)		
				fsm_file.obj(.bss)	
				fsm_gem.obj(.bss)
				fsm_pbfr.obj(.bss)										
				fsm_tachylog.obj(.bss)
				itoa.obj(.bss)	
				
				/* UIM */
				
				uim_ui.obj(.bss)														

			} = 0
}

SECTIONS {

		.cspy_consts: 		 
			RUN_START(_run_start_of_cspy_consts), 
			SIZE(_size_of_cspy_consts), load = SDRAM, align(0x20000)			 
			{ 
				aim_cspy.obj (.const)
			}
}


