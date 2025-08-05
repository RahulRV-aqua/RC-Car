//------------------------------------------------------------------------------
//
//  Description: This file contains the Main Routine - "While" Operating System
//
//  Jim Carlson
//  Jan 2023
//  Built with Code Composer Version: CCS12.4.0.00007_win64
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

#include  <string.h>

#include  "include\macros.h"


volatile unsigned int ADC_display= 0;
extern volatile unsigned int timer_active = 0;

int command_received_iot = 0;
int command_check_iot = 0;

int display_row = 0 ;
int send_back = 0;
int command_check = 0;
char transmit_array[32];
char Process_Buffer[4][32];
int command_received = 0;
int second_flag = 0;
int third_flag = 0;
int fourth_flag = 0;
int fifth_flag = 0;
int sixth_flag = 0;
int seventh_flag = 0;
int ip_address_found;

char temp_iot_array[55];

int boot_state = 0;
int ready_done = 0;

int call_once = 0;
int movement = 0;

int command_in_process = 0;
int forward_flag = 0;
int reverse_flag = 0;
int right_spin_flag = 0;
int left_spin_flag = 0;
int x = 0;

int enable_timer = 0;
unsigned int pad_eight_flag = 0;
int CHECK_ADC_VALUE = 0;

int right_side = 1;
int left_side = 1;
unsigned int white_line_value = 0;
unsigned int black_line_value = 0;

int exit_flag = 0;
int ping_ready = 0;
volatile unsigned int ping_count = 0;

char store_line_one[10] = "          ";
char store_line_two[10] = "          ";
char store_line_three[10] = "          ";
char store_line_four[10] = "          ";
// ALL Function Prototypes and global variables declared in macros.h!!!!!



