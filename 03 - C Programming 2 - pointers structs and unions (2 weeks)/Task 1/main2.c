#include <p24FJ128GA010.h>

_CONFIG2( FNOSC_FRCPLL & OSCIOFNC_OFF );	// Internal oscillator - 4xPLL giving 16 MIPS
											// pin RC15 has the oscillator
//Declare global functions using in main.c
extern void do_delay_badly(const unsigned int D);
extern void update_display(const unsigned int uPattern);							
extern unsigned int xor_with_mask(const unsigned int pattern, const unsigned int mask );
	
int main()
{
	//Configure the device to use the internal oscillator
	OSCCONbits.COSC  = 1u;	// Internal oscillator with PLL
	CLKDIVbits.RCDIV = 0u;	//Internal oscillator not divided (8MHz)
	CLKDIVbits.DOZEN =0;	//No post scaling
	CLKDIVbits.DOZE  =0;	//
	
	//Local variables here
	unsigned int n, uOutputPattern;
	
	//set up ports
	TRISA = 0xFF00;			//Least-significant 4 bits are digital outputs
	   
	//Main Loop
	while (1)
	{
		uOutputPattern = 0x0000;			//Initial value
		update_display(uOutputPattern);
		
		//EXAMPLE - XOR all bits 4 times
		for (n=0; n<4; n++) {
			uOutputPattern = xor_with_mask(uOutputPattern, 0b11111111);		//toggle alternate bits using an XOR
			update_display(uOutputPattern);
		}	

		//PATTERN 1
		for (n=0; n<4; n++) {
			uOutputPattern = xor_with_mask(uOutputPattern, 0b01010101);		//toggle alternate bits using an XOR
			update_display(uOutputPattern);
		}
		
		//PATTERN 2
		for (n=0; n<4; n++) {
			uOutputPattern = xor_with_mask(uOutputPattern, 0b10101010);		//toggle alternate bits using an XOR
			update_display(uOutputPattern);
		}	
		
	} //end while
	
	return 0;
}


