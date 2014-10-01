#include <p24FJ128GA010.h>

//_CONFIG2( FNOSC_FRCPLL & OSCIOFNC_OFF );	// Internal oscillator - 4xPLL giving 16 MIPS
#pragma config FNOSC = FRCPLL, OSCIOFNC = OFF

int main()
{
	//Configure the device to use the internal oscillator
	OSCCONbits.COSC  = 1u;	// Internal oscillator with PLL
	CLKDIVbits.RCDIV = 0u;	//Internal oscillator not divided (8MHz)
	CLKDIVbits.DOZEN =0;	//No post scaling
	CLKDIVbits.DOZE  =0;	//
	
	//Local variables
	unsigned int x = 0;
	//unsigned int n=0;
	
	//Set the LSB of port A to be outputs
	TRISA = 0xFF00;					
	
	//Main Loop
	while (1) {
		PORTA = x++;				//WRITE x to h/w port A
	}	

	return 0;
}
