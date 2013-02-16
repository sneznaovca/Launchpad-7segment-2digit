#include <msp430g2553.h>
#include "7segment-direct.h";

/**
 * example usage 7segment-direct connect, display number from 0 to 99
 */

int main(void) {
	WDTCTL = WDTPW + WDTHOLD;		// Stop watchdog timer

	unsigned int j;
	volatile unsigned int i;	// volatile to prevent optimization

	seg7DirInit();

	for(;;) {

		for(j=0;j<=99;j++){

			seg7DirDispNumb(j);

			//sw delay
			i = 10000000;
			do i--;
			while(i != 0);


		}

	}
}
