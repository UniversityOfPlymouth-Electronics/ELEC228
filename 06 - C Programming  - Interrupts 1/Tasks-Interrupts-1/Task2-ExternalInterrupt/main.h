#ifndef _MAIN_H_
#define _MAIN_H_


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
    } bit;    
} input_port;

#endif
