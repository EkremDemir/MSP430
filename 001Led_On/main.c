#include <msp430.h> 
#include <stdint.h>

/**
 * main.c
 */

/*Function prototypes*/
void delay_ms(uint16_t time);

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	/*Set Ports*/
	P1DIR |= BIT0;        //set pin P1.0 as output
	P1OUT &= ~(BIT0);     //Clear bit

	while(1)
	{
	    P1OUT ^= BIT0;    // Toggle the pin P1.0
	    delay_ms(500);

	}

}

void delay_ms(uint16_t time)
{
    while(time)
    {
        __delay_cycles(1000);  //By default clock is 1 MHZ. Hence 1 tick is 1us. 1ms means 1000 ticks.

        --time;
    }
}
