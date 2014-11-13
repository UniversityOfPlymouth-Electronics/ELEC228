#include <p24FJ128GA010.h>

//_CONFIG2( FNOSC_FRCPLL & OSCIOFNC_OFF );	// Internal oscillator - 4xPLL giving 16 MIPS
#pragma config FNOSC = FRCPLL, OSCIOFNC = OFF											// pin RC15 has the oscillator
											
//Function prototypes
void update_display(unsigned int t, unsigned int u);
unsigned int poll_switch();
void led_on();
void led_off();
					
//Local variables						
typedef union {
    unsigned int word16;
    struct  {
        unsigned int data     :4;    //Bits0..3 are used for the display data (output)
        unsigned int EN_TENS  :1;    //BIT4 is the ENable for the TENS display
        unsigned int EN_UNITS :1;    //BIT5 is the ENable for the UNITS display
        unsigned int SW       :1;    //BIT6 is the input SWITCH 
        unsigned int D1       :1;    //BIT7 is the LED D1       
        unsigned int          :8;    //Bits7..15 are not used
    } attribute;      
} display_port;

typedef union {
    unsigned int word16;
    struct {
        unsigned int          :6;   //Bottom 6 bits (data and enable pins)
        unsigned int SW       :1;   //Switch
        unsigned int          :9;   //All other pins
    } BIT;
} input_port;

display_port *display = (display_port*)&LATA;   // Address of Output latch (that connects to PORTA) - it is SAFER to write to the LATCH
input_port   *inputs  = (input_port*) &PORTA;	// PORTA Address (you cannot read from LATA)
			
//Main code								
int main()
{
    //Configure the device to use the internal oscillator
    OSCCONbits.COSC  = 1u;	// Internal oscillator with PLL
    CLKDIVbits.RCDIV = 0u;	// Internal oscillator not divided (8MHz)
    CLKDIVbits.DOZEN =0;	// No post scaling
    CLKDIVbits.DOZE  =0;	//

    //set up ports
    TRISA = 0xFF40;			//Least-significant 5 bits are digital outputs
    LATA  = 0x0000;			//Write zero to PORTA via the latch
    
    //Configure timer
    T1CON = 0x8030;         //Internal osc, pre-scale by 256
    
    //Local variables here
    unsigned int sw_state;  //Switch state (0=up; 1=down)
    unsigned int count;     //Value to be displayed
    unsigned int units;     //For display 0
    unsigned int tens;      //For display 1
    unsigned int state=0;   //FSM state variable

    //Initialisation
    count = 0;              //Reset counter value
    units = 0;
    tens  = 0;
    update_display(tens, units);
    led_on();
	     
	   
    //Main Loop
    while (1)
    {
    //Read inputs
        sw_state = poll_switch();

        //Update state
        switch (state)
        {
        case 0:
            //code here
            break;

        case 1:
            //code here
            break;

        default:
            //if state is corrupted
            state=0;
            break;

    } //end of switch

        //Update display
        // TO DO
    // Call led_on() or led_off() depending on state


    } //end while

    return 0;
}



//Switch on LED
void led_on()
{
    display->attribute.D1 = 1;
}

void led_off()
{
    display->attribute.D1 = 0;
}        

//Write a constant value to the display
void update_display(const unsigned int t, const unsigned int u)
{
   display->attribute.EN_TENS  = 1; //Select the tens display
   display->attribute.EN_UNITS = 0; //Disable units display
   
   display->attribute.data = t;     //Write data to latch
   
   display->attribute.EN_TENS  = 0; //Disable tens display
   display->attribute.EN_UNITS = 1; //Enable units display
   
   display->attribute.data = u;     //Write data to latch
   display->attribute.EN_UNITS = 0; //Disable units display   
}    


//Read digital switch input and return a 1 is the switch is pressed, and a 0 otherwise
unsigned int poll_switch()
{
    return (inputs->BIT.SW);  //Read input
} 

 
     