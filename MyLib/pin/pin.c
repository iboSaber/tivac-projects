/*
 * pin.c
 *
 *  Created on: Jan 24, 2023
 *      Author: ibrah
 */

// ========================= Header Files =========================

#include "pin/pin.h"


// ============================= Implementation =============================
extern void Pin_Init(pin_t pin) {

        uint32_t port_enable = 0;   // Port enable value

        switch (pin.port) {
            case PORT_A:
                port_enable = SYSCTL_PERIPH_GPIOA;
                break;
            case PORT_B:
                port_enable = SYSCTL_PERIPH_GPIOB;
                break;
            case PORT_C:
                port_enable = SYSCTL_PERIPH_GPIOC;
                break;
            case PORT_D:
                port_enable = SYSCTL_PERIPH_GPIOD;
                break;
            case PORT_E:
                port_enable = SYSCTL_PERIPH_GPIOE;
                break;
            default:
                port_enable = SYSCTL_PERIPH_GPIOF;
             break;
        }

        // Enable access to GPIO peripheral via the AHB.
        SysCtlGPIOAHBEnable(port_enable);


        // Enable the port.
        SysCtlPeripheralEnable(port_enable) ;


        // Unlocks a GPIO pin which had been previously locked.
        if(((pin.port == PORT_F) && (pin.place == PIN_0)) || // PFO
        ((pin.port == PORT_D) && (pin.place == PIN_7)) ){  // PD7

            GPIOUnlockPin(pin.port, pin.place);

        }

        // Check if the peripheral access is enabled.
        while(!SysCtlPeripheralReady(port_enable)) {/* Nothing*/}

        // Specify the drive strength.
        // Set the pad configuration.
        GPIOPadConfigSet(pin.port, pin.place, pin.current, pin.type);

        // Set the direction.
        GPIODirModeSet(pin.port, pin.place, pin.dir);

        // Write logic low on pin
        GPIOPinWrite(pin.port, pin.place, 0x00);
}

//---------------------------------------------------------------------------------------

extern void Pin_Write(pin_t pin, uint8_t cmd) {

    uint8_t pin_state = 0;

    switch (cmd) {
        case HIGH:
            GPIOPinWrite(pin.port, pin.place, pin.place);
            break;

        case LOW:
            GPIOPinWrite(pin.port, pin.place, 0x00);
            break;

        default: // TOGGLE
         pin_state = GPIOPinRead(pin.port, pin.place);

         if(pin_state == pin.place){

             GPIOPinWrite(pin.port, pin.place, 0x00);
         }else{

             GPIOPinWrite(pin.port, pin.place, pin.place);
         }

         break;
    }


}

//-----------------------------------------------------------------------------------

extern uint8_t Pin_Read(pin_t pin){

    uint32_t pin_state = 0;

    pin_state = GPIOPinRead(pin.port, pin.place);

    if(pin_state == pin.place){

        return HIGH;
    }else{

        return LOW;
    }

}
// ================================== END =================================

