/*
 * wheels.c
 *
 *  Created on: Feb 27, 2025
 *      Author: rahul
 */
#include "include\macros.h"



volatile unsigned int process_state=0;
volatile unsigned int motion= 0 ;




 void Wheels_Process(void){
 //-----------------------------------------------------
  switch(process_state){
    case IDLE:                   // IDLE
      break;
    case Configure_Wheel_Speeds: // Configure Movement
        if(motion == 1){
            process_state = Forward_Move_Start;
        }
        if(motion == 2){
            process_state = Reverse_Move_Start;
        }
        if(motion == 3){
            process_state = Spin_Move_Start_clock;
        }
        if(motion == 4){
            process_state = Initiate_Stop;
        }
        if(motion == 5){
            process_state = Spin_Move_Start_anti;
        }
       break;
    case Forward_Move_Start:     // Move Forward Start slowly speed up
      if (((RIGHT_FORWARD_SPEED && RIGHT_REVERSE_SPEED) > WHEEL_OFF)  ||  ((LEFT_FORWARD_SPEED && LEFT_REVERSE_SPEED) >  WHEEL_OFF)){
          process_state = Initiate_Stop;
          P1OUT |= RED_LED;
      }
      else {
          process_state = Forward_Adjust;
      }
      break;
    case Forward_Adjust:         // Adjust Forward incrementing by a 1000
      if ((RIGHT_FORWARD_SPEED < right_target_speed) && (LEFT_FORWARD_SPEED < left_target_speed)){
          RIGHT_FORWARD_SPEED += SPEED_INCREMENT;
          LEFT_FORWARD_SPEED  += SPEED_INCREMENT;
      }

      if ((RIGHT_FORWARD_SPEED < right_target_speed) && (LEFT_FORWARD_SPEED == left_target_speed)){
          RIGHT_FORWARD_SPEED += SPEED_INCREMENT;
          LEFT_FORWARD_SPEED  = left_target_speed;
      }

      if ((RIGHT_FORWARD_SPEED == right_target_speed) && (LEFT_FORWARD_SPEED < left_target_speed)){
          RIGHT_FORWARD_SPEED = right_target_speed;
          LEFT_FORWARD_SPEED  += SPEED_INCREMENT;
      }

      if ((RIGHT_FORWARD_SPEED < right_target_speed) && ( left_target_speed == WHEEL_OFF)){  //turning circle conditions
          RIGHT_FORWARD_SPEED += SPEED_INCREMENT;
          LEFT_FORWARD_SPEED  = WHEEL_OFF;
      }
      if ((right_target_speed == WHEEL_OFF) && (LEFT_FORWARD_SPEED < left_target_speed)){
          RIGHT_FORWARD_SPEED = WHEEL_OFF;
          LEFT_FORWARD_SPEED  += SPEED_INCREMENT;
      }


      if ((RIGHT_FORWARD_SPEED > right_target_speed) && (LEFT_FORWARD_SPEED > left_target_speed)){
          RIGHT_FORWARD_SPEED = right_target_speed;
          LEFT_FORWARD_SPEED  = left_target_speed;
      }
      break;
    case Reverse_Move_Start: // Move Reverse Start
        if (((RIGHT_FORWARD_SPEED && RIGHT_REVERSE_SPEED) > WHEEL_OFF)  ||  ((LEFT_FORWARD_SPEED && LEFT_REVERSE_SPEED) >  WHEEL_OFF)){
            process_state = Initiate_Stop;
            P1OUT |= RED_LED;
        }
        else {
            process_state = Reverse_Adjust;
        }
        break;
    case Reverse_Adjust :        // Adjust Reverse
        if ((RIGHT_REVERSE_SPEED < right_target_speed) && (LEFT_REVERSE_SPEED < left_target_speed)){
            RIGHT_REVERSE_SPEED += SPEED_INCREMENT;
            LEFT_REVERSE_SPEED  += SPEED_INCREMENT;
        }
        if ((RIGHT_REVERSE_SPEED > right_target_speed) && (LEFT_REVERSE_SPEED > left_target_speed)){
            RIGHT_REVERSE_SPEED = right_target_speed;
            LEFT_REVERSE_SPEED  = left_target_speed;
        }
        else {
            RIGHT_REVERSE_SPEED = right_target_speed;
            LEFT_REVERSE_SPEED  = left_target_speed;
        }
        break;
    case Spin_Move_Start_clock :
        if (((RIGHT_FORWARD_SPEED && RIGHT_REVERSE_SPEED) > WHEEL_OFF)  ||  ((LEFT_FORWARD_SPEED && LEFT_REVERSE_SPEED) >  WHEEL_OFF)){
            process_state = Initiate_Stop;
            P1OUT |= RED_LED;
        }
        else {
            process_state = Spin_Move_Adjust_clock;
        }

      break;
    case Spin_Move_Adjust_clock :
        if ((RIGHT_FORWARD_SPEED < right_target_speed) && (LEFT_REVERSE_SPEED < left_target_speed)){
            RIGHT_FORWARD_SPEED += SPEED_INCREMENT;
            LEFT_REVERSE_SPEED  += SPEED_INCREMENT;
        }
        if ((RIGHT_FORWARD_SPEED > right_target_speed) && (LEFT_REVERSE_SPEED > left_target_speed)){
            RIGHT_FORWARD_SPEED = right_target_speed;
            LEFT_REVERSE_SPEED  = left_target_speed;
        }
        else {
            RIGHT_FORWARD_SPEED = right_target_speed;
            LEFT_REVERSE_SPEED  = left_target_speed;
        }
      break;

    case Spin_Move_Start_anti :
        if (((RIGHT_FORWARD_SPEED && RIGHT_REVERSE_SPEED) > WHEEL_OFF)  ||  ((LEFT_FORWARD_SPEED && LEFT_REVERSE_SPEED) >  WHEEL_OFF)){
            process_state = Initiate_Stop;
            P1OUT |= RED_LED;
        }
        else {
            process_state = Spin_Move_Adjust_anti;
        }

      break;
    case Spin_Move_Adjust_anti :
        if ((LEFT_FORWARD_SPEED < left_target_speed) && (RIGHT_REVERSE_SPEED < right_target_speed)){
            LEFT_FORWARD_SPEED += SPEED_INCREMENT;
            RIGHT_REVERSE_SPEED  += SPEED_INCREMENT;
        }
        if ((LEFT_FORWARD_SPEED > right_target_speed) && (RIGHT_REVERSE_SPEED > left_target_speed)){
            LEFT_FORWARD_SPEED = left_target_speed;
            RIGHT_REVERSE_SPEED  = right_target_speed;
        }
        else {
            LEFT_FORWARD_SPEED = left_target_speed;
            RIGHT_REVERSE_SPEED  = right_target_speed;
        }
      break;


    case Initiate_Stop :          // Begin Stop Process
      process_state = Stop;
      break;
    case Stop :                   // Look for End of Stop Time
        RIGHT_FORWARD_SPEED = WHEEL_OFF;   // set all motors to 0
        LEFT_FORWARD_SPEED = WHEEL_OFF;
        RIGHT_REVERSE_SPEED = WHEEL_OFF;
        LEFT_REVERSE_SPEED = WHEEL_OFF;
        motion = 0;
        process_state = IDLE;
      break;

    case Follow_Line:
                if (ADC_Left_Det > (black_line_value - 200) && ADC_Right_Det > (black_line_value - 200)) {
                    // Move straight when both sensors detect the black line
                    LEFT_FORWARD_SPEED = 40000;    //40000 with max
                    RIGHT_FORWARD_SPEED = 20000;        //20000 with max
                    LEFT_REVERSE_SPEED = WHEEL_OFF;
                    RIGHT_REVERSE_SPEED = WHEEL_OFF;
                }
                else if (ADC_Left_Det > (black_line_value - 250) && ADC_Right_Det < (white_line_value + 150)) {
                    // If only left sensor sees black, turn left (toward the line)
                    LEFT_FORWARD_SPEED = 40000;
                    RIGHT_FORWARD_SPEED = WHEEL_OFF;
                    LEFT_REVERSE_SPEED = WHEEL_OFF;
                    RIGHT_REVERSE_SPEED = WHEEL_OFF;

                }
                else if (ADC_Right_Det > (black_line_value - 250) && ADC_Left_Det < (white_line_value + 150)) {
                    // If only right sensor sees black, turn right (toward the line)

                    LEFT_FORWARD_SPEED = WHEEL_OFF;
                    RIGHT_FORWARD_SPEED = 20000;
                    LEFT_REVERSE_SPEED = WHEEL_OFF;
                    RIGHT_REVERSE_SPEED = WHEEL_OFF;

                }
                else {
                    // If both sensors are off the line (both seeing white),
                    // move backward until any sensor detects the black line again
                    LEFT_FORWARD_SPEED = WHEEL_OFF;
                    RIGHT_FORWARD_SPEED = WHEEL_OFF;
                    LEFT_REVERSE_SPEED = 20000;
                    RIGHT_REVERSE_SPEED = 20000;
                }
                break;
    default: break;              //when 0 default break start cases from int=1
  }
}
 //-----------------------------------------------------

 void forward_on_slow(void){
     RIGHT_FORWARD_SPEED = 11300;
     LEFT_FORWARD_SPEED  = 50000;
     motion = 1; // motion type variable  forward
     process_state = Configure_Wheel_Speeds;
 }
 void motor_off(void){
     right_target_speed = WHEEL_OFF;
     left_target_speed  = WHEEL_OFF;
     motion = 4;
     process_state = Configure_Wheel_Speeds;
 }

 void reverse_on(void){
     right_target_speed = SLOW;
     left_target_speed = SLOW;
     motion = 2; // motion type variable  reverse
     process_state = Configure_Wheel_Speeds;

 }

 void clockwise_spin(void){
     right_target_speed = 20000;
     left_target_speed = 30000;
     motion = 3; // motion type variable  spin
     process_state = Configure_Wheel_Speeds;

 }
 void anti_clockwise_spin(void){
     right_target_speed = 20000;
     left_target_speed = 30000;
     motion = 5; // motion type variable  spin
     process_state = Configure_Wheel_Speeds;

 }

 void forward_on_slow_right(void){
     right_target_speed = SLOWEST;
     left_target_speed = MEDIUM;
     motion = 1; // motion type variable  forward
     process_state = Configure_Wheel_Speeds;

 }
 void forward_on_slow_left(void){
     right_target_speed = SLOWER;
     left_target_speed = WHEEL_OFF;
     motion = 1; // motion type variable  forward
     process_state = Configure_Wheel_Speeds;

 }





