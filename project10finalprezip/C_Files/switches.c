/*
 * switches.c
 *
 *  Created on: Feb 11, 2025
 *      Author: rahul
 */

#include "include\macros.h"

//p4 states defines
#define PRESSED    (0)
#define RELEASED   (1)
#define OKAY       (1)
#define NOT_OKAY   (0)

#define DEBOUNCE_RESTART (0)


volatile unsigned char okay_to_look_at_switch1 = OKAY; // using this to save more space since it only takes uo 1 box
volatile unsigned char sw1_position = FALSE;
volatile unsigned int count_debounce_SW1;

volatile unsigned char sw2_position = FALSE;
volatile unsigned int count_debounce_SW2;

volatile unsigned char debounce_happening_sw1 = OKAY;
volatile unsigned char debounce_happening_sw2 = OKAY;

volatile unsigned int goku = 0;

volatile unsigned int emitter_state = 0;

unsigned int blackval = 0;
unsigned int whiteval = 0;

unsigned int delay = 0;
unsigned int sw1_presses = 0;
unsigned int sw2_presses = 0;




void Switches_Process(void){
 //-----------------------------------------------------------------------------
// This function calls the individual Switch Functions
 //-----------------------------------------------------------------------------
    Switch1_Process();
    Switch2_Process();
 }



void Switch1_Process(void){
 //-----------------------------------------------------------------------------
// Switch 1 Configurations
 // Port P4 Pin 1
 //-----------------------------------------------------------------------------
    if (sw1_position){  //if (sw_1 is pressed) external interrupt is called so that switch cannot be pressed again
        sw1_position = FALSE;  // Reset after processing
        sw2_position = FALSE;  // Reset SW2 so it can be pressed again
        if (sw1_presses == 0){
            strncpy (store_line_one, display_line[0], 10);
            strncpy (store_line_two, display_line[1], 10);
            strncpy (store_line_three, display_line[2], 10);
            strncpy (store_line_four, display_line[3], 10);

            strcpy(display_line[0], "          ");
            strcpy(display_line[1], "          ");
            strcpy(display_line[2], "L         ");
            strcpy(display_line[3], "R         ");
            display_changed = TRUE;
            P2OUT |= IR_LED;
            CHECK_ADC_VALUE = 1;
            sw1_presses++;
        }
        else if (sw1_presses == 1){
            strncpy (display_line[0], store_line_one, 10 );
            strncpy (display_line[1], store_line_two, 10 );
            strncpy (display_line[2], store_line_three, 10 );
            strncpy (display_line[3], store_line_four, 10 );
            display_changed = TRUE;
            sw1_presses = 0;
            P2OUT &= ~IR_LED;
            CHECK_ADC_VALUE = 0;
        }



    }
 //do what you want with button press


}
 //-----------------------------------------------------------------------------



void Switch2_Process(void){
 //-----------------------------------------------------------------------------
// Switch 2 Configurations
 // Port P2 Pin 3
 //-----------------------------------------------------------------------------
    if (sw2_position){
        sw1_position = FALSE;  // Reset after processing
        sw2_position = FALSE;  // Reset SW2 so it can be pressed again

        if (sw2_presses == 0){
            white_line_value = (ADC_Left_Det + ADC_Right_Det) >>1 ;
            strcpy(display_line[0], "W         ");
            display_changed = TRUE;
            HEXtoBCD(white_line_value);
            adc_line(1, 4);
            left_side = 0;
            sw2_presses ++;
        }
        else if (sw2_presses == 1){
            black_line_value = (ADC_Left_Det + ADC_Right_Det) >>1;
            strcpy(display_line[1], "B         ");
            display_changed = TRUE;
            display_changed = TRUE;
            HEXtoBCD(black_line_value);
            adc_line(2, 4);

            right_side = 0;
            sw2_presses = 0;
        }




/*

        while (Curr_timeval < (timeval + 10)){
            continue;
        }
        strncpy (transmit_array, NCSU_array, 10);
        UCA1IE |= UCTXIE;      //enable interrupt
*/
    }

}
 //do what you want with button press


