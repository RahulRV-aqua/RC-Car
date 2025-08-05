/*
 * macros.h
 *
 *  Created on: Jan 30, 2025
 *      Author: rahul
 */

#ifndef MACROS_H_
#define MACROS_H_

#include <string.h>
#include <stdlib.h>

#include "include\States.h" // has defines for states
#include "include\clocks.h"
#include "include\display.h"
#include "include\functions.h"
#include "include\init.h"
#include "include\LCD.h"
#include "include\led.h"
#include "include\ports.h"
#include "include\system.h"
#include "include\globals.h"
#include "include\timer_display.h"

#include "include\wheels.h"
#include "include\converter.h"
#include "include\ADC.h"
#include "include\Commands.h"
#include "include\DAC.h"
#include "include\pad_eight.h"
//removed all prev motor definitioons from previous projects



#include "msp430.h"  //has all other

#define ALWAYS                  (1)
#define RESET_STATE             (0)
#define RED_LED              (0x01) // RED LED 0
#define GRN_LED              (0x40) // GREEN LED 1
#define TEST_PROBE           (0x01) // 0 TEST PROBE
#define TRUE                 (0x01) //

#define USE_GPIO     (0x00)
#define USE_SMCLK    (0x01)

#define P4PUD   (P4OUT)
#define P2PUD   (P2OUT)


#define TB0CCR0_INTERVAL  (25000)
#define DEBOUNCE_INTERVAL  (25000)
#define DEBOUNCE_TIME  (5) //5*200 is 1 sec so switch cannot be pressed again for 1 second

#define TIMER_B0_CCR1_2_OV_VECTOR  TIMER0_B1_VECTOR

#define TB1CCR0_INTERVAL_20MS  (1500)  //around 15ms
#define TB1CCR1_INTERVAL_200MS (25000)
#define SPEED_INCREMENT  (2000)



// P5 defines for dividers and a lot of things!!!

#define ID__2                    (0x0040)        /* /2 */
#define ID__4                    (0x0080)        /* /4 */
#define ID__8                    (0x00c0)        /* /8 */

#define TBIDEX_0                 (0x0000)        /* Divide by 1 */
#define TBIDEX_1                 (0x0001)        /* Divide by 2 */
#define TBIDEX_2                 (0x0002)        /* Divide by 3 */
#define TBIDEX_3                 (0x0003)        /* Divide by 4 */
#define TBIDEX_4                 (0x0004)        /* Divide by 5 */
#define TBIDEX_5                 (0x0005)        /* Divide by 6 */
#define TBIDEX_6                 (0x0006)        /* Divide by 7 */
#define TBIDEX_7                 (0x0007)        /* Divide by 8 */

#define TBIDEX__1                (0x0000)        /* Divide by 1 */
#define TBIDEX__2                (0x0001)        /* Divide by 2 */
#define TBIDEX__3                (0x0002)        /* Divide by 3 */
#define TBIDEX__4                (0x0003)        /* Divide by 4 */
#define TBIDEX__5                (0x0004)        /* Divide by 5 */
#define TBIDEX__6                (0x0005)        /* Divide by 6 */
#define TBIDEX__7                (0x0006)        /* Divide by 7 */
#define TBIDEX__8                (0x0007)        /* Divide by 8 */


volatile unsigned char event; // event state can be accessed anywhere


//project6 defines timers all PWM STUFF!!!!
#define PWM_PERIOD          (TB3CCR0)
#define LCD_BACKLITE_DIMING (TB3CCR1)
#define RIGHT_FORWARD_SPEED (TB3CCR4)
#define RIGHT_REVERSE_SPEED (TB3CCR5)
#define LEFT_FORWARD_SPEED  (TB3CCR2)
#define LEFT_REVERSE_SPEED  (TB3CCR3)


#define SLOW            (15000)
#define SLOWER          (8000)
#define SUPERSLOW       (15000)
#define FAST            (50000)
#define MEDIUM          (25000)
#define SLOWEST         (20000)
#define PERCENT_100     (50005)
#define PERCENT_80      (45000)
#define RIGHTSLOW       (17000)
#define SUPERSLOWLEFT   (7000)


#define BLACK_LINE_MAX          (600)



//HW8 defines

#define ROWS            (4)
#define COLUMNS         (32)

#define BEGINNING       (0x00)

#endif /* MACROS_H_ */
