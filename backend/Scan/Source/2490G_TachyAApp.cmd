
/* Include the main linker setup file */
-l "link.cmd"			
			
/* Now group the application's uninitialized variable sections. */
/* In com_MainTask(), the start and size are used to zero out uninitialized
/* variables as ANSI C specifies. */

SECTIONS {
		.appUninitializedVars: 		 
			RUN_START(_run_start_of_appUninitializedVars), 
			SIZE(_size_of_appUninitializedVars), load = SDRAM, align(4)			 
			{ 
			
				/* For each app, put the aim, fsm, uim files here */ 
				
				
				/* TACHYB */
				
				aim_7227.obj(.bss)
				aim_7229.obj(.bss)
				aim_7231.obj(.bss)
				aim_7271.obj(.bss)
				aim_7272.obj(.bss)
				aim_7273.obj(.bss)
				aim_7275.obj(.bss)
				aim_7290.obj(.bss)
									
				/* AIM */
															
				aim_deviceLog.obj(.bss)
				aim_gem.obj(.bss)
				aim_general.obj(.bss)
				aim_stdb.obj(.bss)
				aim_tachylog.obj(.bss)
				
				aim_tlma.obj(.bss)
				
				/* FSM */
				
				fsm_encrypt.obj(.bss)		
				fsm_file.obj(.bss)	
				fsm_gem.obj(.bss)
				fsm_pbfr.obj(.bss)										
				fsm_tachylog.obj(.bss)
				itoa.obj(.bss)	
				
				/* UIM */
				
				uim_ui.obj(.bss)														


			} = 0x00
}



