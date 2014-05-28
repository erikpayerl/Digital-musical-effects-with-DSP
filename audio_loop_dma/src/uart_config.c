#include 	"stdio.h"
#include	"csl_uart.h"
#include 	"csl_general.h"
#include 	"csl_uartAux.h"
#include 	"ezdsp5535.h"

	CSL_UartSetup uartSetup =
		{
		/* Input clock freq in Hz */
	    100000000,
		/* Baud rate */
	    9600,
		/* Word length of 8 */
	    CSL_UART_WORD8,
		/* To generate 1 stop bit */
	    0,
		/* Disable the parity */
	    CSL_UART_DISABLE_PARITY,
		/* Disable fifo */
		/* Enable trigger 1 fifo */
		CSL_UART_FIFO_DISABLE,
		/* Loop Back enable */
	    CSL_UART_NO_LOOPBACK,
		/* No auto flow control*/
		CSL_UART_NO_AFE ,
		/* No RTS */
		CSL_UART_NO_RTS ,
	};
	
	CSL_UartObj uartObj;	// UART objekt struktur
	CSL_UartHandle hUart;	// UART handtag
	
	extern void VECSTART(void); // Interruptvectorns startadress
	
	/* Fördefinitioner */
	CSL_Status uart_init(void); //Sändarloop, initierar uart och skickar en buffer
	CSL_Status FUART_init(CSL_UartObj *  uartObj,Uint32 uartInstId,
                     CSL_UartOpmode opmode);
	
	interrupt void uart_isr(void); 
	
	CSL_Status UARTstatus;
	int charsent = 0;
	int count=0;
	
CSL_Status uart_init(void) {
		CSL_UartIsrAddr	isrAddr;

		UARTstatus = FUART_init(&uartObj,CSL_UART_INST_0,UART_INTERRUPT);
		if(CSL_SOK != UARTstatus) {
			printf("UART_init failed error code %d\n",UARTstatus);
        	return UARTstatus;
		}
		else
		{
			printf("UART_init Successful\n");
		}
		
		hUart = (CSL_UartHandle)(&uartObj);
		
		UARTstatus = UART_setup(hUart,&uartSetup);
		if(CSL_SOK != UARTstatus)
	    {
	        printf("UART_setup failed error code %d\n",UARTstatus);
	        return UARTstatus;
	    }
	    else
	    {
			printf("UART_setup Successful\n");
		}
	
	   isrAddr.rbiAddr  = uart_isr;
	    
			/* Disable interrupt */
	    IRQ_globalDisable();
	    	/* Clear any pending interrupts */
		IRQ_clearAll();
			/* Disable all the interrupts */
		IRQ_disableAll();
		IRQ_setVecs((Uint32)(&VECSTART));
		IRQ_clear(UART_EVENT);
			/* Configuring Interrupt */
		IRQ_plug (UART_EVENT, &uart_isr);
			/* Enabling Interrupt */
		IRQ_enable(UART_EVENT);
		IRQ_enable(DMA_EVENT);
		IRQ_globalEnable();
			/* Set the UART callback function */
	 	UARTstatus = UART_setCallback(hUart,&isrAddr);
		if(UARTstatus != CSL_SOK)
		{
			printf("UART_setCallback Failed\n");
			return(UARTstatus);
		}
	
	 	/* Enable the UART Events */
		/*UARTstatus = UART_eventEnable(hUart, CSL_UART_RECVOR_REG_DATA_INTERRUPT);
		if(UARTstatus != CSL_SOK)
		{
			printf("UART_eventEnable Failed\n");
			return(UARTstatus);
		}*/
	   	return UARTstatus;
}

interrupt void uart_isr() {
	//CSL_FINST(hUart->uartRegs->FCR, UART_FCR_FIFOEN, ENABLE);
	/*rx = CSL_FEXT(hUart->uartRegs->RBR,UART_RBR_DATA);
	charsent=1;*/
	CSL_FINST(CSL_CPU_REGS->IFR0,CPU_IFR0_UART,DISABLED);
	/*CSL_FINST(hUart->uartRegs->FCR, UART_FCR_RXCLR, CLR);
	CSL_FINST(hUart->uartRegs->PWREMU_MGMT,UART_PWREMU_MGMT_URRST,RESET);
	CSL_FINST(hUart->uartRegs->PWREMU_MGMT,UART_PWREMU_MGMT_URRST,ENABLE);
	*/
	//printf("%d\n",thresh);
	//count++;
}

CSL_Status FUART_init(CSL_UartObj *  uartObj,Uint32 uartInstId,
                     CSL_UartOpmode opmode)
{
	UARTstatus = CSL_SOK;
 
	if(NULL == uartObj)
	{
		return CSL_ESYS_INVPARAMS;
	}

    if(opmode ==  UART_OPMODE_OTHER)
    {
        return CSL_ESYS_INVPARAMS;
    }
   	/* Set the base address  */
	switch ( uartInstId) 
	{
        case CSL_UART_INST_0:
   				uartObj->insId = uartInstId;
                uartObj->sysAddr = CSL_SYSCTRL_REGS;
                uartObj->uartRegs = CSL_UART_REGS; 
                uartObj->opmode = opmode;
                break;
		default:					
                uartObj->insId = CSL_UART_INST_INVALID;	
                UARTstatus = CSL_EUART_INVALID_INST_ID;
                break;
    }   
    if(CSL_UART_INST_INVALID != uartObj->insId)
    {
        /**Enable Master clock                                     */
        CSL_FINST(uartObj->sysAddr->PCGCR1,SYS_PCGCR1_SYSCLKDIS,ACTIVE);
        /**Enable uart peripheral clock gating                */
        CSL_FINST(uartObj->sysAddr->PCGCR1,SYS_PCGCR1_UARTCG,ACTIVE);
        /* changing parallel port mode to 5 - supports UART         */
        CSL_FINST(uartObj->sysAddr->EBSR,SYS_EBSR_PPMODE,MODE1); // ÄNDRAR HÄR TILL MODE1 FRÅN MODE5
        /**Resetting UART  module*/
        //CSL_FINST(uartObj->sysAddr->PRCR, SYS_PRCR_PG4_RST,RST);
    }
    return UARTstatus;
}
