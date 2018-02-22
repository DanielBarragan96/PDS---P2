#include "MK64F12.h"
#include "fsl_pit.h"
#include "fsl_uart.h"
#include "DataTypeDefinitions.h"
#include "FIFO.h"
#include "DAC.h"
#include "PIT.h"

//FIFO's flags
static BooleanType full = FALSE;
static BooleanType empty = TRUE;
//Current index of the FIFO
static sint8 FIFOIndex = 0;
//FIFO array
static sint8 FIFO[FIFO_LENGHT];

static sint8 currentValue = 0;



int8_t h1[7] = {
0.07840464525404556,
0.17707825519483075,
0.22014353249171387,
0.2759015644497544,
0.22014353249171387,
0.17707825519483075,
0.07840464525404556
};


int8_t h2[7] ={
-0.08857280384687653,
-0.20001387909943527,
-0.13289448474069163,
0.7755518089951376,
-0.13289448474069163,
-0.20001387909943527,
-0.08857280384687653
};

sint8 pop ()
{
    if (empty)
        return FALSE; //if the FIFO is empty we cannot pop
    uint16 index = FIRST_ELEMENT; //the first element of the FIFO
    sint8 popValue = FIFO[index];
    FIFO[index] = (sint8) FIRST_ELEMENT; //erase the first element of the FIFO
    for (index; index < FIFOIndex; index)
    { //Move the upper FIFO chars to the left
        FIFO[index] = FIFO[++index];
    }
    FIFOIndex--;
    if (FALSE == FIFOIndex)
    { //If the FIFOindex is cero, it's empty
        empty = TRUE;
        full = FALSE;
    }
    return popValue;
}

BooleanType manage()
{
    currentValue = (h1[0]*FIFO[0] + h1[1]*FIFO[1] + h1[2]*FIFO[2] + h1[3]*FIFO[3] + h1[4]*FIFO[4] + h1[5]*FIFO[5] + + h1[6]*FIFO[6]);
    pop();
    initDAC();
    DACFunction(PIT_0, (uint8) currentValue);

    return TRUE;
}

BooleanType push (sint8 newVal)
{
    if (FIFO_LENGHT <= FIFOIndex)
    { //check if FIFO it's full
        full = TRUE;
        return FALSE;
    }

    FIFO[FIFOIndex++] = newVal; //add new value to the FIFO
    empty = FALSE; //The FIFO isn't empty because we just added a new value
    if ((FIFO_LENGHT) == FIFOIndex)
    {
        manage();
        return TRUE;
    }
    return TRUE;
}

sint8* getFIFO ()
{
    return &FIFO[FIRST_ELEMENT];
} //return the first element of FIFO direction

BooleanType clearFIFO ()
{
    uint8 eraseIndex = 0;
    while (FIFOIndex >= eraseIndex)
        FIFO[eraseIndex++] = 0; //over write the FIFO values to zero
    //reset variables to initial condition
    FIFOIndex = 0;
    empty = TRUE;
    full = FALSE;
    return TRUE;
}
sint8 getFIFOIndex ()
{
    return FIFOIndex;
}	//return FIFOIndex value
