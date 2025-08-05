/*
 * switchbaudrate.c
 *
 *  Created on: Mar 27, 2025
 *      Author: rahul
 */

#include "include\macros.h"

char wait_array[8] = "WAITING\n";

unsigned int usb_rx_ring_wr = 0;
unsigned int usb_rx_ring_rd = 0;
char USB_Char_Rx[16];

unsigned int iot_rx_wr = 0;
unsigned int iot_rx_rd = 0;
char AT[16] = "AT+CWJAP?\r\n";


int transmit_index = 0x00;
int iot_t_index = 0x00;

long currentBaudRate = 460800;
int pb_index_row = 0x00;
int pb_index_column = 0x00;

int line = 0x00;
int character = 0x00;
char IOT_Ring_Rx[16];
char iot_TX_buf[32];
char IOT_Data[4][55];

int transmitting = 0;



void Init_Serial_UCA1(void){
    //------------------------------------------------------------------------------
    // TX error (%) RX error (%)
    // BRCLK Baudrate UCOS16 UCBRx UCFx UCSx neg pos neg pos
    // 8000000 4800 1 104 2 0xD6 -0.08 0.04 -0.10 0.14
    // 8000000 9600 1 52 1 0x49 -0.08 0.04 -0.10 0.14
    // 8000000 19200 1 26 0 0xB6 -0.08 0.16 -0.28 0.20
    // 8000000 57600 1 8 10 0xF7 -0.32 0.32 -1.00 0.36
    // 8000000 115200 1 4 5 0x55 -0.80 0.64 -1.12 1.76
    // 8000000 .,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,, 0 17 0 0x4A -2.72 2.56 -3.76 7.28
    //------------------------------------------------------------------------------
    // Configure eUSCI_A0 for UART mode
    usb_rx_ring_wr = BEGINNING;
    usb_rx_ring_rd = BEGINNING;

     UCA1CTLW0 = 0;
     UCA1CTLW0 |= UCSWRST ; // Put eUSCI in reset
     UCA1CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK
     UCA1CTLW0 &= ~UCMSB; // MSB, LSB select
     UCA1CTLW0 &= ~UCSPB; // UCSPB = 0(1 stop bit) OR 1(2 stop bits)
     UCA1CTLW0 &= ~UCPEN; // No Parity
     UCA1CTLW0 &= ~UCSYNC;
     UCA1CTLW0 &= ~UC7BIT;
     UCA1CTLW0 |= UCMODE_0;
    // BRCLK Baudrate UCOS16 UCBRx UCFx UCSx neg pos neg pos
    // 8000000 115200 1 4 5 0x55 -0.80 0.64 -1.12 1.76
    // UCA?MCTLW = UCSx + UCFx + UCOS16


     UCA1BRW = 4 ; // 460800 baud
     UCA1MCTLW = 0x5551 ;
     UCA1CTLW0 &= ~UCSWRST ; // release from reset
     UCA1TXBUF = 0x00; // Prime the Pump
     UCA1IE |= UCRXIE; // Enable RX interrupt
    //------------------------------------------------------------------------------
}

void Init_Serial_UCA0(void){
    //------------------------------------------------------------------------------
    // TX error (%) RX error (%)
    // BRCLK Baudrate UCOS16 UCBRx UCFx UCSx neg pos neg pos
    // 8000000 4800 1 104 2 0xD6 -0.08 0.04 -0.10 0.14
    // 8000000 9600 1 52 1 0x49 -0.08 0.04 -0.10 0.14
    // 8000000 19200 1 26 0 0xB6 -0.08 0.16 -0.28 0.20
    // 8000000 57600 1 8 10 0xF7 -0.32 0.32 -1.00 0.36
    // 8000000 115200 1 4 5 0x55 -0.80 0.64 -1.12 1.76
    // 8000000 .,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,, 0 17 0 0x4A -2.72 2.56 -3.76 7.28
    //------------------------------------------------------------------------------
    // Configure eUSCI_A0 for UART mode
    usb_rx_ring_wr = BEGINNING;
    usb_rx_ring_rd = BEGINNING;

     UCA0CTLW0 = 0;
     UCA0CTLW0 |= UCSWRST ; // Put eUSCI in reset
     UCA0CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK
     UCA0CTLW0 &= ~UCMSB; // MSB, LSB select
     UCA0CTLW0 &= ~UCSPB; // UCSPB = 0(1 stop bit) OR 1(2 stop bits)
     UCA0CTLW0 &= ~UCPEN; // No Parity
     UCA0CTLW0 &= ~UCSYNC;
     UCA0CTLW0 &= ~UC7BIT;
     UCA0CTLW0 |= UCMODE_0;
    // BRCLK Baudrate UCOS16 UCBRx UCFx UCSx neg pos neg pos
    // 8000000 115200 1 4 5 0x55 -0.80 0.64 -1.12 1.76
    // UCA?MCTLW = UCSx + UCFx + UCOS16


     UCA0BRW = 4 ; // 460800 baud
     UCA0MCTLW = 0x5551 ;
     UCA0CTLW0 &= ~UCSWRST ; // release from reset
     UCA1TXBUF = 0x00; // Prime the Pump
     UCA0IE |= UCRXIE; // Enable RX interrupt
    //------------------------------------------------------------------------------
}

