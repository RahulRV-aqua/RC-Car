/*
 * display.c
 *
 *  Created on: Jan 30, 2025
 *      Author: rahul
 */

#include "include\macros.h"

//displayupdate .h problem check it out!!!!!!!

void Display_Process(void){
  if(update_display){
    update_display = 0;
    if(display_changed){
      display_changed = 0;
      Display_Update(0,0,0,0);
    }
  }
}


