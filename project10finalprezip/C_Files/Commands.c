/*
 * Commands.c
 *
 *  Created on: Apr 7, 2025
 *      Author: rahul
 */

#include "include\macros.h"

void process_commands(void){
    if (command_received){

        if(Process_Buffer[display_row][1]  == '^'){
            strcpy(transmit_array, "I'm here\n");
            UCA1IE |= UCTXIE;
            transmitting = TRUE;
            command_received = 0;
        }
        if(Process_Buffer[display_row][1]  == 'F'){
            strcpy(transmit_array, "115200\n");
            UCA1IE |= UCTXIE;
            transmitting = TRUE;
            command_received = 0;
        }
        if(Process_Buffer[display_row][1]  == 'S'){
            strcpy(transmit_array, "9600\n");
            UCA1IE |= UCTXIE;
            transmitting = TRUE;
            command_received = 0;
        }
        /*
        if(Process_Buffer[display_row][1]  == 'A'){
            strcpy(transmit_array, "forward\n");
            strcpy(display_line[0], "forward   ");
            display_changed = TRUE;
            UCA1IE |= UCTXIE;
            transmitting = TRUE;
            movement = 1; // make it exterm
            timeval = Curr_timeval;
            call_once = 1;
            command_received = 0;
        }*/
    }

}


