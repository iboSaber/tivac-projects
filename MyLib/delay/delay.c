/*
 * delay.c
 *
 *  Created on: Jan 24, 2023
 *      Author: ibrah
 */


// ========================= Header Files =========================
#include <stdint.h>
#include <stdbool.h>

/* Prototypes for the system control driver */

#include "driverlib/sysctl.h"

#include "delay.h"


// ============================= Implementation =============================

void DelayMs(uint32_t ui32Ms) {

    /* First:

        * SysCt1ClockGet() => clock rate (Hz)
        * since the clock time (s) = 1 / clock rate (Hz)
        * then the clock time (s) = 1 / SysCtlClockGet()
        * so the clock time (us) = 1 * 1000000 / SysCtlClockGet() --> (1)

    * Second:

        * The loop of SysCtlDelay() = 3 clock cycles

        * then the 1 loop time = 3 clock time --> (2) from eq (1) and eq (2)

        *        1 loop time (ms) = 3 * (1 * 10000000 / SysCtlClockGet())

        *        1 loop time (ms) = 30000000 / SysCtlClockGet() --> (3)

        * so     2 loop time (ms) = 2 * 3000000 / SysCt1ClockGet ()

        * let    Count = ui32Ms --> (4) by equating Equation (3) with Equation (4)

        *        count = ui32Ms / [3000000 / SysCtlClockGet ()]

        *        count = ui32Ms * SysCtlClockGet() / 3000000 */

        SysCtlDelay(SysCtlClockGet() * ((float)ui32Ms / 3000.0));
  }

//************************************************************************

void DelayUs (uint32_t ui32Us) {

    /* First:

        * SysCt1ClockGet() => clock rate (Hz)
        * since the clock time (s) = 1 / clock rate (Hz)
        * then the clock time (s) = 1 / SysCtlClockGet()
        * so the clock time (ms) = 1 * 1000 / SysCtlClockGet() --> (1)

    * Second:

        * The loop of SysCtlDelay() = 3 clock cycles

        * then the 1 loop time = 3 clock time --> (2) from eq (1) and eq (2)

        *        1 loop time (ms) = 3 * (1 * 1000 / SysCtlClockGet())

        *        1 loop time (ms) = 3000 / SysCtlClockGet() --> (3)

        * so     2 loop time (ms) = 2 * 3000 / SysCt1ClockGet ()

        * let    Count = ui32Ms --> (4) by equating Equation (3) with Equation (4)

        *        count = ui32Ms / [3000 / SysCtlClockGet ()]

        *        count = ui32Ms * SysCtlClockGet() / 3000 */

        SysCtlDelay(SysCtlClockGet() * ((float)ui32Us / 3000000.0));
  }
