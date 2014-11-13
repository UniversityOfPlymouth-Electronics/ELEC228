#include <p24FJ128GA010.h>


_CONFIG2( FNOSC_FRCPLL & OSCIOFNC_OFF );	// Internal oscillator - 4xPLL giving 16 MIPS
											// pin RC15 has the oscillator
//Declare global functions using in main.c

   
	
int main()
{
	//Configure the device to use the internal oscillator
	OSCCONbits.COSC  = 1u;	// Internal oscillator with PLL
	CLKDIVbits.RCDIV = 0u;	//Internal oscillator not divided (8MHz)
	CLKDIVbits.DOZEN =0;	//No post scaling
	CLKDIVbits.DOZE  =0;	//
	
	//Local variables here
	unsigned int n;                     //loop variable
    union {
        unsigned int word16;            //full 16 bits
        unsigned int led_code :4;       //least significant 4 bits
    } outputPattern; 	
    
    
    
	//set up ports
	TRISA = 0xFF00;			//Least-significant 4 bits are digital outputs
	   
	//Main Loop
	while (1) {
            //Set overall 16-bit word to 0
            outputPattern.word16 = 0;
		
            for (n=0; n<10; n++) {
                //Set bottom 4-bits to the number you want to display
		outputPattern.led_code = n;

                //Write full 16-bit word to the hardware port
                PORTA = outputPattern.word16;
            }
	} //end while
	
	return 0;
}


