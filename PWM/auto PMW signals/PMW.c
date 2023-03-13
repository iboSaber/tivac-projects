/*
 * Test 11.c
 *
 *  Created on: Jan 20, 2023
 *      Author: ibrah
 */


/* Define  integer data types */

#include <stdint.h>

/*  TM4C123GH6PM Register Definitions */

#include "inc\tm4c123gh6pm.h"


/* Generates 10KHz and 50% duty cycle on PF2 pin of TM4C123 Tiva C Launchpad */
/* PWM1 module and PWM generator 3 of PWM1 module is used */

    void delay(long d)
    {
        while(d--);
    }

    uint16_t i;


    int main()
    {
        /* Clock setting for PWM and GPIO PORT */
        SYSCTL_RCGCPWM_R |= (1<<1); /* Enable clock to PWM1 module */
        SYSCTL_RCGCGPIO_R |= (1<<5); /* Enable system clock to PORTF */
        SYSCTL_RCC_R &= (~(1<<20) ); /* Directly feed clock to PWM1 module without pre-divider */

        /* Setting of PF2 pin for M1PWM6 channel output pin */
        GPIO_PORTF_AFSEL_R |= (1<<2); /* PF2 sets a alternate function */
        GPIO_PORTF_PCTL_R = 0x00000500; /* make PF2 PWM output pin */
        GPIO_PORTF_DEN_R |= (1<<2); /* set PF2 as a digital pin */

        /* PWM1 channel 6 setting */
        PWM1_3_CTL_R &= (~(1<<0)); /* Disable Generator 3 counter */
        PWM1_3_CTL_R &= (~(1<<1)); /* select down count mode of counter 3*/
        PWM1_3_LOAD_R = 16000; /* set load value for 100kHz (16MHz/1600) */
        PWM1_3_CMPA_R = 8000; /* set duty cyle to 50% by loading of 16000 to PWM1CMPA */
        PWM1_3_GENA_R |= (1<<2) | (1<<3)  | (1<<7); /* Set PWM output when counter reloaded and clear when match*/
        PWM1_3_CTL_R |= ((1<<0)); /* Enable Generator 3 counter */
        PWM1_ENABLE_R |= (1<<6); /* Enable PWM1 channel 6 output */


        while (1)
        {
            for(i=0; i<16000; i++)
            {
                PWM1_3_CMPA_R = i;
                delay(1000);
            }

            delay(1000000);

            for (i=16000; i>0; i--)
            {
                PWM1_3_CMPA_R = i;
                delay(1000);
            }

            delay(1000000);
        }
}
