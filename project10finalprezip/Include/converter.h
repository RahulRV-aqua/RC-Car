/*
 * converter.h
 *
 *  Created on: Mar 2, 2025
 *      Author: rahul
 */

#ifndef CONVERTER_H_
#define CONVERTER_H_

#include "include\macros.h"

void HEXtoBCD(int hex_value);
void adc_line(char line, char location);

volatile unsigned char  adc_char[4];




#endif /* CONVERTER_H_ */
