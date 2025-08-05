/*
 * clocks.h
 *
 *  Created on: Jan 30, 2025
 *      Author: rahul
 */

#ifndef CLOCKS_H_
#define CLOCKS_H_

#define MCLK_FREQ_MHZ           (8) // MCLK = 8MHz
#define CLEAR_REGISTER     (0X0000)

void Init_Clocks(void);
void Software_Trim(void);



#endif /* CLOCKS_H_ */