//void main(void){
void main(void){
//    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

//------------------------------------------------------------------------------
// Main Program
// This is the main routine for the program. Execution of code starts here.
// The operating system is Back Ground Fore Ground.
//
//------------------------------------------------------------------------------
  PM5CTL0 &= ~LOCKLPM5;
// Disable the GPIO power-on default high-impedance mode to activate
// previously configured port settings


  Init_Ports();                        // Initialize Ports
  Init_Clocks();                       // Initialize Clock System
  Init_Conditions();                   // Initialize Variables and Initial Conditions
  Init_Timers();                       // Initialize Timers
  Init_DAC();
  Init_LCD();                          // Initialize LCD
  Init_ADC();                          // Initialize ADC
  Init_Serial_UCA0();                  // Initialize TRANSMIT AND RECEIVE
  Init_Serial_UCA1();

//P2OUT &= ~RESET_LCD;
  // Place the contents of what you want on the display, in between the quotes
// Limited to 10 characters per line
  strcpy(display_line[0], "          ");
  strcpy(display_line[1], "          ");
  strcpy(display_line[2], "LOADING...");
  strcpy(display_line[3], "          ");
  display_changed = TRUE;
  Display_Update(0,0,0,0);
  wheel_move = 0;
  forward = TRUE;
  event = NONE;
  //char Splash = 1;  // 5 second splash code

//------------------------------------------------------------------------------
// Begining of the "While" Operating System
//------------------------------------------------------------------------------
  while(ALWAYS) {                      // Can the Operating system run
//    Carlson_StateMachine();            // Run a Time Based State Machine

    IOT_Process();
/*    if(ping_ready){
        if (ping_count < 16){
            command_in_process = 0;
        }
        else if (ping_count > 15){
            int j;
            char ping[26] = "AT+PING=\"www.google.com\"\r\n";
             for(j=0; j<sizeof(ping); j++){
                 iot_TX_buf[j] = ping[j];
            }
            ping_count = 0;
            UCA0IE |= UCTXIE;
            command_in_process = 1;
        }
    }*/

    Switches_Process();                // Check for switch state change
    Display_Process();                 // Update Display
    Wheels_Process();
    //goku_state_mach();
    Display_Timer(); // remove for trial
    process_commands();
    pad_eight_process();

    if (Curr_timeval > 5){
        P3OUT |= IOT_EN_CPU;
    }

    /*if (Splash && (Curr_timeval >25)) {
          strcpy(display_line[0], "          ");
          strcpy(display_line[1], "          ");
          strcpy(display_line[2], "Baud Rate:");
          strcpy(display_line[3], "          ");
          display_changed = TRUE;
          Splash = 0;
      }*/
    if (usb_rx_ring_rd != usb_rx_ring_wr) {
        Process_Buffer[pb_index_row][pb_index_column] = USB_Char_Rx[usb_rx_ring_rd];
            if (USB_Char_Rx[usb_rx_ring_rd] == '\r') {
                display_row = pb_index_row;   // save the row index for displaying
                pb_index_row++;               // move to next row
                if (pb_index_row >= ROWS) pb_index_row = 0;
                pb_index_column = 0;             // reset the column to 0

                // Clear the following row
                int i;
                for (i = 0; i < COLUMNS; i++) {                 // clear the next line
                   Process_Buffer[pb_index_row][i] = 0x00;
                }               // display the message on the process buffer

                command_received = 1;


            }
            else {
                // get character from ring buffer to process buffer
                pb_index_column++;     // increment process buffer pointer
                // dont check for the end of column (assume that process buffer long enough to store any message
            }

            usb_rx_ring_rd++;   // increment ring rd index
            if (usb_rx_ring_rd >= (sizeof(USB_Char_Rx))) usb_rx_ring_rd = BEGINNING;   // Circular buffer back to beginning

        }


    if (CHECK_ADC_VALUE){
            HEXtoBCD(ADC_Left_Det);
            adc_line(3, 3);
            HEXtoBCD(ADC_Right_Det);
            adc_line(4, 3);
            display_changed = TRUE;
    }



    //function to check flags
    if( boot_state && ready_done){
         int j;
          for(j=0; j<sizeof(AT); j++){
              iot_TX_buf[j] = AT[j];
          }
          boot_state = 0;
          ready_done = 0;
          second_flag = 1;
          timeval = Curr_timeval;
          UCA0IE |= UCTXIE;
    }

    if(IOT_parse && second_flag && (Curr_timeval > timeval + 5)){
        char ssid_buffer[10] = {'\0'};
        int j;
        int i = 0;
        for (j=8; j<18; j++){
            if (IOT_Data[1][j] == 0x22){
               break;
            }
            ssid_buffer[i] = IOT_Data[1][j];
            i++;
        }
        strncpy (display_line[0], ssid_buffer, 10);
        display_changed = TRUE;
        //Display_Update(0,0,0,0);
        second_flag = 0;
        third_flag = 1;
        IOT_parse = 0;
        timeval = Curr_timeval;
    }



    if ( third_flag && (Curr_timeval > timeval + 3)){
        int j;
        char second[10] = "AT+CIFSR\r\n";
         for(j=0; j<sizeof(second); j++){
             iot_TX_buf[j] = second[j];
        }
        third_flag = 0;
        fourth_flag = 1;
        timeval = Curr_timeval;
        UCA0IE |= UCTXIE;
    }

    if (fourth_flag && ip_address_found && (Curr_timeval > timeval + 5)){
        strncpy (temp_iot_array , IOT_Data[1] , 55);
        int i = 1;
        int z = 1;
        int j ;
        int group_count = 0;
        char ip_up[10]   = "          ";
        char ip_down[10] = "          ";

        for (j=14; j<28; j++){
            if (temp_iot_array[j] == 0x22){
                break;
            }
            if (group_count < 2){
                ip_up[i] = temp_iot_array[j];
                i++;
            }

            if (IOT_Data[1][j] == 0x2E){
               group_count++;
            }

            if (group_count >= 2){
                ip_down[z] = temp_iot_array[j];
                z++;
            }
        }
        strcpy(display_line[1], "IP ADDRESS");
        strncpy (display_line[2], ip_up, 10);
        strncpy (display_line[3], ip_down, 10);
        display_changed = TRUE;
        //Display_Update(0,0,0,0);
        fourth_flag = 0;
        fifth_flag = 1 ;
        ip_address_found = 0;
        timeval = Curr_timeval;

    }

    if ( fifth_flag && (Curr_timeval > timeval + 5)){
        int j;
        char second[13] = "AT+CIPMUX=1\r\n";
         for(j=0; j<sizeof(second); j++){
             iot_TX_buf[j] = second[j];
        }
        fifth_flag = 0;
        sixth_flag = 1;
        timeval = Curr_timeval;
        UCA0IE |= UCTXIE;
    }

    if (sixth_flag && (Curr_timeval > timeval + 5)){
        int j;
        char second[21] = "AT+CIPSERVER=1,9004\r\n";
         for(j=0; j<sizeof(second); j++){
             iot_TX_buf[j] = second[j];
        }
        sixth_flag = 0;
        seventh_flag = 1;
        timeval = Curr_timeval;
        UCA0IE |= UCTXIE;
        strcpy(display_line[0], " WAITING  ");
        strcpy(display_line[1], "FOR INPUT ");
        display_changed = TRUE;

    }

    if (seventh_flag && (Curr_timeval > timeval + 5)){
        ping_ready = 1;
        seventh_flag = 0;
    }

    if(movement){
        if(forward_flag){
            if (Curr_timeval > (timeval + x)){
                strcpy(display_line[0], "          ");
                display_changed = TRUE;
                motor_off();
                command_in_process = 0;
                forward_flag = 0;
            }
        }
        if(reverse_flag){
            if (Curr_timeval > (timeval + x) ){
                strcpy(display_line[0], "          ");
                display_changed = TRUE;
                motor_off();
                command_in_process = 0;
                reverse_flag = 0;
            }
        }
        if(right_spin_flag){
            if (Curr_timeval > (timeval + x) ){
                strcpy(display_line[0], "          ");
                display_changed = TRUE;
                motor_off();
                command_in_process = 0;
                right_spin_flag = 0;
            }
        }
        if(left_spin_flag){
            if (Curr_timeval > (timeval + x) ){
                strcpy(display_line[0], "          ");
                display_changed = TRUE;
                motor_off();
                command_in_process = 0;
                left_spin_flag = 0;
            }
        }


    }








  }


// check if rd!= wr
/*    if (usb_rx_ring_rd != usb_rx_ring_wr) {
            Process_Buffer[pb_index_row][pb_index_column] = USB_Char_Rx[usb_rx_ring_rd];
            usb_rx_ring_rd++;
            // get character from ring buffer to process buffer
            if(usb_rx_ring_rd >= (sizeof(USB_Char_Rx))){
                usb_rx_ring_rd = BEGINNING;
            }
            pb_index_column++;
            if (USB_Char_Rx[usb_rx_ring_rd] == '\n') {
                display_row = pb_index_row;   // save the row index for displaying
                pb_index_row++;               // move to next row
                if (pb_index_row >= ROWS) pb_index_row = 0;
                pb_index_column = 0;             // reset the column to 0
                int i;
                for (i = 0; i < COLUMNS; i++) {                 // clear the next line
                    Process_Buffer[pb_index_row][i] = 0x00;
                }
                // display the message on the process buffer
                strncpy(display_line[0], Process_Buffer[display_row], 10);
                display_changed = TRUE;
            }
        }

  }
  */

 /*   if (display_serial) {
              display_serial = 0;
              strcpy(display_line[0], USB_Char_Rx);
              display_changed = TRUE;
              UCA1IE |= UCRXIE;

          }
          if (transmit_ncsu_flag) {
                        transmit_ncsu_flag = 0;
                        pb_index = 0;                // Start from beginning
                        UCA1TXBUF = ncsu_msg[0];     // Kick off transmission
                        UCA1IE |= UCTXIE;            // Enable TX interrupt
                          }
          Display_Process();                 // Update Display
          P3OUT ^= TEST_PROBE;               // Change State of TEST_PROBE OFF

*/

//------------------------------------------------------------------------------

  }

void Carlson_StateMachine(void){
    switch(Time_Sequence){
      case 250:                        //
        if(one_time){
          Init_LEDs();
          lcd_BIG_mid();
          display_changed = 1;
          one_time = 0;
        }
        Time_Sequence = 0;             //
        break;
      case 200:                        //
        if(one_time){
//          P1OUT &= ~RED_LED;            // Change State of LED 4
          P6OUT |= GRN_LED;            // Change State of LED 5
          one_time = 0;
        }
        break;
      case 150:                         //
        if(one_time){
          P1OUT |= RED_LED;            // Change State of LED 4
          P6OUT &= ~GRN_LED;            // Change State of LED 5
          one_time = 0;
        }
        break;
      case 100:                         //
        if(one_time){
//          lcd_4line();
          lcd_BIG_bot();
          P6OUT |= GRN_LED;            // Change State of LED 5
          display_changed = 1;
          one_time = 0;
        }
        break;
      case  50:                        //
        if(one_time){
          one_time = 0;
        }
        break;                         //
      default: break;
    }
}

