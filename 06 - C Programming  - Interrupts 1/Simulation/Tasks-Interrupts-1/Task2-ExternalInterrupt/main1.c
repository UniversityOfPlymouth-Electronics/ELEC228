#include <p24fj128ga010.h>
#include "main.h"

_CONFIG2(FNOSC_FRCPLL & OSCIOFNC_OFF); // Internal oscillator - 4xPLL giving 16 MIPS
// pin RC15 has the oscillator										
//Function prototypes
void update_display(unsigned int t, unsigned int u);
unsigned int poll_switch();
void led_on();
void led_off();

//Global variables
unsigned int count; //Value to be displayed
unsigned int units; //For display 0
unsigned int tens; //For display 1
unsigned int displayOn = 0; //Switch for Display ON or OFF - shared by two ISR routines
unsigned int IC1BUFFERVAL; //Used to read IC1 timer buffer

display_port *display = (display_port*) & LATA; // Address of Output latch (that connects to PORTA) - it is SAFER to write to the LATCH
input_port *inputs = (input_port*) & PORTA; // PORTA Address (you cannot read from LATA)

//Main code

int main() {
    //Configure the device to use the internal oscillator
    OSCCONbits.COSC = 1u; // Internal oscillator with PLL
    CLKDIVbits.RCDIV = 0u; // Internal oscillator not divided (8MHz)
    CLKDIVbits.DOZEN = 0; // No post scaling
    CLKDIVbits.DOZE = 0; //

    //set up ports
    TRISA = 0xFF40; //Least-significant 5 bits are digital outputs
    LATA = 0x0000; //Write zero to PORTA via the latch

    //Initialisation
    count = 0; //Reset counter value
    units = 0;
    tens = 0;
    update_display(tens, units);
    led_off();

    //TIMER1 Configuration Register
    T1CON = 0;
    T1CONbits.TCKPS = 0b11; //Prescale = 256
    T1CONbits.TON = 1; //Timer on
    TMR1 = 0; //Reset Timer Counter

    //Configure TIMER1 interrupt 	     
    _T1IP = 4; //Interrupt priority = 4 - REVIEW THIS!
    PR1 = 62500 - 1; //Period Register - set for 1s
    _T1IF = 0; //Clear timer interrupt flag

    //Configure the input capture (IC1)
    _IC1IP = 4; //Set interrupt priority for the Input Capture - REVIEW THIS!
    _TRISD8 = 1; //Set RD8 to be an input
    IC1CON = 0x0002; //InputCaptureCONfiguration register - falling edge - REVIEW THIS!
    _IC1IF = 0; //Reset the Input Capture 1 Interrupt Flag

    //ENABLE INTERRUPTS
    _IC1IE = 1; //Set the Input Capture 1 Interrupt Enable
    _T1IE = 1; //Switch on timer 1 interrupt enable

    //Main Loop
    while (1) {
        //TASK 1 - Check and correct the interrupt priorities
        //TASK 2 - Single step the following code - press SW2 - what happens?
        //TASK 3 - add another Input Capture to start and stop the counter
        Idle(); //Switch off main core - peripherals continue
        asm("nop"); //Woken by interrupt (TIMER 1 or INPUT CAPTURE 1)

    } //end while

    return 0;
}


//************************************************************************
//********************* INTERRUPT SERVICE ROUTINES ***********************
//************************************************************************

//ISR FOR THE TIMER

void __attribute__((interrupt, no_auto_psv)) _T1Interrupt() {
    //Increment the second counter on every interrupt
    count++;

    //Check for an overflow
    if (count == 100) {
        count = 0;
    }

    //Calculate tens and units for the display (BCD)    
    tens = count / 10;
    units = count % 10;

    //Check the displayOn flag
    if (!displayOn) {
        //Switch display off
        display->attribute.D1 = 0;
    } else {
        //Toggle LED state
        display->attribute.D1 = !display->attribute.D1;
        update_display(tens, units);
    }

    //Read the IC1 buffer (we are not using this yet)     
    IC1BUFFERVAL = IC1BUF; //This is needed to prevent buffer overflow

    //Reset interrrupt flag before returning
    _T1IF = 0;
}

//ISR FOR THE INPUT CAPTURE

void __attribute__((interrupt, no_auto_psv)) _IC1Interrupt() {
    displayOn = (1 - displayOn); //Toggle the flag displayOn
    _IC1IF = 0; //Reset the interrupt flag
}
