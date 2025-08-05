/*
 * ports.c
 *
 *  Created on: Jan 30, 2025
 *      Author: rahul
 */

#include  "include\macros.h"

void Init_Port_1(void){ //configure port 1
    P1OUT = 0x00;                  // P1 set Low
    P1DIR = 0x00;                  // Set P1 direction to output

    //pin 1.0
    P1SEL0 &= ~RED_LED;           // SLOW_CLK GPIO operation
    P1SEL1 &= ~RED_LED;           // SLOW_CLK GPIO operation
    P1OUT &= ~RED_LED;            // Initial Value = Low / Off
    P1DIR &= ~RED_LED;             // Direction = output

    //pin 1.1
    P1SELC |=  A1_SEEED;

    //pin 1.2
    P1SELC |=  V_DETECT_L ;

    //pin 1.3
    P1SELC |=  V_DETECT_R;

    //pin 1.4
    P1SELC |=  A4_SEEED;

    //pin 1.5
    P1SELC |=  V_THUMB;

    //pin 1.6
    P1SEL0 |=  UCA0RXD;
    P1SEL1 &=  ~UCA0RXD;

    //pin 1.7
    P1SEL0 |=  UCA0TXD;
    P1SEL1 &=  ~UCA0TXD;


}

void Init_Port_2(void){ // Configure Port 2
     P2OUT = 0x00;                  // P2 set Low
     P2DIR = 0x00;                  // Set P2 direction to output

     //pin 2.0
     P2SEL0 &= ~SLOW_CLK;           // SLOW_CLK GPIO operation
     P2SEL1 &= ~SLOW_CLK;           // SLOW_CLK GPIO operation
     P2OUT &= ~SLOW_CLK;            // Initial Value = Low / Off
     P2DIR |= SLOW_CLK;             // Direction = output

     //pin 2.1
     P2SEL0 &= ~CHECK_BAT;          // CHECK_BAT GPIO operation
     P2SEL1 &= ~CHECK_BAT;          // CHECK_BAT GPIO operation
     P2OUT &= ~CHECK_BAT;           // Initial Value = Low / Off
     P2DIR |= CHECK_BAT;            // Direction = output

     //pin 2.2
     P2SEL0 &= ~IR_LED;             // P2_2 GPIO operation
     P2SEL1 &= ~IR_LED;             // P2_2 GPIO operation
     P2OUT &= ~IR_LED;              // Initial Value = Low / Off
     P2DIR |= IR_LED;               // Direction = output

     //pin 2.3
     P2SEL0 &= ~SW2;                // SW1 GPIO operation
     P2SEL1 &= ~SW2;                // SW1 GPIO operation
     P2DIR &= ~SW2;                 // Direction = input
     P2PUD |= SW2;                  // Configure pullup resistor
     P2REN |= SW2;                  // Enable pullup resistor

     P2IES |= SW2;                  // SW1 hi/lo edge interupt
     P2IFG &= ~SW2;                 //interrupt flag cleared
     P2IE |= SW2;                   //SW1 interrupt enabled

     //pin 2.4
     P2SEL0 &= ~IOT_RUN_CPU;        // IOT_RUN_CPU GPIO operation
     P2SEL1 &= ~IOT_RUN_CPU;        // IOT_RUN_CPU GPIO operation
     P2OUT &= ~IOT_RUN_CPU;         // Initial Value = Low / Off
     P2DIR |= IOT_RUN_CPU;          // Direction = output

     //pin 2.5
     P2SEL0 &= ~DAC_ENB;            // DAC_ENB GPIO operation
     P2SEL1 &= ~DAC_ENB;            // DAC_ENB GPIO operation
     P2OUT |= DAC_ENB;              // Initial Value = High
     P2DIR |= DAC_ENB;              // Direction = output

     //pin 2.6
     P2SEL0 &= ~LFXOUT;             // LFXOUT Clock operation
     P2SEL1 |= LFXOUT;              // LFXOUT Clock operation

     //pin 2.7
     P2SEL0 &= ~LFXIN;              // LFXIN Clock operation
     P2SEL1 |= LFXIN;               // LFXIN Clock operation
}

