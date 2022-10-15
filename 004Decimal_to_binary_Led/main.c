#include <msp430.h> 


#define LD0   BIT0
#define LD1   BIT1
#define LD2   BIT2
#define LD3   BIT3
#define LD4   BIT4


#define LENGTH 5 //length of the bits = number of leds.

/**
 * main.c
 * purpose:
 * convert decimal number which in 'num' variable to binary number.
 * For example, num  is 21 = 10101b, then LD0 is high, LD1 is low, LD2 is high, LD3 is low, LD4 is high
 */


void delay_ms(int time);
void GPIO_Init(void);

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	GPIO_Init();


	int num = 21; //010101 (led state)
	int i = 0;


	for ( i = 0;  i < 5; ++i)
	{
        P1OUT |= (num % 2) << i;
        num = num / 2;
	}

	P1OUT |=  num << 5 ;
	(void)num;


}



void GPIO_Init(void)
{
    /*Set Ports*/
    P1DIR |= LD0;        //set pin P1.0 as output
    P1OUT &= ~(LD0);     //Clear bit

    P1DIR |= LD1;        //set pin P1.1 as output
    P1OUT &= ~(LD1);     //Clear bit

    P1DIR |= LD2;        //set pin P1.2 as output
    P1OUT &= ~(LD2);     //Clear bit


    P1DIR |= LD3;        //set pin P1.3 as output
    P1OUT &= ~(LD3);     //Clear bit


    P1DIR |= LD4;        //set pin P1.4 as output
    P1OUT &= ~(LD4);     //Clear bit



}

void delay_ms(int time)
{
    while(time)
    {
        __delay_cycles(1000);  //By default clock is 1 MHZ. Hence 1 tick is 1us. 1ms means 1000 ticks.

        --time;
    }
}

