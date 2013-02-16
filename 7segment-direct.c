#include "7segment-direct.h";

unsigned int seg7Numb_dig1; //store first digit for double digit number
unsigned int seg7Numb_dig2; //store second digit for double digit number
unsigned int seg7Numb_state; //determine order digits for display

/**
 * Inicialization 7segment, 2digit display
 * Set output mode, enable timer interupt
 *
 * @return void
 */
void seg7DirInit(){

	P1DIR |= SEG7_A + SEG7_B + SEG7_C + SEG7_D + SEG7_E + SEG7_F + SEG7_G; //set output 7segment
	P2DIR |= SEG7_DIG1 + SEG7_DIG2; //set output digit selection

	CCTL0 = CCIE; //enable timer interupt
	__enable_interrupt(); //enable interupt

}

/**
 * Display single digit on select position
 *
 * @param digit digit for display
 * @param position position on 7segment
 * @return void
 */
void seg7DirDispDigit(int digit, int position){

	switch(position){
	case 1:
		P2OUT |=SEG7_DIG1;
		P2OUT &= ~(SEG7_DIG2);
		break;
	case 2:
		P2OUT |=SEG7_DIG2;
		P2OUT &= ~(SEG7_DIG1);
		break;
	}

	switch(digit){
	case 0:
		P1OUT &= ~(SEG7_A + SEG7_B + SEG7_C + SEG7_D + SEG7_E + SEG7_F);
		P1OUT |=  (SEG7_G);
		break;
	case 1:
		P1OUT &= ~(SEG7_B + SEG7_C);
		P1OUT |=  (SEG7_A + SEG7_D + SEG7_E + SEG7_F + SEG7_G);
		break;
	case 2:
		P1OUT &= ~(SEG7_A + SEG7_B + SEG7_D + SEG7_E + SEG7_G);
		P1OUT |=  (SEG7_F + SEG7_C);
		break;
	case 3:
		P1OUT &= ~(SEG7_A + SEG7_D + SEG7_B + SEG7_C + SEG7_G);
		P1OUT |=  (SEG7_E + SEG7_F);
		break;
	case 4:
		P1OUT &= ~(SEG7_B + SEG7_C + SEG7_F + SEG7_G);
		P1OUT |=  (SEG7_A + SEG7_D + SEG7_E);
		break;
	case 5:
		P1OUT &= ~(SEG7_A + SEG7_D + SEG7_F + SEG7_C + SEG7_G);
		P1OUT |=  (SEG7_E + SEG7_B);
		break;
	case 6:
		P1OUT &= ~(SEG7_A + SEG7_D + SEG7_F + SEG7_C + SEG7_G + SEG7_E);
		P1OUT |=  (SEG7_B);
		break;
	case 7:
		P1OUT &= ~(SEG7_A + SEG7_B + SEG7_C);
		P1OUT |=  (SEG7_D + SEG7_E + SEG7_F + SEG7_G);
		break;
	case 8:
		P1OUT &= ~(SEG7_A + SEG7_B + SEG7_C + SEG7_D + SEG7_E + SEG7_F + SEG7_G);
		break;
	case 9:
		P1OUT &= ~(SEG7_A + SEG7_B + SEG7_C + SEG7_D + SEG7_G + SEG7_F);
		P1OUT |=  (SEG7_E);
		break;
	}
}

/**
 * Display any number between 0-99
 *
 * @param number number for display
 * @return void
 */
void seg7DirDispNumb(int number){

	//for double digit number use timer
	if(number>=10){
		seg7Numb_dig2 = number%10;
		seg7Numb_dig1 = number/10;
		TACCR0=10000; //100hz
		TACTL = TASSEL_2 + MC_1; //set SMCLK, upmode
	}else{
		TACTL = 0; //stop timer
		seg7DirDispDigit(number,2);
	}

}


/**
 * timer for use in double digit numbers
 */
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
	if(seg7Numb_state){
		seg7DirDispDigit(seg7Numb_dig1,1);
		seg7Numb_state=0;
	}else{
		seg7DirDispDigit(seg7Numb_dig2,2);
		seg7Numb_state=1;
	}
}

