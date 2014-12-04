// AUTHOR: NICHOLAS OUTRAM - UNIVERSITY OF PLYMOUTH - 2008
// MODULE: ELEC212 and ELEC224

#include "uart_constants.h"

void ConfigureUARTs() {
    //UART1
    TRISDbits.TRISD15 = 0; //Ready To Send - (RTS) is an output
    TRISDbits.TRISD14 = 1; //Clear To Send (CTS) is an input
    U1MODEbits.BRGH = 1; //BRGH = 1, so use a 1:4 divider
    U1BRG = BAUD; //Set baud rate to 2400 for (assuming BRGH = 1)
    U1MODEbits.UARTEN = 1; //Enable the UART
    U1STA = 0x0400; //Enable Transmit and reset all other bits
    RTS1 = NOT_RTS; //Not ready, default mode (active low)

    //UART2
    TRISFbits.TRISF12 = 0;
    TRISFbits.TRISF13 = 1;
    U2MODEbits.BRGH = 1; //BRGH = 1, so use a 1:4 divider
    U2BRG = BAUD; //Set baud rate to 2400 for (assuming BRGH = 1)
    U2MODEbits.UARTEN = 1; //Enable the UART
    U2STA = 0x0400; //Enable the UART and reset all other bits
    RTS2 = NOT_RTS; //RTS = 1, default (active low)
}

void putU1_blocking(char c) {
    while (CTS1 == NOT_RTS); //Wait on a clear to send from the other end - this is blocking
    while (U1STAbits.UTXBF); //Wait if transmitt buffer is full
    U1TXREG = c; //Write data to bufer (and transmit)
}

void putU2_blocking(char c) {
    while (CTS2 == NOT_RTS); //Wait on a clear to send from the other end - this is blocking
    while (U2STAbits.UTXBF); //Wait if transmitt buffer is full
    U2TXREG = c; //Write data to bufer (and transmit)
}

char getU1_blocking() {
    char res;
    RTS1 = RTS; //Tell the other end you are read to recieve data
    while (!U1STAbits.URXDA); //Wait for data to arrive
    res = U1RXREG; //Read a byte from the recieve buffer
    RTS1 = NOT_RTS;
    return res;
}

char getU2_blocking() {
    char res;
    RTS2 = RTS; //Tell the other end you are read to recieve data
    while (!U2STAbits.URXDA); //Wait for data to arrive
    res = U2RXREG; //Read a byte from the recieve buffer
    RTS2 = NOT_RTS;
    return res;
}

//This is the non-blocking version - call it multiple times until it returns a 1

unsigned int putU1_polling(const char c) {
    static int state = 0; //Local and static state - first time this is called, it is a 0
    unsigned int sent = 0;

    switch (state) {

        case 0: //waiting for CTS
            if (CTS1 == RTS) state = 1; //CTS recieved
            break;
        case 1: //Wait for transmitt buffer to become empty
            if (U1STAbits.UTXBF == 0) state = 2; //Ok, buffer is not full - proceed
            break;
        case 2: //CTS received, buffer is not full - we can now send some data
            U1TXREG = c; //Write data
            sent = 1; //Flag that data has been sent
            state = 0; //Return to state 0
            break;
        default: //should not occur, but just in case!
            state = 0;
            break;
    } //end switch

    return sent;
}

unsigned int getU1_polling(char *rxData) {
    static unsigned int state = 0;
    unsigned int dataIsReceived = 0;

    switch (state) {
        case 0:
            RTS1 = RTS; //Tell the other end you are ready to recieve data
            state = 1;
            break;
        case 1:
            if (U1STAbits.URXDA == 1) //If Receiver data has arrived...
            {
                *rxData = U1RXREG; //read the buffer
                dataIsReceived = 1; //Flag that data is now recieved
                RTS1 = NOT_RTS; //Pull RTS back
                state = 0; //Go back to state 0
            }
            break;
        default:
            state = 0;
            break;
    } //end switch

    return dataIsReceived;
}



//This is the non-blocking version - call it multiple times until it returns a 1

unsigned int putU2_polling(const char c) {
    static int state = 0; //Local and static state - first time this is called, it is a 0
    unsigned int sent = 0;

    switch (state) {

        case 0: //waiting for CTS
            if (CTS2 == RTS) state = 1; //CTS recieved
            break;
        case 1: //Wait for transmitt buffer to become empty
            if (U2STAbits.UTXBF == 0) state = 2; //Ok, buffer is not full - proceed
            break;
        case 2: //CTS received, buffer is not full - we can now send some data
            U2TXREG = c; //Write data
            sent = 1; //Flag that data has been sent
            state = 0; //Return to state 0
            break;
        default: //should not occur, but just in case!
            state = 0;
            break;
    } //end switch

    return sent;
}

unsigned int getU2_polling(char *rxData) {
    static unsigned int state = 0;
    unsigned int dataIsReceived = 0;

    switch (state) {
        case 0:
            RTS2 = RTS; //Tell the other end you are ready to recieve data
            state = 1;
            break;
        case 1:
            if (U2STAbits.URXDA == 1) //If Receiver data has arrived...
            {
                *rxData = U2RXREG; //read the buffer
                dataIsReceived = 1; //Flag that data is now recieved
                RTS2 = NOT_RTS; //Pull RTS back up (active low)
                state = 0; //Go back to state 0
            }
            break;
        default:
            state = 0;
            break;
    } //end switch

    return dataIsReceived;
}


// String functions

void putsU1_blocking(const char *str) {
    unsigned int idx;

    for (idx = 0; str[idx] != '\0'; idx++)
        putU1_blocking(str[idx]);
}

void putsU2_blocking(const char *str) {
    unsigned int idx;

    for (idx = 0; str[idx] != '\0'; idx++)
        putU2_blocking(str[idx]);
}
