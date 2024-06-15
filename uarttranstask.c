
// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#define _XTAL_FREQ 6000000

void init();
unsigned char swicthval;
unsigned char recval;




void main()
{
    init();
    while (1)
    {
        swicthval = PORTB & 0xF0;  
switch (swicthval) //enable switches
{
    case 0xE0: //case 1 0xE0
        TXREG = 'A';  // need to transmit A to slave        
        PORTD = 0x02; // LED blinking code for 'A'
        break;

    case 0xD0://case 1 0xD0
        TXREG = 'B';// need to transmit A to slave 
        PORTD = 0x10; // LED blinking code for 'B'
        break;

    case 0xB0://case 1 0xB0
        TXREG = 'C';// need to transmit A to slave 
        PORTD = 0x12; // LED blinking code for 'C'
        break;

    case 0x70://case 1 0x70
        TXREG = 'D';// need to transmit A to slave 
        PORTD = 0x00; // LED blinking code for 'D'
        break;
}


        __delay_ms(100);

        if (PIR1 & 0x20)//to enable RCIF to check data is transmiting or not
        {
            recval = RCREG; //transmited data from slave
            switch (recval)//enable switches
            {
            case 'a':
                PORTD = 0x02; //0000 0010 LED blinking for 'a'
                break;

            case 'b':
                PORTD = 0x10; //0001 0000 LED blinking for 'b' 
                break;

            case 'c':
                PORTD = 0x12; //0001 0010 LED blinking for 'c'
                break;

            case 'd':
                PORTD = 0x00; //0000 0000 LED blinking for 'd'
                break;
            }
        }
    }
}

void init()
{
    TRISB=0xF0; // enable switches d4 to d7 
    TRISD=0x00; // setting led input and output
    OPTION_REG=0x7F; //enabling internal pul up resistor 
    TRISC=0xC0;//RC6 Trans and RC7 reciver enable for serial port 1100 0000
    TXSTA=0x20;//0010 0000 Transmit enable
    RCSTA=0x90;//10010000  recevier enable
   SPBRG=0x09;//setting baud rate for 9600 is fosc/64*9600-1 = 6000000/614000=9.7
    
}

