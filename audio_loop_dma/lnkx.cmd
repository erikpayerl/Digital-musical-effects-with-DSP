-stack 		0x1000   /* PRIMARY STACK SIZE    */
-sysstack	0x1000   /* SECONDARY STACK SIZE  */
-heap           0x3F80   /* HEAP AREA SIZE        */  

MEMORY
{
    MMR     (RW) : origin = 0000000h length = 0000C0h /* MMRs */
    VEC     (RX) : origin = 00000C0h length = 000300h /* on-chip ROM vectors */
    DARAM   (RW) : origin = 0000400h length = 00FC00h /* on-chip DARAM  */
    /*SARAM   (RW) : origin = 0010000h length = 040000h /* on-chip SARAM  */
    SARAM   (RW) : origin = 0x10000, len = 0x3df00
    /*PAGE 0: SARAM31: origin = 0x4e000, len = 0x2000*/
}
 
 
SECTIONS
{
    vectors     : > VEC    ALIGN = 256
    .text       : > SARAM  ALIGN = 4
    .stack      : > SARAM  ALIGN = 4
    .sysstack   : > SARAM  ALIGN = 4
    .data       : > SARAM
    .bss        : > SARAM, fill = 0
    .cinit      : > SARAM
    .const      : > SARAM
    .sysmem 	: > DARAM
    .cio    	: > DARAM
    .switch     : > DARAM
    
    /* User defined */
    data_br_buf : > DARAM /*ALIGN = 512 /* 2^9 = 512 , Aligned to addr with 9 least-sig zeros */
    cmplxBuf    : > DARAM
    scratch_buf : > DARAM
    
    dbuffer : > DARAM
    coeffs      : > DARAM
}

/* C5535 HWAFFT ROM table addresses */
_hwafft_br       = 0x00fefe9c;
_hwafft_8pts     = 0x00fefeb0;
_hwafft_16pts    = 0x00feff9f;
_hwafft_32pts    = 0x00ff00f5;
_hwafft_64pts    = 0x00ff03fe;
_hwafft_128pts   = 0x00ff0593;
_hwafft_256pts   = 0x00ff07a4;
_hwafft_512pts   = 0x00ff09a2;
_hwafft_1024pts  = 0x00ff0c1c;