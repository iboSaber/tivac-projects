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

    pin_t button, led_1, led_2, led_3, led_4;
    uint8_t var;

    Set_Clock_80();


    //Button
    //------
    button.port       =   PORT_F;
    button.place      =   PIN_7; // SW1 on kit
    button.dir        =   PIN_IN;
    button.current    =   CURRENT_2MA;
    button.type       =   PIN_PU;


    // Red LED
       //------------
       led_1.port           =   PORT_C;
       led_1.place          =   PIN_4;
       led_1.dir            =   PIN_OUT;
       led_1.current        =   CURRENT_2MA;
       led_1.type           =   PIN_STD;


       // Green LED
       //------------
       led_2.port           =   PORT_C;
       led_2.place          =   PIN_5;
       led_2.dir            =   PIN_OUT;
       led_2.current        =   CURRENT_2MA;
       led_2.type           =   PIN_STD;

       // Green LED
       //------------
       led_3.port           =   PORT_C;
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

       // Initialize
       //------------
       Pin_Init(button);
       Pin_Init(led_1);
       Pin_Init(led_2);
       Pin_Init(led_3);
       Pin_Init(led_4);



        while(1) {

         var =  Pin_Read(button);

         if(var < 80)
         {
                              Pin_Write (led_1, HIGH);

                              Pin_Write (led_2, LOW);
                              Pin_Write (led_3, LOW);
                              Pin_Write (led_4, LOW);
         }

         else if(var < 160)
         {
             Pin_Write (led_1, HIGH);
             Pin_Write (led_2, HIGH);

             Pin_Write (led_3, LOW);
             Pin_Write (led_4, LOW);
         }

         else if(var < 240)
         {
             Pin_Write (led_1, HIGH);
             Pin_Write (led_2, HIGH);
             Pin_Write (led_3, HIGH);

             Pin_Write (led_4, LOW);
         }

         else if(var < 320)
         {
             Pin_Write (led_1, HIGH);
             Pin_Write (led_2, HIGH);
             Pin_Write (led_3, HIGH);
             Pin_Write (led_4, HIGH);
         }



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
