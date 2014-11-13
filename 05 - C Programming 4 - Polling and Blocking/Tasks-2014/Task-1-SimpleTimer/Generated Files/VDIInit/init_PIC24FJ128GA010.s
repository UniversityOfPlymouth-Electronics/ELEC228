
; Initialization Code for PIC24FJ128GA010, Family: GP control, Package: 100-Pin TQFP 100pins

.include "p24FJ128GA010.inc"



; Filter Controls used to Generate Code:

; POR Match Filter ON

; Provisioned Feature Filter ON

; Masks are Ignored and uses UnMasked Register Writes

.GLOBAL _VisualInitialization

; Feature=fuses - fuses (DCR) configuration

; B14=JTSAGEN B13=GCP B12=GWRP B11=DEBUG B10=COE B7=FWDTEN B6=WINDIS B4=FWPSA B3:0=WDTPS3:0

; CONFIG1 is equal to POR and therefore not initialized.

; B15=IESO B10:8=FNOSC2:0 B7:6=FCKSM1:0 B5=OSCIOFCN B1:0=POSCMOD1:0

	config __CONFIG2, 0x01E3

.text

_VisualInitialization:

; Feature=Interrupts - Disable Interrupts during configuration

; clear int flags:

; B13=AD B12=U1TX B11=U1RX B10=SPI1 B9=SPF1 B8=T3

; B7=T2 B6=OC2 B5=IC2 B3=T1 B2=OC1 B1=IC1 B0=INT0

; IFS0 is equal to POR and therefore not initialized.

; B15=U2TX B14=U2RX B13=INT2 B12=T5 B11=T4 B10=OC4 B9=OC3

; B4=INT1 B3=CN B2=CM B1=MI2C1 B0=SI2C1

; IFS1 is equal to POR and therefore not initialized.

; B13=PMP B9=OC5 B7=IC5 B6=IC4 B5=IC3

; B1=SPI2 B0=SPF2

; IFS2 is equal to POR and therefore not initialized.

; B14=RTCC B6=INT4 B5=INT3 B1=MI2C2 B2=SI2C2

; IFS3 is equal to POR and therefore not initialized.

; B3=CRC B2=U2ER B1=U1ER

; IFS4 is equal to POR and therefore not initialized.

; IEC0 is equal to POR and therefore not initialized.

; IEC1 is equal to POR and therefore not initialized.

; IEC2 is equal to POR and therefore not initialized.

; IEC3 is equal to POR and therefore not initialized.

; IEC4 is equal to POR and therefore not initialized.

; Feature=Reset - Reset configuration

; B15=TRAPR B14=IOPWR

; B7=EXTR B6=SWR B5=SWDTEN B4=WDTO B3=SLEEP B2=IDLE B1=BOR B0=POR

	CLR RCON

; Feature=Oscillator - Oscillator configuration

; method to override OSCCON write protect

; B13:12=COSC1:0 B9:8=NOSC1:0

	CLR.B W0

	MOV.B #0x78, W1

	MOV.B #0x9A, W2

	MOV.W #OSCCON, W3

	MOV.B W1, [W3+1]

	MOV.B W2, [W3+1]

	MOV.B W0, [W3+1]

; B7:6=POST1:0 B5=LOCK B3=CF B1=SOSCEN B0=OSWEN

	CLR.B W0

	MOV.B #0x46, W1

	MOV.B #0x57, W2

	MOV.B W1, [W3+0]

	MOV.B W2, [W3+0]

	MOV.B W0, [W3+0]

; B15=ROI B14:12=DOZE2:0 B11=DOZEN B10:8=FRCDIV2:0

; B7:6=PLLPOST1:0 B4:0=PLLPRE4:0

; CLKDIV is equal to POR and therefore not initialized.

; Feature=A2D - A2D configuration

; Feature code removed since notprovisioned.

; Feature=IOPortA - IO Ports configuration

; Feature code removed since notprovisioned.

; Feature=IOPortB - IO Ports configuration

; Feature code removed since notprovisioned.

; Feature=IOPortC - IO Ports configuration

; Feature code removed since notprovisioned.

; Feature=IOPortD - IO Ports configuration

; Feature code removed since notprovisioned.

; Feature=IOPortE - IO Ports configuration

; Feature code removed since notprovisioned.

; Feature=IOPortF - IO Ports configuration

; Feature code removed since notprovisioned.

; Feature=IOPortG - IO Ports configuration

; Feature code removed since notprovisioned.

