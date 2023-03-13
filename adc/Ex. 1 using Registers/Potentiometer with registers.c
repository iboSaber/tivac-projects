/*
 * Tiva C interface with  push button.c
 *
 *  Created on: Jan 21, 2023
 *      Author: ibrah
 */

// ========================= Header Files =========================

#include "pin/pin.h"
#include "delay/delay.h"

// ================================ Main =============================
/* TM4C123G Tiva C Series ADC Example */

/* This Program controls the onboard green LED based on discrete digital value of ADC */
/* If AN0 channel value is less 2048 digital value than LED turns off and otherwise remain on */
#include "inc\TM4C123GH6PM.h"

int main(void)
{
     unsigned int adc_value;
     pin_t led_1, led_2;

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

      /*Initialize PF3 as a digital output pin */

////    SYSCTL_RCGCGPIO_R |= 0x20; // turn on bus clock for GPIOF
//    SYSCTL_RCGCGPIO_R |= (1 << 5); // Setting the 6th bit (Port F) same as one above it
//    GPIO_PORTF_DIR_R  |= 0x08; //set GREEN pin as a digital output pin
//    GPIO_PORTF_DEN_R  |= 0x08;  // Enable PF3 pin as a digital pin

    // Red LED
           //------------
           led_1.port           =   PORT_E;
           led_1.place          =   PIN_4;
           led_1.dir            =   PIN_OUT;
           led_1.current        =   CURRENT_2MA;
           led_1.type           =   PIN_STD;


           // Green LED
           //------------
           led_2.port           =   PORT_D;
           led_2.place          =   PIN_7;
           led_2.dir            =   PIN_OUT;
           led_2.current        =   CURRENT_2MA;
           led_2.type           =   PIN_STD;



    // Initialize
    //------------
    Pin_Init(led_1);
    Pin_Init(led_2);


    while(1)
    {
        ADC0_PSSI_R |= (1<<3);        /* Enable SS3 conversion or start sampling data from AN0 */
        while((ADC0_RIS_R & 8) == 0) ;   /* Wait until sample conversion completed*/
        adc_value = ADC0_SSFIFO3_R; /* read adc conversion result from SS3 FIFO*/
        ADC0_ISC_R = 8;          /* clear conversion clear flag bit*/



// increase constant 320
        if(adc_value < 80 ){
//            GPIO_PORTF_DATA_R  = 0x00; /* turn off green LED*/
        Pin_Write (led_1, HIGH);
        Pin_Write (led_2, LOW);


        }


        else if(adc_value < 160){
//                GPIO_PORTF_DATA_R  = 0x08; /* turn on green LED*/
                Pin_Write (led_1, HIGH);
                Pin_Write (led_2, HIGH);

            }

        else if(adc_value < 480){
//                GPIO_PORTF_DATA_R  = 0x08; /* turn on green LED*/
                Pin_Write (led_1, HIGH);
                Pin_Write (led_2, HIGH);

            }

        else if(adc_value < 800){
//                GPIO_PORTF_DATA_R  = 0x08; /* turn on green LED*/
                Pin_Write (led_1, HIGH);
                Pin_Write (led_2, HIGH);

            }

        else if(adc_value < 1120){
//                GPIO_PORTF_DATA_R  = 0x08; /* turn on green LED*/
                Pin_Write (led_1, HIGH);
                Pin_Write (led_2, HIGH);

            }

        else if(adc_value < 1440){
//                GPIO_PORTF_DATA_R  = 0x08; /* turn on green LED*/
                Pin_Write (led_1, HIGH);
                Pin_Write (led_2, HIGH);

            }

        else if(adc_value < 1760){
//                GPIO_PORTF_DATA_R  = 0x08; /* turn on green LED*/
                Pin_Write (led_1, HIGH);
                Pin_Write (led_2, HIGH);

            }

        else if(adc_value < 2080){
//                GPIO_PORTF_DATA_R  = 0x08; /* turn on green LED*/
                Pin_Write (led_1, HIGH);
                Pin_Write (led_2, HIGH);

            }
    }
}


// ================================ END =============================

