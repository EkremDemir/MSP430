#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	/*Configure Ports*/

    //Configure LED1
    P1DIR |= BIT0;        //set pin P1.0 as a output
    P1OUT &= ~(BIT0);     //Clear bit of P1.0


    //Set up timer
	TA0CTL |= TACLR;       //Reset the timer(0x0004)
	TA0CTL |= TASSEL_1;    //Timer A clock source select: 1 - ACLK(32768 hz)
	//dividers is 1 as default
	TA0CTL |= MC_2;        //Timer A mode control: 2 - Continous up to 0xFFFF

	//Set up TA0 overflow IRQ
	TA0CTL |= TAIE;        //Timer A counter interrupt enable
	__enable_interrupt();  //Enable maskable IRQs

	TA0CTL &= ~TAIFG;      //Clear the interrupt flag


	while(1)
	{

	}

	return 0;
}


//ISRs----------
#pragma vector = t
