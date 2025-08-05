/*
 * switch_interupt.c
 *
 *  Created on: Feb 20, 2025
 *      Author: rahul
 */
#include "include\macros.h"

#pragma vector=PORT4_VECTOR
__interrupt void switchP4_interrupt(void){
    //SW1
    if (P4IFG & SW1){
        P4IE &= ~SW1;                          //disable switch 1
        P4IFG &= ~SW1;                        // interupt flag clear
        TB0CCTL1 &= ~CCIFG;                    // clear timer

        count_debounce_SW1 = 0;
        debounce_happening_sw1 = TRUE;

        TB0CCR1 = TB0R + DEBOUNCE_INTERVAL;  // write value for debounce interval   TB0R stores the current time ...adds same value of 25000

        TB0CCTL1 |= CCIE;  //enable my timer to start

        sw1_position = TRUE;
    }
}

#pragma vector=PORT2_VECTOR
__interrupt void switchP2_interrupt(void){
    //SW1
    if (P2IFG & SW2){
        P2IE &= ~SW2;                          //disable switch 1
        P2IFG &= ~SW2;                        // interupt flag clear goes high when button is pressed and interrupt is called
        TB0CCTL2 &= ~CCIFG;
        // clear timer

        count_debounce_SW2 = 0;
        debounce_happening_sw2 = TRUE;

        TB0CCR2 = TB0R + DEBOUNCE_INTERVAL;  // write value for debounce interval   TB0R stores the current time in register to compare ...adds same value of 25000

        TB0CCTL2 |= CCIE;  //enable my timer to start i now start my timer of 200ms since the switch has been pressed-- jumps to interrupt.c file

        sw2_position = TRUE;
    }
}




