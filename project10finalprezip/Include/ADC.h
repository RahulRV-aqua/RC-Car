/*
 * ADC.h
 *
 *  Created on: Mar 2, 2025
 *      Author: rahul
 */

#ifndef ADC_H_
#define ADC_H_

volatile unsigned int ADC_Left_Det;
volatile unsigned int ADC_Right_Det;
extern volatile unsigned int ADC_Channel;
volatile unsigned int ADC_Thumb;

void Init_ADC(void);



#endif /* ADC_H_ */
