#include <p24FJ128GA010.h>

//_CONFIG2( FNOSC_FRCPLL & OSCIOFNC_OFF );	// Internal oscillator - 4xPLL giving 16 MIPS
#pragma config FNOSC = FRCPLL, OSCIOFNC = OFF											// pin RC15 has the oscillator

//For this to work with Proteus VSM, do the following:
// The  Proteus VSM Viewer plugin must be installed
// Under project properties, make sure the VSM debugger is selected
// Change the animation settings for the VSM file:
//    timeset per frame: 10ns
//    single step time: 10ns

int main()
{
	//Configure the device to use the internal oscillator
//	OSCCONbits.COSC  = 1u;	// Internal oscillator with PLL
//	CLKDIVbits.RCDIV = 0u;	//Internal oscillator not divided (8MHz)
//	CLKDIVbits.DOZEN =0;	//No post scaling
//	CLKDIVbits.DOZE  =0;	//
	
	//Local variables
	unsigned int x = 0;
	unsigned int n=0;
	
	//Set the LSB of port A to be outputs
	TRISA = 0xFF00;					
	
	//Main Loop
	while (1)
	{
		PORTA = x++;				//WRITE x to h/w port A
		for (n=0; n<32767u; n++) {
			asm ("nop");			//Do nothing for one instruction cycle	
		}	
	}
	return 0;
}
