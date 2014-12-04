// AUTHOR: NICHOLAS OUTRAM - UNIVERSITY OF PLYMOUTH - 2008
// MODULE: ELEC212 and ELEC224


#include <p24fj128ga010.h>	

void configure_timers() {
    T1CON = 0x0000;
    TMR1 = 0x0000;
    T1CONbits.TCKPS = 0; //PRESCALE = 1
    T1CONbits.TON = 1; //TIMER1 ON

    T2CON = 0x0000;
    T2CONbits.TCKPS = 3; //PRESCALE = 256
    T2CONbits.TON = 1; //TIMER2 ON
}
