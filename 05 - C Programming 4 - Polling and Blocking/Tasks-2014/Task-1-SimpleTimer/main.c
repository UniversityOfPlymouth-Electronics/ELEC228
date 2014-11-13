#include <p24FJ128GA010.h>

_CONFIG2( FNOSC_FRCPLL & OSCIOFNC_OFF );	// Internal oscillator - 4xPLL giving 16 MIPS
											// pin RC15 has the oscillator
												
int main()
{
	//Configure the device to use the internal oscillator
	OSCCONbits.COSC  = 1u;	// Internal oscillator with PLL
	CLKDIVbits.RCDIV = 0u;	//Internal oscillator not divided (8MHz)
	CLKDIVbits.DOZEN =0;	//No post scaling
	CLKDIVbits.DOZE  =0;	//
	
	//Local variables here
	unsigned int a = 0b00101010;
	unsigned int b = 0b00001111;
	unsigned int y = 0;

	//set up ports
	TRISA = 0xFF00;			//Least-significant 8 bits are digital outputs
	PORTA = y;				//Write zero to the display
	   
	//Main Loop
	while (1)
	{
		asm("nop");
		PORTA = y;		

	} //end while
	
	return 0;
}


