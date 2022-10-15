#include <msp430.h> 
#include <stdio.h>
#include <stdint.h>


/**
 * main.c
 */

void delay(float t);
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	P1DIR = 0x01; //port 1 channele 1 is enable
	P1OUT = 0x00; //pint 1 is in low
	P1REN = 0x00 ;
 	while(1)
	{
	    P1OUT ^= 0x01;
	    delay(1);


	}


}



void delay(float t)
{
    unsigned long time;

    time = (unsigned long)t;
    time *= 2;
    while( time > 0)
    {
        __delay_cycles(500000);
        --time;
    }



}

