#include <p24FJ128GA010.h>
#include <stdlib.h>

_CONFIG2( FNOSC_FRCPLL & OSCIOFNC_OFF );	// Internal oscillator - 4xPLL giving 16 MIPS
											// pin RC15 has the oscillator

//global variables here

int main()
{
	//Configure the device to use the internal oscillator
	OSCCONbits.COSC  = 1u;	// Internal oscillator with PLL
	CLKDIVbits.RCDIV = 0u;	//Internal oscillator not divided (8MHz)
	CLKDIVbits.DOZEN =0;	//No post scaling
	CLKDIVbits.DOZE  =0;	//
	
	//Local variables here
	int x;

	//set up ports
	TRISA = 0xFFF0;		//Least-significant 4 bits are digital outputs
	PORTA = 0x0000;		//Write zero to the display
	   
	//Main Loop
	while (1)
	{

		//WRITE CODE HERE 
		x = rand();
	

	} //end while
	
	return 0;
}
