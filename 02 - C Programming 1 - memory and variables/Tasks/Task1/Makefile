# MPLAB IDE generated this makefile for use with GNU make.
# Project: example1.1.mcp
# Date: Tue Sep 30 23:31:00 2008

AS = pic30-as.exe
CC = pic30-gcc.exe
LD = pic30-ld.exe
AR = pic30-ar.exe
HX = pic30-bin2hex.exe
RM = rm

example1.1.hex : example1.1.cof
	$(HX) "example1.1.cof"

example1.1.cof : main.o
	$(CC) -mcpu=24FJ128GA010 "main.o" -o"example1.1.cof" -Wl,-L"C:\Program Files\Microchip\MPLAB C30\lib",-Tp24FJ128GA010.gld,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--heap=200,-Map="example1.1.map",--report-mem

main.o : ../../../../../../../../program\ files/microchip/mplab\ c30/bin/../support/h/p24FJ128GA010.h main.c
	$(CC) -mcpu=24FJ128GA010 -x c -c "main.c" -o"main.o" -D__DEBUG -g -Wall

clean : 
	$(RM) "main.o" "example1.1.cof" "example1.1.hex"

