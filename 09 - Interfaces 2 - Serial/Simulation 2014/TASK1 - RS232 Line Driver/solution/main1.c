#include <p24fj128ga010.h>										
											
_CONFIG1( JTAGEN_OFF & GCP_OFF & GWRP_OFF & COE_OFF & FWDTEN_OFF & ICS_PGx2) 
//_CONFIG2( FCKSM_CSDCMD & OSCIOFNC_OFF & POSCMOD_XT & FNOSC_PRI)               //These are the Explorer 16 defaults
_CONFIG2( FNOSC_FRCPLL & OSCIOFNC_OFF );

//
// BIT BANGING DEMONSTRATION USING THE MICROCHIP EXPLORER16 BOARD
// AUTHOR: NICHOLAS OUTRAM - UNIVERSITY OF PLYMOUTH - 2008
// MODULE: ELEC212 and ELEC224
//
// This demo implements the RS232 protocol using bit banging - it does NOT use the UART
// The RS232 connector is connected to RF5 (Tx) and RF4 (Rx) via a MAX3232 line driver
// Hardware Timer TIMER1 is used to ensure the correct timing between bits
// I have used blocking for illustrative purposes (no multitasking needed)
// 
// RS232 Protcol using configuration 2400-8-N-1 , No handshaking
// Brief summary
// 
// (i)   Idle state - Tx = 1
// (ii)  Send start bit: Tx = 0
// (iii) Send 8 bits (lsb first) in sequence
// (iv)  Send stop bit:  Tx = 1
//
// The line driver (MAX3232) generates the correct polarity to drive RS232 and communicate with a PC
//
// NOTES - there is no serial input functionality implemented here, but it could be done
//         For RS232, you would normally use the on-chip UART to do this (later in the term)
//         I am using the internal oscillator - this impacts on timing accuracy

// TIMING:
// 
// The time period between each bit for 2400 baud (very slow) is 416us
// Fcy = 16MIPS
// Fck = 32MHz
// PRESCALE = 1 (for max accuracy)

//Function Prototypes
void sendRS232(const unsigned char c);
 	
//Global variables							
		
//Main code								
int main()
{
	//Configure the device to use the internal oscillator
	OSCCONbits.COSC  = 1u;	// Internal oscillator with PLL
	CLKDIVbits.RCDIV = 0u;	// Internal oscillator not divided (8MHz)
	CLKDIVbits.DOZEN =0;	// No post scaling
	CLKDIVbits.DOZE  =0;	//
    
	//PORTS
	TRISF = 0b1111111111011111;	//RF5 is an output
	_RF5  = 1;					//The idle state - send 1 to the reciever
    //LATF  = 0xFFFF;	//All output bits to 1   
             
	//TIMERS
	T1CON = 0x0000;
	TMR1  = 0x0000;
	T1CONbits.TCKPS = 0;	//PRESCALE = 1
 	T1CONbits.TON   = 1;	//TIMER1 ON
	
	T2CON = 0x0000;
	T2CONbits.TCKPS = 3;	//PRESCALE = 256
	T2CONbits.TON = 1;		//TIMER2 ON
		
	//Wait for the reciever to sort itself out
	TMR2 = 0; 
	while (TMR2 < 10000) {
		asm("nop");
	}
	
	// ***********
	// MAIN LOOP *
	// ***********
	while (1)
	{
		sendRS232('H');
		sendRS232('e');
		sendRS232('l');
		sendRS232('l');
		sendRS232('o');
		sendRS232(' ');
		sendRS232('W');
		sendRS232('o');
		sendRS232('r');
		sendRS232('l');
		sendRS232('d');
		sendRS232('.');
		sendRS232('\n');
		sendRS232('\r');

	} //end while
	
	return 0;
} //end of main()


// RS232 BITBANGING SPECIFIC CONSTANT DEFINITIONS
#define DELAY416us 6656
#define STARTBIT 0
#define STOPBIT 1
#define BMASK 0b00000001

//The following definition is created to make the remaining code tidy
#define DELAY1BIT TMR1=0; while (TMR1 < DELAY416us) { asm("nop"); }

void sendRS232(const unsigned char c)
{
	//Local variab;es
	unsigned char b;	//A copy of the data byte that can be copied
	int n;				//loop index
	b = c;
	
	//Send start bit
	_RF5 = STARTBIT;	

	//Delay for 1-bit (set depending on BAUD rate)	- blocking
	DELAY1BIT
	
	//Send 8 data bits
	for (n=0; n<8; n++) {
		
		//Send next bit
		if (b & BMASK) _RF5 = 1;		//Send 1
		else           _RF5 = 0;		//Send 0
		
		b = b >> 1;	 //Shift right, ready to read next bit
		
		DELAY1BIT	//Delay for 1-bit (depends on BAUD rate) - blocking
		
	} //end for
	
	_RF5 = STOPBIT;	//Send stop bit
	DELAY1BIT 		//Delay at the end - blocking
	
} //end of function sendRS232   