; Feature=CN1 - Input Change Notification configuration

; Feature code removed since notprovisioned.

; Feature=Timer1 - Timers configuration

; Feature code removed since notprovisioned.

; Feature=Timer2 - Timers configuration

; Feature code removed since notprovisioned.

; Feature=Timer3 - Timers configuration

; Feature code removed since notprovisioned.

; Feature=Timer4 - Timers configuration

; Feature code removed since notprovisioned.

; Feature=Timer5 - Timers configuration

; Feature code removed since notprovisioned.

; Feature=Timer1 - Timers configuration

; Feature code removed since notprovisioned.

; Feature=Timer3 - Timers configuration

; Feature code removed since notprovisioned.

; Feature=Timer2 - Timers configuration

; Feature code removed since notprovisioned.

; Feature=Timer4 - Timers configuration

; Feature code removed since notprovisioned.

; Feature=Timer5 - Timers configuration

; Feature code removed since notprovisioned.

; Feature=IC1 - Input Capture configuration

; Feature code removed since notprovisioned.

; Feature=IC2 - Input Capture configuration

; Feature code removed since notprovisioned.

; Feature=IC3 - Input Capture configuration

; Feature code removed since notprovisioned.

; Feature=IC4 - Input Capture configuration

; Feature code removed since notprovisioned.

; Feature=IC5 - Input Capture configuration

; Feature code removed since notprovisioned.

; Feature=OC1 - Turn off OC1 thru OC8

; Feature code removed since notprovisioned.

; Feature=OC2 - Turn off OC1 thru OC8

; Feature code removed since notprovisioned.

; Feature=OC3 - Turn off OC1 thru OC8

; Feature code removed since notprovisioned.

; Feature=OC4 - Turn off OC1 thru OC8

; Feature code removed since notprovisioned.

; Feature=OC5 - Turn off OC1 thru OC8

; Feature code removed since notprovisioned.

; Feature=OC1 - Output Compare configuration

; Feature code removed since notprovisioned.

; Feature=OC2 - Output Compare configuration

; Feature code removed since notprovisioned.

; Feature=OC3 - Output Compare configuration

; Feature code removed since notprovisioned.

; Feature=OC4 - Output Compare configuration

; Feature code removed since notprovisioned.

; Feature=OC5 - Output Compare configuration

; Feature code removed since notprovisioned.

; Feature=SPI1 - SPI configuration

; Feature code removed since notprovisioned.

; Feature=SPI2 - SPI configuration

; Feature code removed since notprovisioned.

; Feature=I2C1 - I2C configuration

; Feature code removed since notprovisioned.

; Feature=I2C2 - I2C configuration

; Feature code removed since notprovisioned.

; Feature=UART1 - UART 1 configuration

; Feature code removed since notprovisioned.

; Feature=UART2 - UART 2 configuration

; Feature code removed since notprovisioned.

; Feature=A2D - A2D configuration

; Feature code removed since notprovisioned.

; Feature=Comparator - Comparator 1, 2 and Comparator Voltage Reference configuration

; Feature code removed since does not exist on this device.

; Feature=RTC - RTCC configuration

; B15=ALRMEN B14=CHIME B13:10=AMASK3:0 B9:8=ALRMPTR1:0

; B7:0=ARPT7:0

; ALCFGRPT is equal to POR and therefore not initialized.

                    ; Turn on RTC Write before setting registers
	MOV #0x2000, W0
	MOV W0, RCFGCAL

; B15=RTCEN B13=RTCWREN B12=RTCSYNC B11=HALFSEC B10=RTCOE B9:8=RTCPTR1:0

; B7:0=CAL7:0

; RCFGCAL is equal to POR and therefore not initialized.

; Feature=PMP - PMP/PSP configuration

; B15=PMPEN B13=PSIDL B12:11=ADRMUX1:0 B10=PTBEEN B9=PTWREN B8=PTRDEN

; B7:6=CSF1:0 B5=ALP B4=CS2P B3=CS1P B2:BEP B1:WRSP B0:RDSP

; PMCON is equal to POR and therefore not initialized.

; B15=BUSY B14:13=IRQM1:0 B12:11=INCM1:0 B10=MODE16 B9:8=MODE1:0

; B7:6=WAITB1:0 B5:2=WAITM3:0 B1:0=WAITE1:0

; PMMODE is equal to POR and therefore not initialized.

; B15=CS2 B14=CS1 B13:0= Node Address