#pragma vector=EUSCI_A0_VECTOR
__interrupt void eUSCI_A0_ISR(void){
    unsigned char iot_value;
    switch(__even_in_range(UCA0IV,0x08)){
        case 0: // Vector 0 - no interrupt
            break;
        case 2: // Vector 2 - RXIFG
            iot_value = UCA0RXBUF;

            //if (iot_value == '^'){
            //    iot_command_received = 1;   // iot flag
            //}
            IOT_Ring_Rx[iot_rx_wr] = iot_value;
            iot_rx_wr++;
            if (iot_rx_wr >= sizeof(IOT_Ring_Rx)) {
                iot_rx_wr = BEGINNING;
            }

            UCA1TXBUF = iot_value;

            break;
        case 4: // Vector 4 – TXIFG
            UCA0TXBUF = iot_TX_buf[iot_t_index];
            if (iot_TX_buf[iot_t_index] == '\n'){
                iot_t_index = 0;
                int i;
                for (i = 0; i<sizeof(iot_TX_buf); i++){
                    iot_TX_buf[i] = 0x00;
                }
                UCA0IE &= ~UCTXIE;
            }
            else {
                iot_t_index++;
            }

            break;
        default: break;
    }
}


#pragma vector=EUSCI_A1_VECTOR
__interrupt void eUSCI_A1_ISR(void){
    unsigned char temp;
    switch(__even_in_range(UCA1IV,0x08)){
        case 0: // Vector 0 - no interrupt
            break;
        case 2: // Vector 2 - RXIFG
            temp = UCA1RXBUF;

            if(temp == '^' ){
                command_check = 1;
            }
            if (command_check){
                USB_Char_Rx[usb_rx_ring_wr] = temp;                // **Ensure ring buffer wraps correctly**
                usb_rx_ring_wr++;
                if (usb_rx_ring_wr >= sizeof(USB_Char_Rx)) {
                    usb_rx_ring_wr = BEGINNING;
                }
                if (temp == '\r'){
                    command_check = 0;
                }

            }
            else UCA0TXBUF = temp;

            break;


        case 4: // Vector 4 – TXIFG

            UCA1TXBUF = transmit_array[transmit_index];
            if(transmit_array[transmit_index] == '\n'){
                transmit_index = 0x00;
                transmitting = FALSE;
                UCA1IE &= ~UCTXIE;// stop interrupt
            }
            else transmit_index++;
            break;
        default: break;
    }
}


void setBaudRate(unsigned long baud) {
    if (currentBaudRate == baud) return;

    currentBaudRate = baud;

    UCA0CTLW0 |= UCSWRST;  // Put UART0 in reset mode
    //UCA1CTLW0 |= UCSWRST;  // Put UART1 in reset mode

    if (baud == 115200) {
        //UCA0BRW = 4;        // 115200 baud
        UCA0BRW = 4;
       // UCA0MCTLW = 0x5551;
        UCA0MCTLW = 0x5551;

    }
    else if (baud == 460800) {
       // UCA0BRW = 17;        // 460800 baud
        UCA0BRW = 17;
       // UCA0MCTLW = 0x4A00;
        UCA0MCTLW = 0x4A00;
    }
    else if (baud == 4800){
        UCA0BRW = 104;
        UCA0MCTLW = 0xD621;
    }
    else if (baud == 9600){
        UCA0BRW = 52;
        UCA0MCTLW = 0x4911;
    }
    else if (baud == 19200){
        UCA0BRW = 26;
        UCA0MCTLW = 0xB601;
    }
    else if (baud == 57600){
        UCA0BRW = 8;
        UCA0MCTLW = 0xF701;
    }




    UCA0CTLW0 &= ~UCSWRST;   // Release from reset
    UCA0IE |= UCRXIE;        // Enable RX interrupt
}



