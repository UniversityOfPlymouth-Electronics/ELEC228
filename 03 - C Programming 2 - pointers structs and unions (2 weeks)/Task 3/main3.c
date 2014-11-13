#include <p24FJ128GA010.h>


_CONFIG2( FNOSC_FRCPLL & OSCIOFNC_OFF );	// Internal oscillator - 4xPLL giving 16 MIPS
											// pin RC15 has the oscillator
//Declare global functions using in main.c
extern void do_delay_badly(const unsigned int D);
   
	
int main()
{
	//Configure the device to use the internal oscillator
	OSCCONbits.COSC  = 1u;	// Internal oscillator with PLL
	CLKDIVbits.RCDIV = 0u;	//Internal oscillator not divided (8MHz)
	CLKDIVbits.DOZEN =0;	//No post scaling
	CLKDIVbits.DOZE  =0;	//
	
	//Local variables here
	unsigned int n;                     //loop variable
	unsigned int units;
	unsigned int tens;
	
	//Create a new type "display_control"
    typedef union {
        unsigned int word16;            //full 16 bits
        struct {
	        unsigned int bit0 :1;
	        unsigned int bit1 :1;
	        unsigned int bit2 :1;
	        unsigned int bit3 :1;
	        unsigned int DISP1_EN   :1;
	        unsigned int DISP2_EN   :1;
	       } bits; 
        unsigned int led_code :4;       //least significant 4 bits
    } display_control;
    
    //Create a pointer to a variable of type display_control
    display_control *outputPattern; 	
    
    //give the pointer variable outputPattern the same address as PORTA
    outputPattern = (display_control*)&PORTA;
    
	//set up ports
	TRISA = 0xFF00;			//Least-significant 4 bits are digital outputs
	   
	//Initially disable both displays
	outputPattern->bits.DISP1_EN = 1;	//disable display 1	
	outputPattern->bits.DISP2_EN = 1;	//disable display 2

	//Main Loop
	while (1)
	{
    	//Set overall 16-bit word to 0
		outputPattern->word16 = 0;

		
		for (n=0; n<100; n++) {
		    //convert n to BCD
		    tens  = n / 10;			// integer divide (20 clock cycles)
		    units = n % 10;			// integer modulus (22 clock cycles)
		    		    
		    // ***************************
		    // WRITE DATA TO FIRST DISPLAY
		    // ***************************
		    
                    //Write the data for display 1
                    outputPattern->led_code = tens;		//MSW

		    //Enable display 1 (tens)
		    outputPattern->bits.DISP1_EN = 0;	//select display 1
		   
		    //Disable display 1 (stop it from reading any new data)
		    outputPattern->bits.DISP1_EN = 1;				
    		
		    // ****************************
		    // WRITE DATA TO SECOND DISPLAY
		    // ****************************
		    
                    //Write the data for display 2 (units)
                    outputPattern->led_code = units;		//LSW
				
		    //enable the second display (units)
		    outputPattern->bits.DISP2_EN = 0;	//enable display 2

                    //Disable the second display
		    outputPattern->bits.DISP2_EN = 1;	//Disable display 2

                    //delay
                    do_delay_badly(500);
    		
            }  //end for
	
		
	} //end while
	
	return 0;
}


