#include <msp430.h> 


/**
 * main.c
 */

void GPIO_Init(void);
void TimerA_Init(void);

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	GPIO_Init();
	TimerA_Init();

	return 0;
}



void GPIO_Init(void)
{
    /*Set up Pins*/


    //Led1 pins
    P1DIR |= BIT0;
    P1OUT &= ~BIT0;
}


void TimerA_Init(void)
{

}
