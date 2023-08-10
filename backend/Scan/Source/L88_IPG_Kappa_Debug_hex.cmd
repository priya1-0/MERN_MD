L88_IPG_Kappa_Debug\2490G_Kappa.out       /* Input COFF file */
-m2                        /* Select Motorola-S1 */
-boot                      /* Place all initialized sections in image */
-map 2490G_Kappa_hex.map   /* Name hex utility map file */
-parallel16                /* Set Flash system memory width */
-v5510:2                   /* Set processor type */
-o 2490G_Kappa.hex            /* Name hex output file */

/* PLL Register for C5501 */
-reg_config 0x1C8C, 0x8001
-reg_config 0x1C8E, 0x8001
-reg_config 0x1C90, 0x8003

/* EMIF Registers for the C5501 */
-reg_config 0x0800, 0x00E0
-reg_config 0x0801, 0x0002
-reg_config 0x0804, 0x8411
-reg_config 0x0805, 0x2112
-reg_config 0x0808, 0xFF33
-reg_config 0x0809, 0xFFFF
-reg_config 0x0824, 0x0000
-reg_config 0x0825, 0x0000
-reg_config 0x0828, 0x0000
-reg_config 0x0829, 0x0000
-reg_config 0x080E, 0x0927
-reg_config 0x080F, 0x0000
-reg_config 0x0810, 0x45B7
-reg_config 0x0811, 0x0005
-reg_config 0x080C, 0x5000
-reg_config 0x080D, 0x4751

ROMS
{
	PAGE 0 : ROM : o=0x000000, l=0x200000
}

