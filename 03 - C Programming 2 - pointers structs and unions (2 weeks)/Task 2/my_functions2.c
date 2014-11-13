#include <p24FJ128GA010.h>
#include "my_functions.h"

void xor_with_mask(pattern* m )		//Note that m is an 'address'  (pointer)
{
	//Overwrite data passed by reference
	m->bit_pattern = (m->bit_pattern ^ m->bit_mask);
}	


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




//Update the display and delay
void update_display(const pattern m)
{
	PORTA = m.bit_pattern;		//
	do_delay_badly(1000);		//Call global function
}
