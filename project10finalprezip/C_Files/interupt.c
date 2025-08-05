/*
 * interupt.c
 *
 *  Created on: Feb 19, 2025
 *      Author: rahul
 */

// already has function declaration included in functions.h file
#include "include\macros.h"

//time value counter
 volatile unsigned int timeval = 0;
 volatile unsigned int Curr_timeval=0;




#pragma vector = TIMER0_B0_VECTOR
 __interrupt void Timer0_B0_ISR(void){
 //-----------------------------------------------------------------------------
// TimerB0 0 Interrupt handler
 //---------------------------------------------------------------------------
     Curr_timeval++;
     update_display = 1;
     ping_count++;
     TB0CCR0 += TB0CCR0_INTERVAL;

 // Add Offset to TBCCR0
 //---------------------------------------------------------------------------
}

#pragma vector=TIMER0_B1_VECTOR
 __interrupt void TIMER0_B1_ISR(void){  // think timer bo ccr1 all vectors abd cc captures
 //---------------------------------------------------------------------------
// TimerB0 1-2, Overflow Interrupt Vector (TBIV) handler
 //---------------------------------------------------------------------------
    switch(__even_in_range(TB0IV,14)){
     case  0: break;
     // No interrupt
     case  2:
     // SW1
     if (debounce_happening_sw1){
         count_debounce_SW1++;
         if (count_debounce_SW1 > DEBOUNCE_TIME){ //set debounce time
             debounce_happening_sw1 = FALSE;
             P4IE |= SW1;
             TB0CCTL1 &= ~CCIE;
         }

     }
     break;

     case 4:// switch 2 vector
         if (debounce_happening_sw2){
             count_debounce_SW2++;
             if (count_debounce_SW2 > DEBOUNCE_TIME){
                 debounce_happening_sw2 = FALSE;
                 P2IE |= SW2;                        //re enable the ability to call interrupt again by reset
                 TB0CCTL2 &= ~CCIE;                  // set timer back to 0
             }
         }
         break;

     case 14:
         DAC_data = DAC_data - 100;
         SAC3DAT = DAC_data;
         if(DAC_data <= DAC_Limit){
             DAC_data = DAC_Adjust;
             SAC3DAT = DAC_data;
             TB0CTL &= ~TBIE;
             P6OUT &= ~GRN_LED;
             }
     break;
     default: break;
    }
}

#pragma vector=TIMER1_B1_VECTOR
 __interrupt void TIMER1_B1_ISR(void){  // think timer bo ccr1 all vectors abd cc captures
 //---------------------------------------------------------------------------
// TimerB0 1-2, Overflow Interrupt Vector (TBIV) handler
 //---------------------------------------------------------------------------
    switch(__even_in_range(TB0IV,14)){
     case  0: break;
     // No interrupt
     case  2:
     // SW1
        // ADC_display = 1;
        // TB1CCR1 += TB1CCR0_INTERVAL_20MS;
     break;

     case 4:// switch 2 vector
         break;
     case 14:
     // overflow
     break;
     default: break;
    }
}






