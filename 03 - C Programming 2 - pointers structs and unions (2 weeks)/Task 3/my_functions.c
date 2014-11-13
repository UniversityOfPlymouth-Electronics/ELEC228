#include <p24FJ128GA010.h>


//Very crude delay (depends on compiler settings and clock speed)
void do_delay_badly(const unsigned int D)
{
	unsigned int n,m;		//loop indeces
	for (n=0; n<D; n++) {
		for (m=0; m<D; m++) {
			asm("nop");		//waste a single instruction cycle
		} // end inner-for-loop	
	} //end of outer for-loop
} //end of function	

