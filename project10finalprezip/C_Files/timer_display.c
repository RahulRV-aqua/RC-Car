/*
 * timer_display.c
 *
 *  Created on: Mar 6, 2025
 *      Author: rahul
 */
#include "include\macros.h"


volatile unsigned int hundreds= 0;
volatile unsigned int tens = 0;
volatile unsigned int ones = 0;
volatile unsigned int tenths = 0;

volatile unsigned int total_seconds = 0;
volatile unsigned int timer = 0;

volatile int time_start_point = 0;




// Update timer function to be called in the main timer interrupt (Timer0_B0_ISR)


void Update_Timer(void) {
    if (!timer_active) return;  // Stop timer when car stops

    if (Curr_timeval >= time_start_point) { //current time increment in sets of 0.2

        timer = Curr_timeval - time_start_point;

        // Convert 0.2-second intervals to seconds
        total_seconds = timer / 5;

        // Calculate individual digits
        hundreds = total_seconds / 100;  // Number of hundreds of seconds
        tens = (total_seconds % 100) / 10;  // Number of tens of seconds
        ones = total_seconds % 10;  // Number of ones of seconds
        tenths = (timer % 5) * 2;  // Tenths of a second (0-4 becomes 0-8)
    }
}


void Display_Timer(void) {
    if (enable_timer){
        Update_Timer();
        // Clear timer display line

        // Format: "T:XXX.X" where XXX is seconds, X is tenths
        display_line[3][6] = '0' + hundreds;
        display_line[3][7] = '0' + tens;
        display_line[3][8] = '0' + ones;
        display_line[3][9] = 's';

        display_changed = TRUE;
    }
}


