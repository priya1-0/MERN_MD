
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
				
				
				/* KAPPA */
				
				aim_enpulse.obj(.bss)
				aim_kappa.obj(.bss)
				aim_kdr700.obj(.bss)
				aim_KDR900.obj(.bss)

									
				/* AIM */
															
				/* (None) */
				
				/* FSM */

				fsm_encrypt.obj(.bss)		
				fsm_file.obj(.bss)	
				fsm_kappa.obj(.bss) /* In KAPPA directory */
				fsm_pbfr.obj(.bss)										
				itoa.obj(.bss)	
				
				/* UIM */
				
				uim_ui.obj(.bss)														


			} = 0
}



