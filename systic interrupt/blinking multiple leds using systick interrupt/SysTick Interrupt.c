/*
 * Tiva C interface with  push button.c
 *
 *  Created on: Jan 21, 2023
 *      Author: ibrah
 */

// ========================= Header Files =========================

#include "pin/pin.h"


// Prototypes for the NVIC driver
#include "inc/hw_types.h"           // Note: Include hw_types.h before including interrupt-h
#include "driverlib/interrupt.h"
#include "inc/hw_ints.h"            // For interrupt assignments (vector numbers)

// prototypes for the SysTick driver
#include "driverlib/systick.h"
#include "inc/hw_nvic.h"            // For SysTick Current Value Register (NVIC_ST_CURRENT)


// =========================== Variables ======================

volatile pin_t led_1, led_2, led_3, led_4, led_5, led_6, led_7, led_8;

// ===========================Function Prototypes ======================

// Set the clock to run at 8OMHz
void Set_Clock_80(void) ;

// Systick Interrupt Initialize
void Systick_INT_Init (void);

// Systack Interrupt Handler
void Systick_INT_Handler (void) ;

// ================================ Main =============================
void main(void){



    Set_Clock_80();

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

       // Green LED
       //------------
       led_3.port           =   PORT_D;
       led_3.place          =   PIN_6;
       led_3.dir            =   PIN_OUT;
       led_3.current        =   CURRENT_2MA;
       led_3.type           =   PIN_STD;

       // Green LED
       //------------
       led_4.port           =   PORT_C;
       led_4.place          =   PIN_7;
       led_4.dir            =   PIN_OUT;
       led_4.current        =   CURRENT_2MA;
       led_4.type           =   PIN_STD;

       // Green LED
       //------------
       led_5.port           =   PORT_C;
       led_5.place          =   PIN_6;
       led_5.dir            =   PIN_OUT;
       led_5.current        =   CURRENT_2MA;
       led_5.type           =   PIN_STD;

       // Green LED
       //------------
       led_6.port           =   PORT_C;
       led_6.place          =   PIN_5;
       led_6.dir            =   PIN_OUT;
       led_6.current        =   CURRENT_2MA;
       led_6.type           =   PIN_STD;

       // Green LED
       //------------
       led_7.port           =   PORT_C;
       led_7.place          =   PIN_4;
       led_7.dir            =   PIN_OUT;
       led_7.current        =   CURRENT_2MA;
       led_7.type           =   PIN_STD;

       // Green LED
       //------------
       led_8.port           =   PORT_F;
       led_8.place          =   PIN_0;
       led_8.dir            =   PIN_OUT;
       led_8.current        =   CURRENT_2MA;
       led_8.type           =   PIN_STD;

       // Initialize
       //------------
       Pin_Init(led_1);
       Pin_Init(led_2);
       Pin_Init(led_3);
       Pin_Init(led_4);
       Pin_Init(led_5);
       Pin_Init(led_6);
       Pin_Init(led_7);
       Pin_Init(led_8);

    Systick_INT_Init();


        while(1) {

                        __asm(" WFI "); // WET stands tor ‘Wait tor Interrupt
                                        // This instruction allow the core to enter a low power
                                        // mode and stop executing code.
    }   // END while
}


void Set_Clock_80(void) {


    // (1) Set the clock to run at 80 MHz
    //------------------------------
    // SYSCTL_OSC_MAIN   : Osc source is main osc
    // SYSCTL_XTAL_16MHZ : External crystal is 16 MHz
    // SXSCTL_USE_PLL    : System clock is the PLL clock
    // SYSCTL_SYSDIV_2_5 : Frequency 80 MHz


    SysCtlClockSet(SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ | SYSCTL_USE_PLL | SYSCTL_SYSDIV_2_5);
}

//----------------------------------------------------------------------------------------------------

