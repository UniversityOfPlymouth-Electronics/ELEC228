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
	char strMystring[10];				//Storage for a string
	//char strMystring[] = "Hello world";
	
	unsigned int n;
	
	//Set the LSB of port A to be outputs
	TRISA = 0xFF00;					
	
	//Fill the string with some values
   	for (n=0; n<10; n++) {
    	strMystring[n] = 'x';			// strMystring is an array of characters, indexed by 'n'
   	} 	
   
	//Main Loop
	n = 0;                  			//I am going to reuse n as an index variable
	while (1)
	{
		asm("nop");
      	      
	} //end while
	
	return 0;
}
