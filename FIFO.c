#include "MK64F12.h"
#include "fsl_pit.h"
#include "fsl_uart.h"
#include "DataTypeDefinitions.h"
#include "FIFO.h"

//FIFO's flags
static BooleanType full = FALSE;
static BooleanType empty = TRUE;
//Current index of the FIFO
static sint8 FIFOIndex = 0;
//FIFO array
static sint8 FIFO[FIFO_LENGHT];

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

BooleanType push (sint8 newVal)
{
    if (FIFO_LENGHT <= FIFOIndex)
    { //check if FIFO it's full
        full = TRUE;
        return FALSE;
    }

    FIFO[FIFOIndex++] = newVal; //add new value to the FIFO
    empty = FALSE; //The FIFO isn't empty because we just added a new value
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
