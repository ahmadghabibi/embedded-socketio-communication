#ifndef UARTSERVICE_H
#define UARTSERVICE_H

#define USE_INTERRUPTS 1

// Setup



extern void UART0IntHandler();
extern void UARTInit();

// Runtime service
extern void UARTSend(const uint8_t *pui8Buffer, uint32_t ui32Count);
extern void UARTSendSingleCharacter(uint8_t c);

#endif
