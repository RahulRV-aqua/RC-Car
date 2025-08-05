/*
 * globals.h
 *
 *  Created on: Feb 11, 2025
 *      Author: rahul
 */

#ifndef GLOBALS_H_
#define GLOBALS_H_

volatile char slow_input_down;
extern char display_line[4][11];
extern char *display[4];
unsigned char display_mode;
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;
extern volatile unsigned int Time_Sequence;
extern volatile char one_time;
unsigned int test_value;
char chosen_direction;
char change;

unsigned int wheel_move;
char forward;

//project 4 globlals for time sequence and shapes

volatile unsigned int Last_Time_Sequence;
volatile unsigned int cycle_time;
volatile unsigned int time_change;

//move switch defines and variables to globals so it can be accessed by interrupts

extern volatile unsigned char okay_to_look_at_switch1; // using this to save more space since it only takes uo 1 box
extern volatile unsigned char sw1_position;
extern volatile unsigned int count_debounce_SW1;

extern volatile unsigned char sw2_position;
extern volatile unsigned int count_debounce_SW2;

extern volatile unsigned char debounce_happening_sw1;
extern volatile unsigned char debounce_happening_sw2;

//global for project 5 state machine int value
extern volatile unsigned int goku;

extern volatile unsigned int timeval;
extern volatile unsigned int Curr_timeval;


//globals for project 6 state machines

extern volatile unsigned int requested_move;

extern volatile unsigned int ADC_display;

//timer display globals
extern volatile unsigned int timer_active;

extern volatile unsigned int hundreds;
extern volatile unsigned int tens;
extern volatile unsigned int ones;
extern volatile unsigned int tenths;

//Hw 8 globals

extern long currentBaudRate;
extern char NCSU_array[9];

extern char Process_Buffer[4][32];
extern int pb_index_row;
extern int pb_index_column;


extern char transmit_array[32];    // transmit array for tx
extern int transmit_index ;

extern char USB_Char_Rx[16];
extern unsigned int usb_rx_ring_wr;
extern unsigned int usb_rx_ring_rd;

extern unsigned int delay;


extern int display_row;
extern int send_back;
extern int command_check;
extern int command_received;
extern int transmitting;
extern int command_received_iot;
extern int command_check_iot;

extern char IOT_Data[4][55];
extern int line;
extern int character;
extern unsigned int iot_rx_wr;
extern unsigned int iot_rx_rd;
extern char AT[16];
extern char iot_TX_buf[32];
extern char IOT_Ring_Rx[16];
extern int IOT_line;


extern int movement;
extern int call_once;


extern int boot_state;
extern int ready_done;
extern int IOT_parse;
extern int ip_address_found;


extern int command_in_process;
extern int forward_flag;
extern int reverse_flag;
extern int right_spin_flag;
extern int left_spin_flag;

extern int x;
extern int DAC_data;
extern int enable_timer;

extern volatile int time_start_point;

extern unsigned int pad_eight_flag;
extern int CHECK_ADC_VALUE;
extern int right_side;
extern int left_side;
extern unsigned int white_line_value;
extern unsigned int black_line_value;

extern char store_line_one[10];
extern char store_line_two[10];
extern char store_line_three[10];
extern char store_line_four[10];

extern int exit_flag;
extern int ping_ready;
extern volatile unsigned int ping_count;
extern int movement_state;
#endif /* GLOBALS_H_ */
