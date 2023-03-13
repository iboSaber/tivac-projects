/*
 * Tiva C interface with  push button.c
 *
 *  Created on: Jan 21, 2023
 *      Author: ibrah
 */

// ========================= Header Files =========================

#include "pin/pin.h"
#include "delay/delay.h"

// ======================== Macro ======================
#define DEBOUNCE_DELAY  50   // 50 Milli seconed


// ===========================Function Prototypes ======================
void Set_Clock_80(void);


// ================================ Main =============================
void main(void){

    pin_t button, led;
    uint8_t button_state, flag = 0;

    Set_Clock_80();


    //Button
    //------
    button.port       =   PORT_F;
    button.place      =   PIN_0; // SW1 on kit
    button.dir        =   PIN_IN;
    button.current    =   CURRENT_2MA;
    button.type       =   PIN_PU;


    // External LED
    //------------

    led.port           =   PORT_D;
    led.place          =   PIN_7; // SW1 on kit
    led.dir            =   PIN_OUT;
    led.current        =   CURRENT_2MA;
    led.type           =   PIN_STD;



    // Initialize
    //------------
    Pin_Init(button);
    Pin_Init(led);

        while(1) {

        button_state =  Pin_Read(button);

        // Button is pressed
        if(button_state == LOW && flag == 0) {

            Pin_Write (led, TOGGLE);
            flag = 1;
            DelayMs(DEBOUNCE_DELAY);
        }   // end if


        // Button is NOT pressed
        if(button_state == HIGH){

            flag = 0;

        }   // end if

    }   // END while
}



void Set_Clock_80(void) {


    // (1) Set the clock to run at 80 MHz
    //------------------------------
    // SYSCTL_OSC_MAIN   : Osc. source is main osc
    // SYSCTL_XTAL_16MHZ : External crystal is 16 MHz
    // SXSCTL_USE_PLL    : System clock is the PLL clock
    // SYSCTL_SYSDIV_2_5 : Frequency 80 MHz


    SysCtlClockSet(SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ | SYSCTL_USE_PLL | SYSCTL_SYSDIV_2_5);
}

// ================================ END =============================
