/*****************************************************************************/
/*                                                                           */
/* FILENAME                                                                  */
/*  LEDFlasher.c                                                             */
/*                                                                           */
/* DESCRIPTION                                                               */
/*   TMS320C5505 USB Stick. Flash LEDs to indicate different settings.       */
/*                                                                           */
/* REVISION                                                                  */
/*   Revision: 1.00                                                          */
/*   Author  : Richard Sikora                                                */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/* HISTORY                                                                   */
/*   Revision 1.00                                                           */
/*   28th January 2010. Created by Richard Sikora.                           */
/*                                                                           */
/*****************************************************************************/
/*
 *
 * Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/ 
 * 
 * 
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions 
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the   
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/

#define UPDATE_TIME   	 20 // Time between updates in seconds
#define LED_ON_TIME      2  // LED on time in units of 100ms 
#define LED_OFF_TIME     3  // LED off time in units of 100ms   

#define SAMPLES_PER_SECOND 48000

enum {S_START, S_BUSY, S_DONE } state = S_START;

static unsigned int ticks = 0; // Incremented each time function is called i.e. 48000 times per second.
static unsigned int ticks2 = 0;
static unsigned int seconds = 0;
static unsigned int last_seconds = 0xFF; // Non-zero value to ensure used first time through.
static unsigned int counter_100ms = 0;


/*****************************************************************************/
/* LEDFlasher()                                                              */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/* Input: Total number of steps before starting again.                       */ 
/*                                                                           */
/* Returns: Selected state. 1 for 10 seconds. 2 for 10 - 20 seconds etc.     */
/*                                                                           */
/*****************************************************************************/


unsigned int LEDFlasher(unsigned int steps)
{
 static unsigned int selected_state = 0; // Start at zero.
 static unsigned int busy = 0;
 unsigned int update;
 static unsigned int counter = 0;
 static unsigned int loop_counter;

 ticks++;
 ticks2++;

 /* Count in units of 1 second */
 if ( ticks >= SAMPLES_PER_SECOND)
   {
     seconds++;
     ticks = 0; // Start again 
   }

 /* Count in units of 100ms */
 if ( ticks2 >= SAMPLES_PER_SECOND/10)
   {
     counter_100ms++ ; // Update once every 100ms
     ticks2 = 0; // Start again
   }
 
  if ( seconds != last_seconds)
  {
   /* Seconds have just updated. Time for new LED flashes. */
   last_seconds = seconds;
   
   if (seconds % UPDATE_TIME)
     {
      update = 0;
     }
   else
    {
     /* Time exactly divisible by UPDATE_TIME */    	
      update = 1;
      counter++;
      selected_state = counter;
    }  
  }
  else
  {
   update = 0; 
  }
   
  if ( update || busy )
    {
     /* Time exactly divisible by UPDATE_TIME */
     
     switch ( state)
      {
       case S_START:
         if ( steps == 1)
           {
             asm(" bclr XF"); // Single step only. LED stays off.          	
           }
         else
           {
             asm(" bset XF");   // Turn LED on            
           } 
         loop_counter = counter;  
         busy = 1;  
		 counter_100ms = 0;
         state = S_BUSY;   
       break;
       
       case S_BUSY:
         if ( counter_100ms >= LED_ON_TIME)
          {
	        state = S_DONE;	
            asm(" bclr XF");// Turn LED off 
            counter_100ms = 0; 
	      } 
		 else
		 {
		   asm(" bset XF"); // Keep LED on
		 }	  
        break;
       
       case S_DONE:
         if ( counter_100ms >= LED_OFF_TIME)
          {
           counter_100ms = 0;

           loop_counter--;

           if ( loop_counter == 0)
            {
             /* Terminating condition */
             busy = 0;
             state = S_START;
             ticks = 0;
             ticks2 = 0;
             if ( (steps == 0) || (counter == steps) )
              {
               counter = 0; // Back to beginning of sequence
              }
            }
           else
            {
             state = S_BUSY;  // More flashes to do
             asm(" bset XF"); // Turn on LED. Note space between " and bset".
            } 

          }  
		 else
		 {
		   asm(" bclr XF"); // Keep LED off.
		 }
        break; 
      } // End of switch
      
    } // End of if
    
  
 return (selected_state);

}   

/*****************************************************************************/
/* End of LEDFlasher.c                                                       */
/*****************************************************************************/