void Init_Port_3(unsigned int s_event){ //configure port 3
    P3OUT = 0x00;                  // P3 set Low
    P3DIR = 0x00;                  // Set P3 direction to output

    //pin 3.0
    P3SEL0 &= ~TEST_PROBE;           // SLOW_CLK GPIO operation
    P3SEL1 &= ~TEST_PROBE;           // SLOW_CLK GPIO operation
    P3OUT &= ~TEST_PROBE;            // Initial Value = Low / Off
    P3DIR &= ~TEST_PROBE;             // Direction = output

    //pin 3.1
    P3SELC |=  OA2O;

    //pin 3.2
    P3SELC |=  OA2N ;

    //pin 3.3
    P3SELC |=  OA2P;

    //pin 3.4
        if (s_event == USE_GPIO){
        P3SEL0 &= ~SMCLK_OUT;
        P3SEL1 &= ~SMCLK_OUT;
        P3OUT  |= SMCLK_OUT;
        P3DIR |= SMCLK_OUT;
        }

        if( s_event == USE_SMCLK){
            /*
                P3SEL0 &= ~SMCLK_OUT;
                P3SEL1 &= ~SMCLK_OUT;
                P3OUT  |= SMCLK_OUT;
                P3DIR |= SMCLK_OUT;

               */
                P3SEL0 |= SMCLK_OUT;
                P3SEL1 &= ~SMCLK_OUT;
                P3DIR |= SMCLK_OUT;



            }


    //pin 3.5

    P3SELC |=  DAC_CTRL;  // DAC_CNTL DAC operation
    //P3SEL0 &= ~DAC_CTRL;           // SLOW_CLK GPIO operation
    //P3SEL1 &= ~DAC_CTRL;           // SLOW_CLK GPIO operation
    //P3OUT |= DAC_CTRL;            // Initial Value = Low / Off
   // P3DIR |= DAC_CTRL;              // Direction = input




    //pin 3.6
    P3SEL0 &= ~IOT_LINK_CPU;           // SLOW_CLK GPIO operation
    P3SEL1 &= ~IOT_LINK_CPU;           // SLOW_CLK GPIO operation
    P3OUT &= ~IOT_LINK_CPU;            // Initial Value = Low / Off
    P3DIR |= IOT_LINK_CPU;              // Direction = input

    //pin 3.7
    P3SEL0 &= ~IOT_EN_CPU;           // SLOW_CLK GPIO operation
    P3SEL1 &= ~IOT_EN_CPU;           // SLOW_CLK GPIO operation
    P3OUT &= ~IOT_EN_CPU;            // Initial Value = Low / Off
    P3DIR |= IOT_EN_CPU;              // Direction = input


}

void Init_Port_4(void){ //configure port 4
     P4OUT = 0x00;                  // P4 set Low
     P4DIR = 0x00;                  // Set P4 direction to output

     //pin 4.0
     P4SEL0 &= ~RESET_LCD;          // RESET_LCD GPIO operation
     P4SEL1 &= ~RESET_LCD;          // RESET_LCD GPIO operation
     P4OUT &= ~RESET_LCD;           // Initial Value = Low / Off
     P4DIR |= RESET_LCD;            // Direction = output

     //pin 4.1
     P4SEL0 &= ~SW1;                // SW1 GPIO operation
     P4SEL1 &= ~SW1;                // SW1 GPIO operation
     P4DIR &= ~SW1;                 // Direction = input
     P4PUD |= SW1;                  // Configure pullup resistor
     P4REN |= SW1;                  // Enable pullup resistor

     P4IES |= SW1;                  // SW1 hi/lo edge interupt
     P4IFG &= ~SW1;                 //interrupt flag cleared
     P4IE |= SW1;                   //SW1 interrupt enabled

     //pin 4.2
     P4SEL0 |= UCA1RXD;             // USCI_A1 UART operation
     P4SEL1 &= ~UCA1RXD;            // USCI_A1 UART operation

     //pin 4.3
     P4SEL0 |= UCA1TXD;             // USCI_A1 UART operation
     P4SEL1 &= ~UCA1TXD;            // USCI_A1 UART operation

     //pin 4.4
     P4SEL0 &= ~UCB1_CS_LCD;        // UCB1_CS_LCD GPIO operation
     P4SEL1 &= ~UCB1_CS_LCD;        // UCB1_CS_LCD GPIO operation
     P4OUT |= UCB1_CS_LCD;          // Set SPI_CS_LCD Off [High]
     P4DIR |= UCB1_CS_LCD;          // Set SPI_CS_LCD direction to output

     //pin 4.5
     P4SEL0 |= UCB1CLK;             // UCB1CLK SPI BUS operation
     P4SEL1 &= ~UCB1CLK;            // UCB1CLK SPI BUS operation

     //pin 4.6
     P4SEL0 |= UCB1SIMO;            // UCB1SIMO SPI BUS operation
     P4SEL1 &= ~UCB1SIMO;           // UCB1SIMO SPI BUS operation

     //pin 4.7
     P4SEL0 |= UCB1SOMI;            // UCB1SOMI SPI BUS operation
     P4SEL1 &= ~UCB1SOMI;           // UCB1SOMI SPI BUS operation
}


