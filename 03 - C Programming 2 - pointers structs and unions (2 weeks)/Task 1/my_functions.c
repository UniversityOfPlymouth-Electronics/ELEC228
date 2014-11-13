#include <p24FJ128GA010.h>

unsigned int xor_with_mask(const unsigned int pattern, const unsigned int mask )
{
	unsigned int y;
	y =pattern ^ mask;
	return y;
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
void update_display(const unsigned int uPattern)
{
	PORTA = uPattern;			//This function can see the global variable uOutputPattern
	do_delay_badly(1000);		//Call global function
}