; PMADDR is equal to POR and therefore not initialized.

; B15:0=PTEN15:0

; PMAEN is equal to POR and therefore not initialized.

; B15=IBF B14=IBOV B11=IB3F B10=IB2F B9=IB1F B8=IB0F

; B7=OBE B6=OBUF B3=OB3E B2=OB2E B1=OB1E B0=OB0E

; PMSTAT is equal to POR and therefore not initialized.

; B1=RTSECSEL B0=PMPTTL`

; PADCFG1 is equal to POR and therefore not initialized.

; Feature=required - Interrupt flags cleared and interrupt configuration

; interrupt priorities IP

; B14:12=T1 B10:8=OC1 B6:4=IC1 B2:0=INTO

; IPC0 is equal to POR and therefore not initialized.

; B14:12=T2 B10:8=OC2 B6:4=IC2

; IPC1 is equal to POR and therefore not initialized.

; B14:12=U1RX B10:8=SPI1 B6:4=SPF1 B2:0=T3

; IPC2 is equal to POR and therefore not initialized.

; B6:4=AD1 B2:0=U1TX

; IPC3 is equal to POR and therefore not initialized.

; B14:12=CN B10:8=CM B6:4=MI2C1 B2:0=SI2C1

; IPC4 is equal to POR and therefore not initialized.

; B2:0=INT1

; IPC5 is equal to POR and therefore not initialized.

; B14:12=T4 B10:8=OC4 B6:4=OC3

; IPC6 is equal to POR and therefore not initialized.

; B14:12=U2TX B10:8=U2RX B6:4=INT2 B2:0=T5

; IPC7 is equal to POR and therefore not initialized.

; B6:4=SPI2 B2:0=SPF2

; IPC8 is equal to POR and therefore not initialized.

; B14:12=IC5 B10:8=IC4 B6:4=IC3

; IPC9 is equal to POR and therefore not initialized.

; B6:4=OC5

; IPC10 is equal to POR and therefore not initialized.

; B6:4=PMP

; IPC11 is equal to POR and therefore not initialized.

; B10:8=MI2C2 B6:4=SI2C2

; IPC12 is equal to POR and therefore not initialized.

; B10:8=INT4 B6:4=INT3

; IPC13 is equal to POR and therefore not initialized.

; B10:8=RTCC

; IPC14 is equal to POR and therefore not initialized.

; B14:12=CRC B10:8=U2ER B6:4=U1ER

; IPC15 is equal to POR and therefore not initialized.

; external interrupt enables

; B15=NSTDIS

; B4=MATHERR B3=ADDRERR B2=STKERR B1=OSCFAIL

; INTCON1 is equal to POR and therefore not initialized.

; B15=ALTIVT B14=DISI B4:0=INTnEP4:0

; INTCON2 is equal to POR and therefore not initialized.

; Feature=Timer1 - Start timers

; Feature code removed since notprovisioned.

; Feature=Timer3 - Start timers

; Feature code removed since notprovisioned.

; Feature=Timer2 - Start timers

; Feature code removed since notprovisioned.

; Feature=Timer5 - Start timers

; Feature code removed since notprovisioned.

; Feature=Timer4 - Start timers

; Feature code removed since notprovisioned.

; Feature=CPU - CPU register configuration

	CLR SR

	CLR SR

	CLR W0

	CLR W1

	CLR W2

	CLR W3

; Feature=Interrupts - enable interrupts

; feature interrupt enables IE

; B13=AD B12=U1TX B11=U1RX B10=SPI1 B9=SPF1 B8=T3

; B7=T2 B6=OC2 B5=IC2 B3=T1 B2=OC1 B1=IC1 B0=INT0

; IEC0 is equal to POR and therefore not initialized.

; B15=U2TX B14=U2RX B13=INT2 B12=T5 B11=T4 B10=OC4 B9=OC3

; B4=INT1 B3=CN B2=CM B1=MI2C1 B0=SI2C1

; IEC1 is equal to POR and therefore not initialized.

; B13=PMP B9=OC5 B7=IC5 B6=IC4 B5=IC3

; B1=SPI2 B0=SPF2

; IEC2 is equal to POR and therefore not initialized.

; B14=RTCC B6=INT4 B5=INT3 B1=MI2C2 B2=SI2C2

; IEC3 is equal to POR and therefore not initialized.

; B3=CRC B2=U2ER B1=U1ER

; IEC4 is equal to POR and therefore not initialized.

	return
