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


void main(void){

    uint32_t ui32Loop = 0;  // used for delay

    // (1) Enable the GPIO port that is used for the on-board LED.
    // -----------------------------------------------------------

    //SYSCTL_RCGCGPIO_R = SYSCTL_RCGCGPIO_R5; = /// Port F

    // OR

    //SYSCTL_RCGCGPIO_R = 0x20; // Port F

    // OR

    //SYSCTL_RCGCGPIO_R |= 0x20; // Port F

    // OR

    SYSCTL_RCGCGPIO_R |= (1 << 5); // Setting the 6th bit (Port F)


    // After enabling the clock to a GPIO module, there must be a 3 clock cycle

    // delay before accessing the GPIO registers.
    // -----------------------------------------------------------

    // Do a dummy read to insert a few cycles after peripheral enable

    ui32Loop = SYSCTL_RCGCGPIO_R;


    // (2) Set the direction as output
    // -----------------------------------------------------------

    GPIO_PORTF_DIR_R |= (1 << 1); // Setting the 2nd bit (PF1 --> Red)


    // (3) Configure the GPIOAFSEL register to program PF as a GPIO
    // -----------------------------------------------------------

    GPIO_PORTF_AFSEL_R = 0x00;


    // (4) Enable the PFl pin for digital function.
    // -----------------------------------------------------------

    GPIO_PORTF_DEN_R |= (1 << 1); // Setting 2nd bit


    // Write logic low on PF1

    GPIO_PORTF_DATA_R &= ~(1 << 1); // Clearing 2nd bit



    while (1) {
        // Turn on the LED.
        GPIO_PORTF_DATA_R |= (1 << 1); // Setting 2nd bit

        // Delay for a bit.
        for(ui32Loop = 0; ui32Loop < 400000; ui32Loop++) {

            // Nothing
        }

        // Turn off the LED.
        GPIO_PORTF_DATA_R &= ~(1 << 1); // Clearing 2nd bit

        // Delay for a bit.
        for(ui32Loop = 0; ui32Loop < 400000; ui32Loop++) {

        // Nothing
        }
    }

}
