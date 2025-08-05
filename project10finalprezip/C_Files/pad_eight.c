/*
 * pad_eight.c
 *
 *  Created on: Apr 20, 2025
 *      Author: rahul
 */
#include "include\macros.h"


int movement_state = 0;
//11950 for curve

void pad_eight_process(void){
    if (pad_eight_flag){

        switch (movement_state){
        case 0:
            P2OUT |= IR_LED;
            RIGHT_FORWARD_SPEED = 11910;
            LEFT_FORWARD_SPEED  = 50000;
            timeval = Curr_timeval;
            strcpy(display_line[0], " BL START ");
            display_changed = TRUE;
            movement_state = 9;
        break;
        case 1:
            if (Curr_timeval > timeval + 15){
                motor_off();
                timeval = Curr_timeval;
                movement_state = 2;
            }
        break;
        case 2:
            if (Curr_timeval > timeval + 3){
                anti_clockwise_spin();
                timeval = Curr_timeval;
                movement_state = 3;
            }
        break;
        case 3:
            if (Curr_timeval > timeval + 3){
                motor_off();
                timeval = Curr_timeval;
                movement_state = 4;
            }
        break;
        case 4:
            if (Curr_timeval > timeval + 3){
                RIGHT_FORWARD_SPEED = 11950;   //11950 for curve
                LEFT_FORWARD_SPEED  = 50000;
                timeval = Curr_timeval;
                movement_state = 5;
            }
        break;
        case 5:
            if (Curr_timeval > timeval + 33){
                motor_off();
                timeval = Curr_timeval;
                movement_state = 6;
            }
        break;
        case 6:
            if (Curr_timeval > timeval + 4){
                anti_clockwise_spin();
                timeval = Curr_timeval;
                movement_state = 7;
            }
        break;
        case 7:
            if (Curr_timeval > timeval + 5){
                motor_off();
                timeval = Curr_timeval;
                P2OUT |= IR_LED;
                movement_state = 8;
            }
        break;
        case 8:
            if (Curr_timeval > timeval + 3){
                RIGHT_FORWARD_SPEED = 11800;
                LEFT_FORWARD_SPEED  = 50000;
                timeval = Curr_timeval;
                movement_state = 9;
            }
        break;
        case 9:
            if ((ADC_Left_Det < (white_line_value + 25) ) && (ADC_Right_Det < (white_line_value + 25))){
                motor_off();
                timeval = Curr_timeval;
                movement_state = 10;
            }
        break;
        case 10:
            if (Curr_timeval > timeval + 3){
                RIGHT_FORWARD_SPEED = 15000;
                LEFT_FORWARD_SPEED  = 50000;
                timeval = Curr_timeval;
                movement_state = 11;
            }
        break;
        case 11:
            if ((ADC_Left_Det > (black_line_value - 45) ) || (ADC_Right_Det > (black_line_value - 45))){
                motor_off();
                strcpy(display_line[0], " INTERCEPT");
                display_changed = TRUE;
                timeval = Curr_timeval;
                movement_state = 12;
            }
        break;
        case 12:
            if (Curr_timeval > timeval + 25){
                clockwise_spin();
                strcpy(display_line[0], " BL TURN  ");
                display_changed = TRUE;
                timeval = Curr_timeval;
                movement_state = 13;
            }
        break;
        case 13:
            if ((ADC_Left_Det > (black_line_value - 20) ) || (ADC_Right_Det > (black_line_value - 20))){
                motor_off();
                strcpy(display_line[0], "BL TRAVEL ");
                display_changed = TRUE;
                timeval = Curr_timeval;
                movement_state = 14;
            }
        break;
        case 14:
            if (Curr_timeval > (timeval + 10)){
                process_state = Follow_Line;
                command_in_process = 0;
                timeval = Curr_timeval;
                movement_state = 15;
            }
        break;
        case 15:
            if (Curr_timeval > (timeval + 45)){
                motor_off();
                strcpy(display_line[0], "BL CIRCLE ");
                display_changed = TRUE;
                command_in_process = 0;
                timeval = Curr_timeval;
                movement_state = 16;
            }
        break;
        case 16:
            if (Curr_timeval > (timeval + 10)){
                process_state = Follow_Line;
                command_in_process = 0;
                timeval = Curr_timeval;
                movement_state = 17;
            }
        break;
        case 17:
           // if (Curr_timeval > (timeval + 130)){
            if (exit_flag){
                process_state = IDLE;
                P2OUT &= ~IR_LED;
                timeval = Curr_timeval;
                motor_off();
                movement_state = 18;
            }
        break;
        case 18:
            if (Curr_timeval > (timeval + 5)){
                strcpy(display_line[0], "  BL EXIT ");
                timeval = Curr_timeval;
                display_changed = TRUE;
                clockwise_spin();
                movement_state = 19;
            }
        break;
        case 19:
            if(Curr_timeval > (timeval + 3)){
                timeval = Curr_timeval;
                motor_off();
                movement_state = 20;
            }
        break;
        case 20:
            if (Curr_timeval > (timeval + 10)){
                timeval = Curr_timeval;
                RIGHT_FORWARD_SPEED = 20000;
                LEFT_FORWARD_SPEED  = 50000;
                movement_state = 21;
            }
        break;
        case 21:
            if (Curr_timeval > (timeval + 20)){
                strcpy(display_line[0], " BL  STOP ");
                strcpy(display_line[1], " FINALLY! ");
                strcpy(display_line[2], " IM DONE! ");
                display_changed = TRUE;
                motor_off();
                pad_eight_flag = 0;
                command_in_process = 0;
                enable_timer = 0;
            }
        break;
        default: break;
        }
    }
}

