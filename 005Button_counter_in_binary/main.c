#include <msp430.h> 


#define LD0   BIT0
#define LD1   BIT1
#define LD2   BIT2
#define LD3   BIT4
#define LD4   BIT5


#define LENGTH 5 //length of the bits = number of leds.

/**
 * main.c
 * purpose:
 * Count the number of pressed button, then show this number in binary format using leds.
 * Since, there are 5 led, button pressed counter can be maximum 31
 * For example, counter  is 21 = 10101b, then LD0 is high, LD1 is low, LD2 is high, LD3 is low, LD4 is high
 */


void delay_ms(int time);
void GPIO_Init(void);
void changeState(int number);

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    GPIO_Init();


    int counter = 0; //010101 (led state)



    while(1)
    {
        if(!(P1IN & (BIT3)))
        {
            ++counter;
            //if counter exceeds max then set it zero
            if(counter >= 32)
            {
                counter = 0;
            }

            changeState(counter);      //Change state of the leds

            //Put some delay because of debounce problem of button
            //delay_ms(1);  delay was not a efficient way,Hence wait until bit of P1.3 becomes 1.
            while(!(P1IN & (BIT3)));


        }

    }


}



void GPIO_Init(void)
{
    /*Set Ports*/

    //Configure LEDs
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


    //Configure User Button(P1.3 in MSP430G2353)
    P1DIR &= ~BIT3;       //Configure  P1.3 as input
    P1REN |=  BIT3;       //Enable the pull up or down resistor
    P1OUT |=  BIT3;       //Enable the pull up resistor, if button is pressed input will read 0

}


void changeState(int number)
{
    int pinNumbersLed[LENGTH] = {0,1,2,4,5}; //Pin name of leds, for shifting purpose
    int i;
    int state;  //state of led is zero or 1, if it is zero go to else,otherwise  go to if statement
    for ( i = 0;  i < LENGTH; ++i)
    {
        state = (number % 2);
        if(state)
        {
            P1OUT |= state << pinNumbersLed[i];
        }
        else
        {
            P1OUT &= ~(1 << pinNumbersLed[i]);
        }
        number = number / 2;
    }
    (void)number;
}

