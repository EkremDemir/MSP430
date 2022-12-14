#include <msp430.h> 

/*
 * main.c
 */


void delay_ms(int time);

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
    /*Set Ports*/

	//Configure LED1
    P1DIR |= BIT0;        //set pin P1.0 as a output
    P1OUT &= ~(BIT0);     //Clear bit of P1.0

    //Configure User Button(P1.3 in MSP430G2353)
    P1DIR &= ~BIT3;       //Configure  P1.3 as input
    P1REN |=  BIT3;       //Enable the pull up or down resistor
    P1OUT |=  BIT3;       //Enable the pull up resistor, if button is pressed input will read 0.


    while(1)
    {
        if(!(P1IN & (BIT3)))
        {
            P1OUT ^= BIT0;      //Toggle the LED1

            //Put some delay because of debounce problem of button
            //delay_ms(1);  delay was not a efficient way,Hence wait until bit of P1.3 becomes 1.
            while(!(P1IN & (BIT3)));
        }

    }
}


void delay_ms(int time)
{
    while(time)
    {
        __delay_cycles(1000);  //By default clock is 1 MHZ. Hence 1 tick is 1us. 1ms means 1000 ticks.

        --time;
    }
}