void Systick_INT_Init (void) {

    // 1) Disables the processor interrupt
    IntMasterDisable();

    // 2) Disables the sysTick counter
    SysTickDisable();

    // 3) Sets the period of the SysTick counter.
    SysTickPeriodSet(16000000);                //  200mS / (1 / 8OMHZ) = 16,000,000 Tick (< 16, 777, 216)

    // 4) Clears current value register
    HWREG(NVIC_ST_CURRENT) = 0;                  // Any write to current value register clears it
                                                 // HWREG macro included in "inc/hw_types.h"

    // 5) Registers an interrupt handler
    IntRegister(FAULT_SYSTICK, Systick_INT_Handler) ; // Interrupt assignment = 15 --> system Tick

    // 6) sets the priority of an interrupt
    IntPrioritySet(FAULT_SYSTICK, 0x00);

    // 7) Enables the interrupt on SysTick Level
    SysTickIntEnable();

    // 8) Enables the SysTick counter
    SysTickEnable();

    // 9) Enables Interrupt on NVIC Level
    IntEnable (FAULT_SYSTICK) ;

    // 10) Enables the processor interrupt.
    IntMasterEnable() ;

}
//-----------------------------------------------------------------------------------------------------

void Systick_INT_Handler (void) {

    static uint8_t systick_int_counter = 0;

    /* the Systick interrupt handler is not required to clear the Sysick interrupt source
    * because it is cleared automatically by the NVIC when the interrupt handler is called.
    */


    systick_int_counter ++;

     if(systick_int_counter == 1){

            Pin_Write (led_1, TOGGLE);
            Pin_Write (led_2, LOW);
            Pin_Write (led_3, LOW);
            Pin_Write (led_4, LOW);
            Pin_Write (led_5, LOW);
            Pin_Write (led_6, LOW);
            Pin_Write (led_7, LOW);
            Pin_Write (led_8, LOW);
    }

    else if(systick_int_counter == 2){

        Pin_Write (led_1, LOW);
        Pin_Write (led_2, TOGGLE);
        Pin_Write (led_3, LOW);
        Pin_Write (led_4, LOW);
        Pin_Write (led_5, LOW);
        Pin_Write (led_6, LOW);
        Pin_Write (led_7, LOW);
        Pin_Write (led_8, LOW);

    }

    else if(systick_int_counter == 3){

            Pin_Write(led_1, LOW) ;
            Pin_Write(led_2, LOW) ;
            Pin_Write(led_3, TOGGLE) ;
            Pin_Write (led_4, LOW);
            Pin_Write (led_5, LOW);
            Pin_Write (led_6, LOW);
            Pin_Write (led_7, LOW);
            Pin_Write (led_8, LOW);
    }

    else if(systick_int_counter == 4){

            Pin_Write(led_1, LOW) ;
            Pin_Write(led_2, LOW) ;
            Pin_Write(led_3, LOW) ;
            Pin_Write(led_4, TOGGLE) ;
            Pin_Write (led_5, LOW);
            Pin_Write (led_6, LOW);
            Pin_Write (led_7, LOW);
            Pin_Write (led_8, LOW);
    }

    else if(systick_int_counter == 5){

            Pin_Write(led_1, LOW) ;
            Pin_Write(led_2, LOW) ;
            Pin_Write(led_3, LOW) ;
            Pin_Write (led_4, LOW);
            Pin_Write (led_5, TOGGLE);
            Pin_Write (led_6, LOW);
            Pin_Write (led_7, LOW);
            Pin_Write (led_8, LOW);
    }

    else if(systick_int_counter == 6){

            Pin_Write(led_1, LOW) ;
            Pin_Write(led_2, LOW) ;
            Pin_Write(led_3, LOW) ;
            Pin_Write (led_4, LOW);
            Pin_Write (led_5, LOW);
            Pin_Write (led_6, TOGGLE);
            Pin_Write (led_7, LOW);
            Pin_Write (led_8, LOW);
    }

    else if(systick_int_counter == 7){

            Pin_Write(led_1, LOW) ;
            Pin_Write(led_2, LOW) ;
            Pin_Write(led_3, LOW) ;
            Pin_Write (led_4, LOW);
            Pin_Write (led_5, LOW);
            Pin_Write (led_6, LOW);
            Pin_Write (led_7, TOGGLE);
            Pin_Write (led_8, LOW);
    }

    else if(systick_int_counter == 8){

            systick_int_counter = 0;

            Pin_Write(led_1, LOW) ;
            Pin_Write(led_2, LOW) ;
            Pin_Write(led_3, LOW) ;
            Pin_Write (led_4, LOW);
            Pin_Write (led_5, LOW);
            Pin_Write (led_6, LOW);
            Pin_Write (led_7, LOW);
            Pin_Write (led_8, TOGGLE);
    }

}


// ================================ END =============================