void Init_Port_5(void){ //configure port 5
    P5OUT = 0x00;                  // P5 set Low
    P5DIR = 0x00;                  // Set P5 direction to output

    //pin 5.0
    P5SELC |=  V_BAT;

    //pin 5.1
    P5SELC |=  V_5;

    //pin 5.2
    P5SELC |=  V_DAC;

    //pin 5.3
    P5SELC |=  V3_3;

    //pin 5.4
    P5SEL0 &= ~IOT_BOOT_CPU;        // IOT_BOOT_CPU GPIO operation
    P5SEL1 &= ~IOT_BOOT_CPU;        // IOT_BOOT_CPU GPIO operation
    P5OUT &= ~IOT_BOOT_CPU;          // Set IOT_BOOT_CPU Off [Low]
    P5DIR &= ~IOT_BOOT_CPU;          // Set IOT_BOOT_CPU direction to input

}

void Init_Port_6(void){ //configure port 6 FOR Project6 !!!!!!!!!!!


    P6OUT = 0x00;                  // P6 set Low
    P6DIR = 0x00;                  // Set P6 direction to output

    //pin 6.0
    P6SEL0 |= LCD_BACKLITE;        // LCD_BACKLITE GPIO operation
    P6SEL1 &= ~LCD_BACKLITE;        // LCD_BACKLITE GPIO operation

    P6DIR |= LCD_BACKLITE;          // Set LCD_BACKLITE direction to output

    //pin 6.1
    P6SEL0 |= R_FORWARD;        // R_FORWARD GPIO operation
    P6SEL1 &= ~R_FORWARD;        // R_FORWARD GPIO operation

    P6DIR |= R_FORWARD;          // Set R_FORWARD direction to input

    //pin 6.2
    P6SEL0 |= L_FORWARD;        // L_FORWARD GPIO operation
    P6SEL1 &= ~L_FORWARD;        // L_FORWARD GPIO operation

    P6DIR |= L_FORWARD;          // Set L_FORWARD direction to input

    //pin 6.3
    P6SEL0 |= R_REVERSE;        // UCB1_CS_LCD GPIO operation
    P6SEL1 &= ~R_REVERSE;        // UCB1_CS_LCD GPIO operation

    P6DIR |= R_REVERSE;          // Set SPI_CS_LCD direction to input

    //pin 6.4
    P6SEL0 |= L_REVERSE;        // UCB1_CS_LCD GPIO operation
    P6SEL1 &= ~L_REVERSE;        // UCB1_CS_LCD GPIO operation

    P6DIR |= L_REVERSE;          // Set SPI_CS_LCD direction to input

    //pin 6.5
    P6SEL0 &= ~ P6_5;        // UCB1_CS_LCD GPIO operation
    P6SEL1 &= ~P6_5;        // UCB1_CS_LCD GPIO operation
    P6OUT &= ~P6_5;
    P6DIR &= ~P6_5;          // Set SPI_CS_LCD direction to input

    //pin 6.6
    P6SEL0 &= ~GRN_LED;        // UCB1_CS_LCD GPIO operation
    P6SEL1 &= ~GRN_LED;        // UCB1_CS_LCD GPIO operation
    P6OUT &= ~GRN_LED;
    P6DIR |= GRN_LED;          // Set SPI_CS_LCD direction to output

}

void Init_Ports(void){ //initialize all ports
    Init_Port_1();
    Init_Port_2();
    Init_Port_3(USE_GPIO);  // change to only use gp/io
    Init_Port_4();
    Init_Port_5();
    Init_Port_6();

}


