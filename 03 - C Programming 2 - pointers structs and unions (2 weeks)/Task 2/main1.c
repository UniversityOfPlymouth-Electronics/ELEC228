#include <p24FJ128GA010.h>
#include "my_functions.h"

_CONFIG2( FNOSC_FRCPLL & OSCIOFNC_OFF );	// Internal oscillator - 4xPLL giving 16 MIPS
											// pin RC15 has the oscillator
//Declare global functions using in main.c
extern void do_delay_badly(const unsigned int D);
void update_display(const pattern m);							
extern unsigned int xor_with_mask(pattern m );
	
int main()
{
	//Configure the device to use the internal oscillator
	OSCCONbits.COSC  = 1u;	// Internal oscillator with PLL
	CLKDIVbits.RCDIV = 0u;	//Internal oscillator not divided (8MHz)
	CLKDIVbits.DOZEN =0;	//No post scaling
	CLKDIVbits.DOZE  =0;	//
	
	//Local variables here
	unsigned int n;
	pattern outputPattern;
	
	//set up ports
	TRISA = 0xFF00;			//Least-significant 4 bits are digital outputs
	   
	//Main Loop
	while (1)
	{
		outputPattern.bit_pattern = 0x0000;			//Initial value
		update_display(outputPattern);
		
		//EXAMPLE - XOR all bits 4 times
		outputPattern.bit_mask = 0b11111111;	
		for (n=0; n<4; n++) {
			outputPattern.bit_pattern = xor_with_mask(outputPattern);		//toggle alternate bits using an XOR
			update_display(outputPattern);
		}	

		//PATTERN 1
		outputPattern.bit_mask = 0b01010101;
		for (n=0; n<4; n++) {
			outputPattern.bit_pattern = xor_with_mask(outputPattern);		//toggle alternate bits using an XOR
			update_display(outputPattern);
		}
		
		//PATTERN 2
		outputPattern.bit_mask = 0b10101010;
		for (n=0; n<4; n++) {
			outputPattern.bit_pattern = xor_with_mask(outputPattern);		//toggle alternate bits using an XOR
			update_display(outputPattern);
		}	
		
	} //end while
	
	return 0;
}


