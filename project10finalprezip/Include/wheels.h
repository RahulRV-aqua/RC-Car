/*
 * wheels.h
 *
 *  Created on: Feb 27, 2025
 *      Author: rahul
 */

#ifndef WHEELS_H_
#define WHEELS_H_


#define IDLE                    (0)
#define Configure_Wheel_Speeds  (1)
#define Forward_Move_Start      (10)
#define Reverse_Move_Start      (2)
#define Spin_Move_Start_clock   (3)
#define Spin_Move_Start_anti   (13)
#define Initiate_Stop           (4)
#define Follow_Line             (11)

#define Forward_Adjust          (5)
#define Reverse_Adjust          (6)
#define Spin_Move_Adjust_clock    (7)
#define Spin_Move_Adjust_anti   (12)
#define Stop                    (9)

extern volatile unsigned int requested_move;
extern volatile unsigned int process_state;

volatile unsigned int right_target_speed;
volatile unsigned int left_target_speed;


void Wheels_Process(void);



void motor_off(void);
void forward_on_slow(void);
void clockwise_spin(void);
void anti_clockwise_spin(void);
void reverse_on(void);
void forward_on_slow_right(void);
void forward_on_slow_left(void);



#endif /* WHEELS_H_ */
