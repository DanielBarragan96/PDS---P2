#include "GlobalFunctions.h"
#include "DataTypeDefinitions.h"

void delay(uint16 delay){
    volatile uint16 counter;

    for(counter=delay; counter > 0; counter--)
    {//Count until the delay value has passed
    }
}
