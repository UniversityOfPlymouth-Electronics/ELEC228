#include <p24FJ128GA010.h>

_CONFIG2( FNOSC_FRCPLL & OSCIOFNC_OFF )	// Internal oscillator - 4xPLL giving 16 MIPS
											// pin RC15 has the oscillator


int main()
{
	//Configure the device to use the internal oscillator
	OSCCONbits.COSC  = 1u;	// Internal oscillator with PLL
	CLKDIVbits.RCDIV = 0u;	//Internal oscillator not divided (8MHz)
	CLKDIVbits.DOZEN =0;	//No post scaling
	CLKDIVbits.DOZE  =0;	//
	
	//Local variables
	unsigned char uOutputPattern;			//Stores the pattern output on the LEDs
	unsigned char mydata[8];				//Array used as a look-up table
	unsigned int n;							//This will be used for looping
	
	//Set the LSB of port A to be outputs
	TRISA = 0xFF00;					
	
	//Initial state
	uOutputPattern = 1;
	
	//Fill the array with some values
   	for (n=0; n<8; n++) {
    	mydata[n] = (1 << n);			// mydata is an array, indexed by 'n'
   	} 	
   
	//Main Loop
	n = 0;                  			//I am going to reuse n as an index variable
	while (1)
	{
		asm("nop");
      	      
	} //end while
	
	return 0;
}
