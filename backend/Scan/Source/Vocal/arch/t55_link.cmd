
//vd - warning, this #define may be ignored
//define TAC_RADIO_FLASH		// Special build for flash memory execution

//vd DO_FAX_T38 conditional use should be considered as temporary

/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* Include the file list */
#include "mst_link.rsp"

/* ************************************************************************* */


/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

/* Include the proper libraries */

-lcsl5502x.lib

/*- No longer needed? -*/
/*- -lcsl5502x.lib -*/


/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */
/* ************************************************************************* */

#define DARAM_U	DARAM	/* Uninitialized Data/Stack */
#define DARAM_I	DARAM	/* Code or Initialized Data */

 
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

	.sect_bulk_int			>	SDRAM_5		PAGE 0, align 0x2000

/* ************************************************************************* */




			
/* ************************************************************************* */



/* ************************************************************************* */

	.isr_code:	load = SDRAM, run = DARAM_VOC, align (4),
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
	.text_int				>	DARAM_I		PAGE 0
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

	.vocal_data_store		>	VOC_STORE	align(4)

	.vocal_uninit_int		>	DARAM_VOC	align(4),
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
//		"link/general/precsine.obj"(.const)	// uses .sect_sine_table instead
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

	.rate_conv_coefs		>	DARAM		PAGE 0
	.sect_sine_table		>	DARAM		PAGE 0
	.bit_rev				>	DARAM		PAGE 0
			
	.internal_routines		>	DARAM		PAGE 0
	.bss_btlz				>	SDRAM		PAGE 0
	.reset_code				>	DARAM		PAGE 0
			
	.sect_mbuf				>	SDRAM_4		PAGE 0
	.sect_fblk				>	SDRAM_10	PAGE 0		

/* ************************************************************************* */

	UNION					>	DARAM_VOC
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

	.v34_bss				>	DARAM		PAGE 0	/* Global & static vars */
	{
		*(.cmn_parms)
		*(.omc_parms)
	}
	
GROUP 	: run				>	TREL_SECT
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

	.const					>	SDRAM_1		PAGE 0
	.sect_state				>	SDRAM_1		PAGE 0
	.bss					>>	SDRAM_1 |
								SDRAM_2 |
								SDRAM_4 |
								SDRAM_5 |
								SDRAM_6 |
								SDRAM_7 |
								SDRAM_8

	.switch					>	SDRAM		PAGE 0	/* Switch statement tables */
	.cinit					>	SDRAM_9		PAGE 0	/* Auto-initialization tables */
	.pinit					>	SDRAM		PAGE 0	/* Initialization fn tables */
	.text					>	SDRAM		PAGE 0	/* Code */

/* ************************************************************************* */


/* ************************************************************************* */


/* ************************************************************************* */

	.ioport					>	0x0000		PAGE 1
}
