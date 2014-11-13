#include <p24FJ128GA010.h>

_CONFIG2( FNOSC_FRCPLL & OSCIOFNC_OFF )	// Internal oscillator - 4xPLL giving 16 MIPS
											// pin RC15 has the oscillator

// GLOBAL and CONST VARIABLES CAN GO HERE

int main()
{
	//Configure the device to use the internal oscillator
	OSCCONbits.COSC  = 1u;	// Internal oscillator with PLL
	CLKDIVbits.RCDIV = 0u;	//Internal oscillator not divided (8MHz)
	CLKDIVbits.DOZEN =0;	//No post scaling
	CLKDIVbits.DOZE  =0;	//
	
	//Local variables
	int x[] = {10,20,30,40,50,60,70,80,90,100};
	char c = 'x';
	unsigned int n=123;
	double f = 3.1415926;
	int y[] = {100,200,300};
	
	//Set the LSB of port A to be outputs
	TRISA = 0xFF00;					
	

	//Main Loop
	while (1)
	{
		asm("nop");

		//The following code is simply there to fool the compiler
		int iDummy;
		char cDummy;
		float fDummy;
		
		x[0]=123;		//modify the contents of the array x at index 0
		x[9]=456;		// "" for index 9
		x[10] = 0;		// Buffer overflow

		iDummy = x[0];
		iDummy = y[0];
		iDummy = (int)n;
		cDummy = c;
		fDummy = f;
		    
	} //end while
	
	return 0;
}
