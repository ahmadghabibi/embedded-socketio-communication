
#include <stdint.h>
#include <stdbool.h>

#include "driverlib/pin_map.h"
#include "UartService.h"
#include "HwSupport.h"

#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
    while(1);
}
#endif

int heartbeatStatus = 0 ;

void    runLedRequestLoop()
{
    int arrIdx = 0 ;
    LedRequest   requets[] =
       {
         {RED,true,200000},
         {BLUE,false,200000},
         {GREEN,true,200000}
       };

    HwTurnOffAllLeds(requets);
    HwToggleLed(&(requets[arrIdx++]));
    if (arrIdx == Arr_Size)
    {
         arrIdx = 0 ;
    }
}

void TurnSelectedLedOn(char ledColorSelection)
{

  HwTurnLedOff(RED);
  HwTurnLedOff(BLUE);
  HwTurnLedOff(GREEN);
  switch (ledColorSelection)
  {
       case 'r':
           HwTurnOnLED(RED);
           break;
       case 'b':
            HwTurnOnLED(BLUE);
            break ;
       case 'g':
            HwTurnOnLED(GREEN);
            break ;
       default:
             break;
   }
}

void HwHeartbeat()
{
    if (heartbeatStatus == 0)
    {
        HwTurnOnLED(GREEN);
        heartbeatStatus = 1;

    }
    else
    {
        HwTurnLedOff(GREEN);
        heartbeatStatus = 0 ;
    }
}
void HwInit()
{

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

       SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

       SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);

       while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB))
               {
               }


       while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA))
                   {
                   }

       while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE))
       {
       }

       GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_5);         // yellow LED
       GPIOPinTypeGPIOInput(GPIO_PORTB_BASE, GPIO_PIN_4);          // external strapping
       GPIOPadConfigSet(GPIO_PORTB_BASE, GPIO_PIN_4,GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);




       //
       // Enable the GPIO port that is used for the on-board LED.  0xf0000805
       //
       SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

       //
       // Check if the peripheral access is enabled.
       //
       while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
       {
       }

       //
       // Enable the GPIO pin for the LED (PF3).  Set the direction as output, and
       // enable the GPIO pin for digital function.
       //


       // -- Red

          GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1);
       // -- Blue
         GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2);

       // -- Green
       GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3);

       GPIOPinConfigure(GPIO_PB0_U1RX);
       GPIOPinConfigure(GPIO_PB1_U1TX);
       GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);



       GPIOPinConfigure(GPIO_PA0_U0RX);
       GPIOPinConfigure(GPIO_PA1_U0TX);
       GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
       UARTInit();


}


void HwTurnOnLED(ledColors color)
{

    switch (color)
        {
           case RED:
                 GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);
                 break;
           case BLUE:
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);
                break ;
            case GREEN:
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
                break ;
        }
}


void HwTurnLedOff(ledColors color)
{

    switch (color)
    {
    case RED:
             GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x0);
             break;
    case BLUE:
              GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0x0);
              break ;
    case GREEN:
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x0) ;
            break ;


    }
}

void waitFor(int loopCount)
{
   volatile uint32_t ui32Loop;
   for(ui32Loop = 0; ui32Loop < loopCount; ui32Loop++)
   {
   }
}

/*
void  HwToggleLed(LedRequest* req)
{
    if (req->turnLedOn)
    {
        HwTurnOnLED(req->color);
        req->turnLedOn = false;
    }
    else
    {
        HwTurnLedOff(req->color);
        req->turnLedOn = true;

    }
    waitFor(req->timeToWait);
}
void HwTurnOffAllLeds(LedRequest req[])
{
    int i ;
    for( i=0;i<Arr_Size;i++)
    {
          HwTurnLedOff(req[i].color);
    }
    waitFor(200000);
}

*/


