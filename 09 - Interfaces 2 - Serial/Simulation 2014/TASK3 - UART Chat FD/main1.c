#include "uart_constants.h"

_CONFIG1(JTAGEN_OFF & GCP_OFF & GWRP_OFF & COE_OFF & FWDTEN_OFF & ICS_PGx2)
//_CONFIG2( FCKSM_CSDCMD & OSCIOFNC_OFF & POSCMOD_XT & FNOSC_PRI)               //These are the Explorer 16 defaults
_CONFIG2(FNOSC_FRCPLL & OSCIOFNC_OFF);

// *************************************************************************************
// ******************************* FULL DUPLEX CHAT ************************************
// *************************************************************************************
//
// UART DEMONSTRATION USING PROTEUS / THE MICROCHIP EXPLORER16 BOARD
// AUTHOR: NICHOLAS OUTRAM - UNIVERSITY OF PLYMOUTH - 2008
// MODULE: ELEC212 and ELEC224
//
// This demo implements the RS232 protocol using a UART - it does NOT use bit banging
// The RS232 connector is connected to RF5 (Tx) and RF4 (Rx) via a MAX3232 line driver
// No hardware is needed to get the correct timing between bits
// I have used polling for illustrative purposes 
// 
// RS232 Protcol using configuration 2400-8-N-1 , RTS/CTS handshaking
// Brief summary
// 
//
// TIMING: The PIC UART needs to be setup to get the correct BAUD rate
// 
// The time period between each bit for 2400 baud (very slow) is 416us
// Fcy = 16MIPS
// Fck = 32MHz
//
// The BAUD generator is essentially a timer and a clock divider
// First, set the clock divider BREGH
//
// The clock divider is either 1:16 (BREGH=0) or the higher speed 1:4 (BREGH=1) 
// 
// Now to control the timer period UxBRG (16 bit) which controls each UART BAUD rate
//
//  UxBRG = (Fcy / (4  * baudrate)) - 1         for BREGH=1
//  UxBRG = (Fcy / (16 * baudrate)) - 1         for BREGH=0
//
// Similarly
//
//  baudrate = Fcy / (4 *  (UxBRG+1))           for BREGH=1
//  baudrate = Fcy / (16 * (UxBRG+1))           for BREGH=1
// 
// where x is the UART number (1 or 2). We will use the 1:4 ratio
//
// So, for a 2400 BAUD and , UxBREG = (16E6 / (4 * 2400)) - 1 = 1666.6667
// We have to choose either 1666 or 1667
//
// The %Error is 100*(Actual Baud - Desired Baud)/Desired Baud
// 


//Function Prototypes
extern void ConfigureUARTs();
extern void putU1_blocking(char c);
extern void putU2_blocking(char c);
extern char getU1_blocking();
extern char getU2_blocking();
extern unsigned int putU1_polling(const char c);
extern unsigned int getU1_polling(char *rxData);
extern unsigned int putU2_polling(const char c);
extern unsigned int getU2_polling(char *rxData);
extern void putsU1_blocking(const char *str);
extern void putsU2_blocking(const char *str);

extern void configure_timers();

//Global variables							
unsigned int data_is_sent, data_is_recieved;
char data_tx, data_rx;

//Main code

int main() {
    //Configure the device to use the internal oscillator
    OSCCONbits.COSC = 1u; // Internal oscillator with PLL
    CLKDIVbits.RCDIV = 0u; // Internal oscillator not divided (8MHz)
    CLKDIVbits.DOZEN = 0; // No post scaling
    CLKDIVbits.DOZE = 0; //

    //TIMERS
    configure_timers();

    //Configure both UARTS to 2400-8-1-N-RTS/CTS
    ConfigureUARTs();

    // ***********
    // MAIN LOOP *
    // ***********

    //Write a prompt on U1
    putsU1_blocking("Ready >\r\n");
    putsU2_blocking("Ready >\r\n");

    char U1rx, U1tx;
    char U2rx, U2tx;
    unsigned int U1HasSentData = 0;
    unsigned int U2HasSentData = 0;
    unsigned int U1HasReceivedData = 0;
    unsigned int U2HasReceivedData = 0;

    while (1) {

        //
        // POLL FOR INCOMING DATA
        //
        //Poll U1 for new data. If it has data (U1HasSentData==1), U1rx will be overwritten
        if (getU1_polling(&U1rx) == 1) {
            U1HasReceivedData = 1;
            U2tx = U1rx;
        }
        //Poll U2 for new data
        if (getU2_polling(&U2rx) == 1) {
            U2HasReceivedData = 1;
            U1tx = U2rx;
        }


        //
        // CONDITIONALLY WRITE DATA BACK OUT TO THE UARTS USING POLLING
        //

        //If there is data received from U1, send it to U2
        if (U1HasReceivedData) {
            //Try and send the data to U2
            U2HasSentData = putU2_polling(U2tx);

            //Has the data been sent yet?
            if (U2HasSentData) {
                //If yes, the transaction is complete
                U1HasReceivedData = 0;
            } //end if
        } //end if


        //If there is data received from U2, send it to U1
        if (U2HasReceivedData) {
            //Try and send the data to U2
            U1HasSentData = putU1_polling(U1tx);

            //Has the data been sent yet?
            if (U1HasSentData) {
                //If yes, the transaction is complete
                U2HasReceivedData = 0;
            } //end if
        } //end if


        // DO WHAT EVER YOU LINK IN THE REST OF THE TIME!!!

    } //end while

    return 0;
} //end of main()




