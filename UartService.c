//*****************************************************************************
//
// uart.c - Example for reading data from and writing data to the UART in
//               an interrupt driven fashion.
//
// Copyright (c) 2012-2020 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
// 
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 2.2.0.295 of the EK-TM4C123GXL Firmware Package.
//
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"             // hardware
#include "UartService.h"                // services provided by this module



#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
}
#endif

char currSelection;
void UART0IntHandler  (void)
{
    const uint8_t *pui8Buffer = "UART0 Interrupted";
    uint32_t bufferCount = strlen(pui8Buffer);
    UARTSend(pui8Buffer,bufferCount);
    uint32_t ui32Status;

    ui32Status = MAP_UARTIntStatus(UART0_BASE, true);
    MAP_UARTIntClear(UART0_BASE, ui32Status);

    while(MAP_UARTCharsAvail(UART0_BASE))
    {

        currSelection =    MAP_UARTCharGetNonBlocking(UART0_BASE);
    }
}

void UARTSend(const uint8_t *pui8Buffer, uint32_t ui32Count)
{
    while(ui32Count--)
    {

        MAP_UARTCharPutNonBlocking(UART0_BASE, *pui8Buffer++);
    }
}

void UARTSendSingleCharacter(uint8_t c)
{
    MAP_UARTCharPutNonBlocking(UART0_BASE, c);
}

void UARTInit()
{

    MAP_FPUEnable();
    MAP_FPULazyStackingEnable();
    MAP_SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |SYSCTL_XTAL_16MHZ);

#if USE_INTERRUPTS
    MAP_IntMasterEnable();
#endif

    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    MAP_UARTConfigSetExpClk(UART0_BASE, MAP_SysCtlClockGet(), 9600,
                            (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                             UART_CONFIG_PAR_NONE));

#if USE_INTERRUPTS
    MAP_IntEnable(INT_UART0);
    MAP_UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);
#endif
}
