/*
This code defines dma transfer between aic3204 and ping pong buffers in memory for both left and right 
channels using 4 separate dma channels. 

It is assumed the aic3204 is configured elsewhere and serial data can be sent and retrived from the I2S2 bus. 

Tomas McKelvey
November 2013
 */

#include "csl_dma.h"
#include "csl_intc.h"
#include "aic_dma.h"
#include <stdio.h>
#include <math.h>
#include <tms320.h>
#include <dsplib.h>


/* Reference the start of the interrupt vector table */
extern void VECSTART(void);
/* prototype declaration for ISR function */

extern int isr_count,isr_count_ping,isr_count_pong;

//extern int lms(int x, int y);



/**
 *  \brief  DMA Interrupt Service routine
 *  \param  none
 *  \return none
 */
interrupt void dma_isr(void);

/* Buffers for L/R audio input/receive */
#pragma DATA_ALIGN (dmaPingDstBufLR, 4)
DATA dmaPingDstBufLR[CSL_DMA_BUFFER_SIZE];
#pragma DATA_ALIGN (dmaPongDstBufLR, 4)
DATA dmaPongDstBufLR[CSL_DMA_BUFFER_SIZE];
#pragma DATA_ALIGN (dmaPingDstBufRR, 4)
DATA dmaPingDstBufRR[CSL_DMA_BUFFER_SIZE];
#pragma DATA_ALIGN (dmaPongDstBufRR, 4)
DATA dmaPongDstBufRR[CSL_DMA_BUFFER_SIZE];

/* Declaration of the L/R audio output/send buffers */
#pragma DATA_ALIGN (dmaPingSrcBufLS, 4)
DATA dmaPingSrcBufLS[CSL_DMA_BUFFER_SIZE];
#pragma DATA_ALIGN (dmaPongSrcBufLS, 4)
DATA dmaPongSrcBufLS[CSL_DMA_BUFFER_SIZE];
#pragma DATA_ALIGN (dmaPingSrcBufRS, 4)
DATA dmaPingSrcBufRS[CSL_DMA_BUFFER_SIZE];
#pragma DATA_ALIGN (dmaPongSrcBufRS, 4)
DATA dmaPongSrcBufRS[CSL_DMA_BUFFER_SIZE];

CSL_DMA_Handle 		dmaHandleLS,dmaHandleRS,dmaHandleLR,dmaHandleRR;
CSL_DMA_Config 		dmaConfigLS,dmaConfigRS,dmaConfigLR,dmaConfigRR;
CSL_DMA_Config 		getdmaConfig;

int pingLR,pingRR,pingLS,pingRS;

int tcr2 =0;
CSL_Status 			status;

int pp =0;

/**
 *  \brief  DMA Ping-Pong Mode transfers from DRAM to/from aic3204
 *  \param  none
 *  \return none
 */

