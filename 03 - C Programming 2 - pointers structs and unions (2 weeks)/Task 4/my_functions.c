#include <p24FJ128GA010.h>


//Very crude delay (depends on compiler settings and clock speed)
unsigned int do_delay_badly(const unsigned int D)
{
	unsigned int n,m;		//loop indeces
	for (n=0; n<D; n++) {
		for (m=0; m<D; m++) {
			if (PORTB == 0x00000001)	//Continuously poll PORTB for an input
				return 1;				//If a button was pressed, immediately return a 1 (exit the function at this point)
		} // end inner-for-loop	
	} //end of outer for-loop
	return 0;		//If we've reached this point, no button was pressed
} //end of function	

