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
