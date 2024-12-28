
/*
 * HwSupport.h
 *
 *  Created on: Oct 3, 2023
 *      Author: ahmad
 */

#ifndef HWSUPPORT_H_
#define HWSUPPORT_H_
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

#include "driverlib/interrupt.h"

#include "inc/TM4C123gh6pm.h"


#define Arr_Size 3
typedef enum {RED,BLUE,GREEN} ledColors;

typedef struct
{
    ledColors color;
    bool  turnLedOn;
    uint32_t timeToWait;
}LedRequest;
extern void HwHeartbeat();
extern void HwToggleLed(LedRequest* req);
extern void HwTurnOffAllLeds(LedRequest req[]);
extern void waitFor(int loopCount);
extern void HwInit();
extern void HwTurnOnLED(ledColors color);
extern void HwTurnLedOff(ledColors color);
extern void HwHeartbeat ();
#endif /* HWSUPPORT_H_ */
