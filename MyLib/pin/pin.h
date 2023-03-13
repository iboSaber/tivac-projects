/*
 * pin.h
 *
 *  Created on: Jan 24, 2023
 *      Author: ibrah
 */

#ifndef PIN_H__
#define PIN_H_H_

// ========================= Header Files =========================
#include <stdint.h>
#include <stdbool.h>


/* Macros defining the memory map of the device */
#include "inc/hw_memmap.h"


/* Prototypes for the system control driver */
#include "driverlib/sysctl.h"


/* Defines and Prototypes for GPIO API */
#include "driverlib/gpio.h"


// ========================= Macro =========================

// Ports
//-----
#define PORT_A  GPIO_PORTA_AHB_BASE       // GPIO Port A (high speed)
#define PORT_B  GPIO_PORTB_AHB_BASE       // GPIO Port B (high speed)
#define PORT_C  GPIO_PORTC_AHB_BASE       // GPIO Port C (high speed)
#define PORT_D  GPIO_PORTD_AHB_BASE       // GPIO Port D (high speed)
#define PORT_E  GPIO_PORTE_AHB_BASE       // GPIO Port E (high speed)
#define PORT_F  GPIO_PORTF_AHB_BASE       // GPIO Port F (high speed)


// Pin
//-----
#define PIN_0   GPIO_PIN_0                // GPIO pin 0
#define PIN_1   GPIO_PIN_1                // GPIO pin 1
#define PIN_2   GPIO_PIN_2                // GPIO pin 2
#define PIN_3   GPIO_PIN_3                // GPIO pin 3
#define PIN_4   GPIO_PIN_4                // GPIO pin 4
#define PIN_5   GPIO_PIN_5                // GPIO pin 5
#define PIN_6   GPIO_PIN_6                // GPIO pin 6
#define PIN_7   GPIO_PIN_7                // GPIO pin 7


// Pad type
//-----
#define PIN_STD     GPIO_PIN_TYPE_STD         // Push-pull
#define PIN_PU     GPIO_PIN_TYPE_STD_WPU     // Push-pull with weak pull-up
#define PIN_PD     GPIO_PIN_TYPE_STD_WPD     // Push-pull with weak pull-down


// Direction
//-----
#define PIN_IN      GPIO_DIR_MODE_IN          // Pin is a GPIO input
#define PIN_OUT     GPIO_DIR_MODE_OUT         // Pin is a GPIO output


// Current
//-----
#define CURRENT_2MA     GPIO_STRENGTH_2MA         // 2mA drive strength
#define CURRENT_4MA     GPIO_STRENGTH_4MA         // 4mA drive strength
#define CURRENT_8MA     GPIO_STRENGTH_8MA         // 8mA drive strength


// Available PIN Commands
//------------------------
//  *** Important: Do not change these values ****
//-------------------------------------------------------------
#define LOW     0   //Turn PIN off
#define HIGH    1   //Turn PIN on
#define TOGGLE  2   //Invert the PIN



// ========================= Structure =========================

// To store a PIN properties
typedef struct{
    uint32_t    port;   // port address
    uint32_t    place;  // pin place
    uint32_t    dir;    // pin direction
    uint32_t    current;// pin maximum current
    uint32_t    type;   // Pad type

} pin_t;                // pin data type



// ========================Function Prototypes ======================

extern void Pin_Init(pin_t pin); // Do Preparation and configuration for the port & for the pin i m gonna work on

//*****************************************************

extern void Pin_Write(pin_t pin, uint8_t cmd); // Give me High or Low on the PIN im working with


//*****************************************************

extern uint8_t Pin_Read(pin_t pin); // return a vlaue of HIGH or LOW constant

//--------------------------------------------------------------------------------------------

#endif /*PIN_H__H_ */
