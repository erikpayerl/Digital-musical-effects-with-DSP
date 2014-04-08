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
}