#include "main.h"

extern display_port *display;   // Address of Output latch (that connects to PORTA) - it is SAFER to write to the LATCH
extern input_port   *inputs;

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
    return (inputs->bit.SW);  //Read input 
} 
