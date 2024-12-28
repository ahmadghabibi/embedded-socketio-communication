
#include <stdint.h>
#include <stdbool.h>
#include "UartService.h"
#include "HwSupport.h"
#include "Shared.h"


char currSelection ;
int main(void)
{
    HwInit();
    while(1)
    {
        HwHeartbeat();
       // UARTSendSingleCharacter('C');
       //waitFor(200000);
       if (currSelection == 'r' || currSelection == 'b' || currSelection == 'g')
       {
           TurnSelectedLedOn(currSelection);

           currSelection = ' ';
       }
       else
       {
           UARTSendSingleCharacter('.');
           waitFor(200000);
       }
    }
}
