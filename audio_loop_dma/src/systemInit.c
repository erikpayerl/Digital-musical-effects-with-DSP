//////////////////////////////////////////////////////////////////////////////
// DIGITALA MUSIKEFFEKTER MED DSP
// * File name: systemInit.c
// *                                                                          
// * Description:  Initialize board. Resets peripherals and sets PLL to 100Mhz
// *                                                                          
// * Erik Payerl 2014-04-08      
// *            
// *                
// * Copyright (C) 2011 Texas Instruments Incorporated - http://www.ti.com/ 
// * Copyright (C) 2011 Spectrum Digital, Incorporated
// *                                                                          
// *                                                                          
// *  Redistribution and use in source and binary forms, with or without      
// *  modification, are permitted provided that the following conditions      
// *  are met:                                                                
// *                                                                          
// *    Redistributions of source code must retain the above copyright        
// *    notice, this list of conditions and the following disclaimer.         
// *                                                                          
// *    Redistributions in binary form must reproduce the above copyright     
// *    notice, this list of conditions and the following disclaimer in the   
// *    documentation and/or other materials provided with the                
// *    distribution.                                                         
// *                                                                          
// *    Neither the name of Texas Instruments Incorporated nor the names of   
// *    its contributors may be used to endorse or promote products derived   
// *    from this software without specific prior written permission.         
// *                                                                          
// *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS     
// *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT       
// *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR   
// *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT    
// *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,   
// *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT        
// *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,   
// *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY   
// *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT     
// *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE   
// *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.    
// *                                                                         
                                                              
//////////////////////////////////////////////////////////////////////////////

#include "stdio.h"
#include "ezdsp5535.h"
#include "csl_pll.h"

#define SYS_ICR        *(volatile ioport Uint16*)(0x0001)

void systemInit(void)
{
    Uint16 i;
    PLL_Obj pllObj;
    CSL_Status status;
    PLL_Handle hPll;
    PLL_Config *pConfigInfo;
    PLL_Config pllCfg_v2_100MHz    = {0x8BE8, 0x8000, 0x0806, 0x0000};
    
    /* Config Idle control */
    SYS_ICR = 0xFF2E;
    asm(" IDLE");
    
    /* Reset peripherals */
    CSL_FINS(CSL_SYSCTRL_REGS->PSRCR, SYS_PSRCR_COUNT, 0x02);
    CSL_SYSCTRL_REGS->PRCR = 0xfb;
    
    /* Delay for devices to reset */
    for (i=0; i< 200; i++);

    /* Setup PLL */
    status = PLL_init(&pllObj, CSL_PLL_INST_0);
    hPll = (PLL_Handle)(&pllObj);
    PLL_reset(hPll);
    pConfigInfo = &pllCfg_v2_100MHz;

    status = PLL_config (hPll, pConfigInfo);
}
