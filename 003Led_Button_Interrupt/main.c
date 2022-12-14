#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	/*Configure the pins*/

	//Set P1.1 as output for external led(with 220 ohm resistor)
	P1DIR |= BIT1;     // Set P1.1 as output
	P1OUT &= ~BIT1;   //Clear bit of the P1.1

	//Set the bits of pin P1.3 for button(internal button) and configure interrupt
	P1DIR &= ~BIT3;   //Set P1.1 as input
    P1REN |=  BIT3;   //Enable the pull up or down resistor
    P1OUT |=  BIT3;   //Enable the pull up resistor, if button is pressed input will read 0.

    P1IES |=  BIT3;   //Select interrupt edge selection as from High to Low. Because when button is pressed the state change from high to low(1 to 0)
    P1IE  |=  BIT3;   //Enable the interrupt for P1.3 pin
    P1IFG &= ~BIT3;   //Clear the interrupt flag for pin P1.3

    __enable_interrupt();  //Enable Maskeble interrupts

    while(1);
}



#pragma vector = PORT1_VECTOR

__interrupt void ISR_Button(void)
{
    P1OUT ^= BIT1;      //Toggle the external led

    //Put some delay because of debounce problem of button
    //delay_ms(50);  delay was not a efficient way,Hence wait until bit of P1.3 becomes 1.
    while(!(P1IN & (BIT3)));
    P1IFG &= ~BIT3;   //Clear the interrupt flag for pin P1.3
}
