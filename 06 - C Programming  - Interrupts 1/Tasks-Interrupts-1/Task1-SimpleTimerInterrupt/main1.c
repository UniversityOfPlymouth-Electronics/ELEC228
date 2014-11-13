#include <p24fj128ga010.h>

_CONFIG2(FNOSC_FRCPLL & OSCIOFNC_OFF); // Internal oscillator - 4xPLL giving 16 MIPS
// pin RC15 has the oscillator

//Function prototypes
void update_display(unsigned int t, unsigned int u);
unsigned int poll_switch();
void led_on();
void led_off();

//Global variables
volatile unsigned int count; //Value to be displayed - volatile means an interrupt might change this at any time
unsigned int units; //For display 0
unsigned int tens; //For display 1

typedef union {
    unsigned int word16;

    struct {
        unsigned int data : 4; //Bits0..3 are used for the display data (output)
        unsigned int EN_TENS : 1; //BIT4 is the ENable for the TENS display
        unsigned int EN_UNITS : 1; //BIT5 is the ENable for the UNITS display
        unsigned int SW : 1; //BIT6 is the input SWITCH
        unsigned int D1 : 1; //BIT7 is the LED D1
        unsigned int : 8; //Bits7..15 are not used
    } attribute;
} display_port;

typedef union {
    unsigned int word16;

    struct {
        unsigned int : 6; //Bottom 6 bits (data and enable pins)
        unsigned int SW : 1; //Switch
        unsigned int : 9; //All other pins
    } BIT;
} input_port;

volatile display_port *display = (display_port*) & LATA; // Address of Output latch (that connects to PORTA) - it is SAFER to write to the LATCH
volatile input_port *inputs = (input_port*) & PORTA; // PORTA Address (you cannot read from LATA)

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
    T1CONbits.TCKPS = 0b00; //Prescale = 1
    T1CONbits.TON = 1; //Timer on
    TMR1 = 0; //Timer = 0

    //Configure TIMER1 interrupt 	     
    _T1IP = 4; //Interrupt priority = 4
    PR1 = 0x32 - 1; //Period Register       -- TASK 2 -- CHANGE THIS AND PRESCALE TO GET 1s

    _T1IF = 0; //Clear timer interrupt flag
    _T1IE = 1; //Switch on timer 1 interrupt enable

    TMR1 = 0;

    //Main Loop
    while (1) {
        //TASK 1 - Single step the following code - watch TMR1 - when does the interrupt occur?
        Idle(); //Switch off main core - peripherals continue
        asm("nop"); //Woken by interrupt

        // TASK 3 - write code to update the display
        // TASK 4 - how does adding this code affect the timing?

    } //end while

    return 0;
}

//void _ISR _T1Interrupt(void)  //Old method

void __attribute__((interrupt, no_auto_psv)) _T1Interrupt() {
    //TASK 5 - WHAT IS THE LATENCY (In Instruction Cycles)?
    display->attribute.D1 = !display->attribute.D1; //Toggle LED
    count++; //Increment the count
    _T1IF = 0; //Create interrrupt flag before returning
}

//Switch on LED

void led_on() {
    display->attribute.D1 = 1;
}

void led_off() {
    display->attribute.D1 = 0;
}

//Write a constant value to the display

void update_display(const unsigned int t, const unsigned int u) {
    display->attribute.EN_TENS = 1; //Select the tens display
    display->attribute.EN_UNITS = 0; //Disable units display

    display->attribute.data = t; //Write data to latch

    display->attribute.EN_TENS = 0; //Disable tens display
    display->attribute.EN_UNITS = 1; //Enable units display

    display->attribute.data = u; //Write data to latch
    display->attribute.EN_UNITS = 0; //Disable units display
}


//Read digital switch input and return a 1 is the switch is pressed, and a 0 otherwise

unsigned int poll_switch() {
    return (inputs->BIT.SW); //Read input
}