int dma_init(void)
{
  
  CSL_DMA_ChannelObj  dmaObjLS,dmaObjRS,dmaObjLR,dmaObjRR;
  
  /*  Left Receive */
  dmaConfigLR.pingPongMode = CSL_DMA_PING_PONG_ENABLE;
  dmaConfigLR.autoMode     = CSL_DMA_AUTORELOAD_ENABLE;
  dmaConfigLR.burstLen     = CSL_DMA_TXBURST_1WORD;
  dmaConfigLR.trigger      = CSL_DMA_EVENT_TRIGGER;
  dmaConfigLR.dmaEvt       = CSL_DMA_EVT_I2S2_RX ;  // or CSL_DMA_EVT_I2S2_TX 
  dmaConfigLR.dmaInt       = CSL_DMA_INTERRUPT_DISABLE; // Use this?
  dmaConfigLR.chanDir      = CSL_DMA_READ; // CSL_DMA_WRITE 
  dmaConfigLR.trfType      = CSL_DMA_TRANSFER_IO_MEMORY;
  dmaConfigLR.dataLen      = CSL_DMA_BUFFER_SIZE * 4;
  dmaConfigLR.srcAddr      = 0x2A28; // I2SRXLT0 
  dmaConfigLR.destAddr     = (Uint32)dmaPingDstBufLR; //

  /*  Right Receive */
  dmaConfigRR.pingPongMode = CSL_DMA_PING_PONG_ENABLE;
  dmaConfigRR.autoMode     = CSL_DMA_AUTORELOAD_ENABLE;
  dmaConfigRR.burstLen     = CSL_DMA_TXBURST_1WORD;
  dmaConfigRR.trigger      = CSL_DMA_EVENT_TRIGGER;
  dmaConfigRR.dmaEvt       = CSL_DMA_EVT_I2S2_RX ;  // or CSL_DMA_EVT_I2S2_TX 
  dmaConfigRR.dmaInt       = CSL_DMA_INTERRUPT_ENABLE; // Use this?
  dmaConfigRR.chanDir      = CSL_DMA_READ; // CSL_DMA_WRITE 
  dmaConfigRR.trfType      = CSL_DMA_TRANSFER_IO_MEMORY;
  dmaConfigRR.dataLen      = CSL_DMA_BUFFER_SIZE * 4;
  dmaConfigRR.srcAddr      = 0x2A2C; // I2SRXRT0 
  dmaConfigRR.destAddr     = (Uint32)dmaPingDstBufRR; //
  
  /*  Left Send */
  dmaConfigLS.pingPongMode = CSL_DMA_PING_PONG_ENABLE;
  dmaConfigLS.autoMode     = CSL_DMA_AUTORELOAD_ENABLE;
  dmaConfigLS.burstLen     = CSL_DMA_TXBURST_1WORD;
  dmaConfigLS.trigger      = CSL_DMA_EVENT_TRIGGER;
  dmaConfigLS.dmaEvt       = CSL_DMA_EVT_I2S2_TX ;  // or CSL_DMA_EVT_I2S2_TX 
  dmaConfigLS.dmaInt       = CSL_DMA_INTERRUPT_DISABLE; // Use this?
  dmaConfigLS.chanDir      = CSL_DMA_WRITE; // CSL_DMA_WRITE 
  dmaConfigLS.trfType      = CSL_DMA_TRANSFER_IO_MEMORY;
  dmaConfigLS.dataLen      = CSL_DMA_BUFFER_SIZE * 4;
  dmaConfigLS.destAddr      = 0x2A08; // I2STXLT0
  dmaConfigLS.srcAddr     = (Uint32)dmaPingSrcBufLS; //

  /*  Right Send */
  dmaConfigRS.pingPongMode = CSL_DMA_PING_PONG_ENABLE;
  dmaConfigRS.autoMode     = CSL_DMA_AUTORELOAD_ENABLE;
  dmaConfigRS.burstLen     = CSL_DMA_TXBURST_1WORD;
  dmaConfigRS.trigger      = CSL_DMA_EVENT_TRIGGER;
  dmaConfigRS.dmaEvt       = CSL_DMA_EVT_I2S2_TX ;  // or CSL_DMA_EVT_I2S2_TX 
  dmaConfigRS.dmaInt       = CSL_DMA_INTERRUPT_DISABLE; // Use this?
  dmaConfigRS.chanDir      = CSL_DMA_WRITE; // CSL_DMA_WRITE 
  dmaConfigRS.trfType      = CSL_DMA_TRANSFER_IO_MEMORY;
  dmaConfigRS.dataLen      = CSL_DMA_BUFFER_SIZE * 4;
  dmaConfigRS.destAddr      = 0x2A0C; // I2STXRT0
  dmaConfigRS.srcAddr     = (Uint32)dmaPingSrcBufRS; //

  IRQ_globalDisable();
  IRQ_clearAll();
  IRQ_disableAll();
  IRQ_setVecs((Uint32)&VECSTART);
  IRQ_clear(DMA_EVENT);
  IRQ_plug (DMA_EVENT, &dma_isr);
  IRQ_enable(DMA_EVENT);
  IRQ_globalEnable();
  
  status = DMA_init();
  if (status != CSL_SOK)
    {
      printf("DMA_init() Failed \n");
    }
  dmaHandleLR = DMA_open((CSL_DMAChanNum) 4,&dmaObjLR, &status);
  if (dmaHandleLR == NULL)
    {
      printf("DMA_open() Failed \n");
      return 1;
    }
  dmaHandleRR = DMA_open((CSL_DMAChanNum) 5,&dmaObjRR, &status);
  if (dmaHandleRR == NULL)
    {
      printf("DMA_open() Failed \n");
      return 1;
    }
  dmaHandleLS = DMA_open((CSL_DMAChanNum) 6,&dmaObjLS, &status);
  if (dmaHandleLS == NULL)
    {
      printf("DMA_open() Failed \n");
      return 1;
    }
  dmaHandleRS = DMA_open((CSL_DMAChanNum) 7,&dmaObjRS, &status);
  if (dmaHandleLS == NULL)
    {
      printf("DMA_open() Failed \n");
      return 1;
    }

  status = DMA_config(dmaHandleLR, &dmaConfigLR);
  status = DMA_config(dmaHandleRR, &dmaConfigRR);
  status = DMA_config(dmaHandleLS, &dmaConfigLS);
  status = DMA_config(dmaHandleRS, &dmaConfigRS);
  if (status != CSL_SOK)
    {
      printf("DMA_config() Failed \n");
      return 1;
    }
  
  status = DMA_start(dmaHandleLR);
  status = DMA_start(dmaHandleRR);
  status = DMA_start(dmaHandleLS);
  status = DMA_start(dmaHandleRS);
  if (status != CSL_SOK)
    {
      printf("DMA_start() Failed \n");
      return 1;
    }
      printf("DMA_init() Done! \n");
	return 0;
} // End of dma_init  


int dma_stop(void){

  
  status = DMA_close(dmaHandleLR);
  status = DMA_close(dmaHandleRR);
  status = DMA_close(dmaHandleLS);
  status = DMA_close(dmaHandleRS);
  if (status != CSL_SOK)
    {
      printf("DMA_close() Failed \n");
      return(1);
    }
  
  status = DMA_reset(dmaHandleLR);
  status = DMA_reset(dmaHandleRR);
  status = DMA_reset(dmaHandleLS);
  status = DMA_reset(dmaHandleRS);
  if (status != CSL_SOK)
    {
      printf("DMA_reset() Failed \n");
      return(2);
    }
  IRQ_clearAll();
  IRQ_disableAll();
  IRQ_globalDisable();
  
  return(0);
} // dma_stop

/**
 *  \brief  DMA Interrupt Service routine
 *  \param  none
 *  \return none
 */
 int ifrflags =0;
 int lst_xfer_ping =0;
 int lst_xfer_pong =0;
 int bin_here1 = 0;
 int bin_here2 = 0;
 
 extern int data_ready;

interrupt void dma_isr(void) {
  int ifrValue;
  
  ifrValue = CSL_SYSCTRL_REGS->DMAIFR;
  ifrflags = ifrValue;
  CSL_SYSCTRL_REGS->DMAIFR |= ifrValue; // Clear all flags by writing 1 to all active

  if (ifrValue & CSL_SYS_DMAIFR_DMA1CH1IF_MASK) { // Channel 0 ready 
	pp = CSL_FEXT(dmaHandleRR->dmaRegs->DMACH1TCR2,
				                       DMA_DMACH1TCR2_LTSTATUS); //LAST_XFER_BIT
	data_ready++;
  }
} // dma_isr

