/*
 * Test 11.c
 *
 *  Created on: Jan 20, 2023
 *      Author: ibrah
 */


/* Define  integer data types */

#include <stdint.h>

/*  TM4C123GH6PM Register Definitions */

#include "inc/tm4c123gh6pm.h"

#include "pin/pin.h"


/* Generates 10KHz and 50% duty cycle on PF2 pin of TM4C123 Tiva C Launchpad */
/* PWM1 module and PWM generator 3 of PWM1 module is used */

    void delay(long d)
    {
        while(d--);
    }

    uint16_t i;


    int main()
    {
        //-------------------------------------------------------
        unsigned int adc_value;

       /* Enable Clock to ADC0 and GPIO pins*/
       SYSCTL_RCGCGPIO_R |= (1<<4);   /* Enable Clock to GPIOE or PE3/AN0 */
       SYSCTL_RCGCADC_R |= (1<<0);    /* AD0 clock enable*/

       /* initialize PE3 for AIN0 input  */
       GPIO_PORTE_AFSEL_R |= (1<<3);       /* enable alternate function */
       GPIO_PORTE_DEN_R &= ~(1<<3);        /* disable digital function */
       GPIO_PORTE_AMSEL_R |= (1<<3);       /* enable analog function */


       /* initialize sample sequencer3 */
       ADC0_ACTSS_R &= ~(1<<3);        /* disable SS3 during configuration */
       ADC0_EMUX_R &= ~0xF000;    /* software trigger conversion */
       ADC0_SSMUX3_R = 0;         /* get input from channel 0 */
       ADC0_SSCTL3_R |= (1<<1)|(1<<2);        /* take one sample at a time, set flag at 1st sample */
       ADC0_ACTSS_R |= (1<<3);         /* enable ADC0 sequencer 3 */
       delay(1000000);
       //-------------------------------------------------------------


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
               PWM1_3_LOAD_R = 80; /* set load value for 100kHz (16MHz/1600) */
//               PWM1_3_CMPA_R = 320; /* set duty cycle to 50% by loading of 16000 to PWM1CMPA */

               PWM1_3_GENA_R |= (1<<2) | (1<<3)  | (1<<7); /* Set PWM output when counter reloaded and clear when match*/
               PWM1_3_CTL_R |= ((1<<0)); /* Enable Generator 3 counter */
               PWM1_ENABLE_R |= (1<<6); /* Enable PWM1 channel 6 output */


        while(1)
            {
                ADC0_PSSI_R |= (1<<3);        /* Enable SS3 conversion or start sampling data from AN0 */
                while((ADC0_RIS_R & 8) == 0) ;   /* Wait until sample conversion completed*/
                adc_value = ADC0_SSFIFO3_R; /* read adc conversion result from SS3 FIFO*/
                ADC0_ISC_R = 8;          /* clear conversion clear flag bit*/



        // increase ADC constant by 320
                if(adc_value < 80 ){PWM1_3_CMPA_R = 79;} // 0% duty Cycle

                else if(adc_value < 280){ PWM1_3_CMPA_R = 72;} // 10% duty Cycle

                else if(adc_value < 480){ PWM1_3_CMPA_R = 64;} // 20% duty Cycle

                else if(adc_value < 680){ PWM1_3_CMPA_R = 56;} // 30% duty Cycle

                else if(adc_value < 880){ PWM1_3_CMPA_R = 48;} // 40% duty Cycle

                else if(adc_value < 1080){ PWM1_3_CMPA_R = 40;} // 50% duty Cycle

                else if(adc_value < 1280){ PWM1_3_CMPA_R = 32;} // 60% duty Cycle

                else if(adc_value < 1480){ PWM1_3_CMPA_R = 24;} // 70% duty Cycle

                else if(adc_value < 1680){ PWM1_3_CMPA_R = 16;} // 80% duty Cycle

                else if(adc_value < 1880){ PWM1_3_CMPA_R = 8;} // 90% duty Cycle

                else if(adc_value < 2000){ PWM1_3_CMPA_R = 0;} // 100% duty Cycle

            }

}
