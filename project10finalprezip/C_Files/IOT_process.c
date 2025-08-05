/*
 * IOT_process.c
 *
 *  Created on: Apr 8, 2025
 *      Author: rahul
 */

#include "include\macros.h"

int IOT_parse =0;
int IOT_line = 0;
unsigned int move_ip = 1;
unsigned int pad_number =1;

void IOT_Process(void){               // Process IOT messages
    //int i;
    unsigned int iot_rx_wr_temp;
    iot_rx_wr_temp = iot_rx_wr;

    if(iot_rx_wr_temp != iot_rx_rd){    // Determine if IOT is available
        IOT_Data[line][character] = IOT_Ring_Rx[iot_rx_rd++];

        if(iot_rx_rd >= sizeof(IOT_Ring_Rx)){
            iot_rx_rd = BEGINNING;
        }

        if(IOT_Data[line][character] == 0x0A){ //check if char is new line
            character = 0;
            IOT_line = line;                   // save line
            line++;                            //next line in buffer
            if(line >= 4){
                line = 0;
            }
            int i;
            if (IOT_Data[IOT_line][15] == 'E'){
                strcpy(display_line[0], "  EXIT    ");
                display_changed = TRUE;
                exit_flag = 1;
                char command_str[5];
                memcpy(command_str, &IOT_Data[IOT_line][15],5);
                display_line[3][5] = ' ';
                strncpy(display_line[3], command_str, 5);
                display_changed = TRUE;
                //timeval = Curr_timeval;
                command_in_process = 0;
            }
            if (command_check_iot && (!command_in_process)){
                if ((IOT_Data[IOT_line][11] == '0') && (IOT_Data[IOT_line][12] == '9') && (IOT_Data[IOT_line][13] == '0') && (IOT_Data[IOT_line][14] == '4')){
                    command_check_iot = 0;
                    if (move_ip){
                        time_start_point = Curr_timeval;
                        timer_active = 1;
                        enable_timer = 1;

                        strcpy(display_line[1], display_line[2]);
                        strcpy(display_line[2], display_line[3]);
                        display_changed = TRUE;
                        move_ip = 0;
                    }
                    if (IOT_Data[IOT_line][15] == 'F'){
                        char period_str[5];
                        memcpy(period_str, &IOT_Data[IOT_line][16],4);
                        period_str[4] = '\0';
                        int y = atoi(period_str);
                        x = (y * 5);
                        char command_str[5];

                        movement = 1 ;
                        memcpy(command_str, &IOT_Data[IOT_line][15],5);
                        display_line[3][5] = ' ';
                        strncpy(display_line[3], command_str, 5);
                        display_changed = TRUE;
                        timeval = Curr_timeval;
                        RIGHT_FORWARD_SPEED = 14000;
                        LEFT_FORWARD_SPEED  = 50000;
                       // forward_on_slow();
                        command_in_process = 1;
                        forward_flag = 1;
                    }
                    if (IOT_Data[IOT_line][15] == 'B'){
                        char period_str[5];
                        memcpy(period_str, &IOT_Data[IOT_line][16],4);
                        period_str[4] = '\0';
                        int y = atoi(period_str);
                        x = (y * 5);
                        movement = 1 ;
                        char command_str[5];
                        memcpy(command_str, &IOT_Data[IOT_line][15],5);
                        display_line[3][5] = ' ';
                        strncpy(display_line[3], command_str, 5);
                        display_changed = TRUE;
                        timeval = Curr_timeval;
                        reverse_on();
                        command_in_process = 1;
                        reverse_flag = 1;
                    }
                    if (IOT_Data[IOT_line][15] == 'R'){
                        char period_str[5];
                        memcpy(period_str, &IOT_Data[IOT_line][16],4);
                        period_str[4] = '\0';
                        int y = atoi(period_str);
                        x = y;
                        movement = 1 ;
                        char command_str[5];
                        memcpy(command_str, &IOT_Data[IOT_line][15],5);
                        display_line[3][5] = ' ';
                        strncpy(display_line[3], command_str, 5);
                        display_changed = TRUE;
                        timeval = Curr_timeval;
                        anti_clockwise_spin();
                        command_in_process = 1;
                        right_spin_flag = 1;
                    }
                    if (IOT_Data[IOT_line][15] == 'L'){
                        char period_str[5];
                        memcpy(period_str, &IOT_Data[IOT_line][16],4);
                        period_str[4] = '\0';
                        int y = atoi(period_str);
                        x = y;
                        movement = 1 ;
                        char command_str[5];
                        memcpy(command_str, &IOT_Data[IOT_line][15],5);
                        display_line[3][5] = ' ';
                        strncpy(display_line[3], command_str, 5);
                        display_changed = TRUE;
                        timeval = Curr_timeval;
                        clockwise_spin();

                        command_in_process = 1;
                        left_spin_flag = 1;
                    }
                    if (IOT_Data[IOT_line][15] == 'A'){
                        if(pad_number >8){
                            pad_number = 0;
                        }
                        char padBuffer[10] = "ARRIVED 0 ";
                        padBuffer[9] = '0' + pad_number;
                        strncpy (display_line[0], padBuffer, 10);
                        display_changed = TRUE;
                        pad_number++ ;

                   }
                   if (IOT_Data[IOT_line][15] == 'Z'){
                       pad_eight_flag = TRUE;
                       command_in_process = 0;
                   }
                  if (IOT_Data[IOT_line][15] == 'E'){
                       strcpy(display_line[0], "  EXIT    ");
                       display_changed = TRUE;
                       exit_flag = 1;
                       char command_str[5];
                       memcpy(command_str, &IOT_Data[IOT_line][15],5);
                       display_line[3][5] = ' ';
                       strncpy(display_line[3], command_str, 5);
                       display_changed = TRUE;
                       //timeval = Curr_timeval;
                       command_in_process = 0;
                  }

            }
        }
        }
        else{

            switch(character){
            case  0:
                if(IOT_Data[line][character] == '+'){   // Got "+"
                    //test_Value++;
                    IOT_parse = 1;                      // is it a vlid response
                }

            break;
            case  1:

                // GRN_LED_ON;
            break;

            case  4:
                if(IOT_Data[line][character] == 'y'){   // Got read"y"
                  //  for(i=0; i<sizeof(AT); i++){
                  //      iot_TX_buf[i] = AT[i];
                   // }
                        //UCA0IE |= UCTXIE;
                        boot_state = 1;                     // flag says IOT it booted up and ready

                    // RED_LED_ON;
                }
            break;

            case  5:
                if(IOT_Data[line][character] == 'G'){      // Got IP
                   // for(i=0; i<sizeof(ip_mac); i++){
                    //    iot_TX_buf[i] = ip_mac[i];
                    //}
                    ready_done  = 1;
                    //UCA0IE |= UCTXIE;
                }
            break;

            case  9:
                //if(IOT_Data[line][character] == '^'){
                //    command_check_iot = 1;
                    //movement = 1;
                //}
            break;

            case  10:
                if(IOT_Data[line][character] == 'I'){
                    ip_address_found = 1;
                }
                else if ((IOT_Data[line][character] == '^') ){
                    command_check_iot = 1;
                    //timeval = Curr_timeval;
                    //Display_Update(0,0,0,0);
                }
            break;
            default: break;
        }
            character++;
    }
   }
}

