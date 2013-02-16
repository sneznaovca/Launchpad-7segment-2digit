#ifndef SEG7_DIR_H_
#define SEG7_DIR_H_

#include <msp430g2553.h>

//define A-G segments pins
#define SEG7_A BIT0 //PORT1
#define SEG7_B BIT1
#define SEG7_C BIT2
#define SEG7_D BIT3
#define SEG7_E BIT4
#define SEG7_F BIT5
#define SEG7_G BIT6

//multiplex connected, define digit selector
#define SEG7_DIG1 BIT0 //PORT 2
#define SEG7_DIG2 BIT1

void seg7DirInit();
void seg7DirDispDigit(int digit, int position);
void seg7DirDispNumb(int number);

#endif // SEG7_DIR_H_
