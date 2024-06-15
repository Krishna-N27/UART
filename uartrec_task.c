
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

unsigned char rec_val;
void lcdcmd(unsigned char);
void lcddata(unsigned char);
void output(unsigned int);
unsigned char x,y,s,t;

void rec_init();
unsigned char rec_val;

unsigned char swicthval;

void main()
{
    rec_init();

    while (1)
    {
        if (PIR1 & 0x20)  //to enable RCIF for who data is transmiting or not
        {
            rec_val = RCREG; //transmited data
            switch (rec_val) //enable switches
            {
            case 'A':  //if RCREG value is A
                lcdcmd(0x80);  //display value in first line
                for ( x = 0; x < 11; x++)  //loop upto 0 to 11
                {
                    lcddata("REC VAL:'A'"[x]); //Display the String
                }
                TXREG = 'a';  //Transmiting 'a' from slave to master
                lcdcmd(0xC0);//display value in secound line
                for ( x = 0; x < 13; x++)//loop upto 0 to 13
                {
                    lcddata("TRANS VAL:'a'"[x]);//Display the String
                }
                break;

            case 'B'://if RCREG value is B
                lcdcmd(0x80);//display value in first line
                for ( x = 0; x < 11; x++)//loop upto 0 to 11
                {
                    lcddata("REC VAL:'B'"[x]);//Display the String
                }
                TXREG = 'b'; //Transmiting 'b' from slave to master
                 lcdcmd(0xC0);//display value in secound line
                for ( x = 0; x < 13; x++)//loop upto 0 to 13
                {
                    lcddata("TRANS VAL:'b'"[x]);//Display the String
                }
                break;

            case 'C'://if RCREG value is C
                lcdcmd(0x80);//display value in first line
                for ( x = 0; x < 11; x++)//loop upto 0 to 11
                {
                    lcddata("REC VAL:'C'"[x]);//Display the String
                }
                TXREG = 'c'; //Transmiting 'c' from slave to master
                 lcdcmd(0xC0);//display value in secound line
                for ( x = 0; x < 13; x++)//loop upto 0 to 13
                {
                    lcddata("TRANS VAL:'c'"[x]);//Display the String
                }
                break;

            case 'D'://if RCREG value is D
                lcdcmd(0x80);//display value in first line
                for ( x = 0; x < 11; x++)//loop upto 0 to 11
                {
                    lcddata("REC VAL:'D'"[x]);//Display the String
                }
                TXREG = 'd'; //Transmiting 'd' from slave to master
                 lcdcmd(0xC0);//display value in secound line
                for ( x = 0; x < 13; x++)//loop upto 0 to 13
                {
                    lcddata("TRANS VAL:'d'"[x]);//Display the String
                }
                break;
            }
            __delay_ms(100);
        }
    }
}


void rec_init()
{
    
    TRISB=0x00;//Input and Output setup for LCD 
    TRISC=0xC0;//RC6 Trans and RC7 reciver enable for serial port 1100 0000
    TXSTA=0x20;//0010 0000 Transmit enable
    RCSTA=0x90;//10010000  recevier enable
    SPBRG=0x09;//setting baud rate for 9600 is fosc/64*9600-1 = 6000000/614000=9.7
     lcdcmd(0x3F);  //0011 1111
    __delay_ms(100);
     lcdcmd(0x3F); //0011 1111
    __delay_ms(100);
     lcdcmd(0x3F); //0011 1111
    __delay_ms(100);
     lcdcmd(0x38) ; //0011 1000
    __delay_ms(100);
     lcdcmd(0x06);  //0000 0110
    __delay_ms(100);
     lcdcmd(0x0C); //0000 1100
    __delay_ms(100);
     lcdcmd(0x01); //0000 0001
    __delay_ms(100);
}


void lcdcmd(unsigned char i)
{
    PORTC&=0xF7;  //RS =0
    PORTB=i; // data set to portd
    PORTC|=0x01; //EN=1
    PORTC&=~0x01;  //EN=0
    __delay_ms(100);
}
void lcddata(unsigned char i)
{
    PORTC|=0x08; //RS =1
    PORTB=i;     // data set to portd
    PORTC|=0x01; //EN=1
    PORTC&=~0x01;   //EN=0
    __delay_ms(100);
}
