/*
 * Led Blinking using main osc.c
 *
 *  Created on: Jan 21, 2023
 *      Author: ibrah
 */


// ========================== Header Files =======================

#include <stdint.h> /* Defines integer data types */
#include <stdbool.h>  /* Defines  boolean data types */

 /* Macros defining the memory map of the device */
#include "inc/hw_memmap.h"

/* Prototypes for the system control driver */
#include "driverlib/sysctl.h"

/* Defines & Prototypes for GPIO API*/
#include "driverlib/gpio.h"

/* Include My delay library y that i made previously */
#include "delay/delay.h"
// ========================== Macros =======================
#define DELAY_TIME 500   //500 millisecond


void DelayMs(uint32_t ui32Ms);


// ========================== Main =========================

void main(void){


    // (1) Set the clock to run at 80 MHz
    //------------------------------
    // SYSCTL_OSC_MAIN   : Osc source is main osc
    // SYSCTL_XTAL_16MHZ : External crystal is 16 MHz
    // SXSCTL_USE_PLL    : System clock is the PLL clock
    // SYSCTL_SYSDIV_2_5 : Frequency 80 MHz


    SysCtlClockSet(SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ | SYSCTL_USE_PLL | SYSCTL_SYSDIV_2_5);


    // (2) Enable the GPIO port that is used for the on-board LED
    //------------------------------
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);



    // After enabling the clock to a GPIO module, there must be a 3 clock cycle
    // delay before accessing the GPIO registers.
    //---------------------------------------------------------------------------
    // SysCtlDelay(3);   // Each value delays for 3 clock cycles, so in our case
                        // with the value 3, we delay 9 clock cycle:

    // OR
    // we can use the next code snippet
    // Check if the peripheral access is enabled. if the peripheral access is not enabled it will loop until it does
    while (!SysCtlPeripheralReady (SYSCTL_PERIPH_GPIOF)){


        // Nothing
    }


    // (3) Set the direction as output
    // (4) Configure the GPIOAFSEL register to program PF as a GPIO
    // (5) Enable the PF1 pin for digital function.
    //---------------------------------------------------------------------------
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1);


    // Write logic low on PFL
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0);

    // Loop forever.
    while(1) {

        // Turn on the LED.
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0b10); // writing high using binary

        // Delay for DELAY_TIME
        DelayMs(DELAY_TIME) ;

        // Turn off the LED.
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0);

        // Delay for DELAY TIME
        DelayMs (DELAY_TIME);
    }
}
// ========================== End of Main =========================

