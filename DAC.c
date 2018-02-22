/*
 * DAC.C
 *
 *  Created on: 03/11/2017
 *      Author: ALEX
 */

#include "DataTypeDefinitions.h"
#include "MK64F12.h"
#include "PIT.h"
#include "GPIO.h"
#include "DAC.h"

static uint16 counter = 0; //index of the function used for the DAC

void DACFunction(PIT_Timer_t pitIn, uint16 actualVal){
    PIT_clear(pitIn);
    DAC0->DAT[0].DATL = (uint8) (actualVal & 0x0FF);//set the low bits of the DAC output
    DAC0->DAT[0].DATH = (uint8) (actualVal >>8);//set the high bits of the DAC output
    PIT_delay(pitIn, SYSTEM_CLOCK, 0.000028);// delay until next function value
    if(++counter>50) counter=0;//if z is the limit value of the sample
}

uint16 getIndex(){
    return counter;
}

void initDAC(){
    PIT_clockGating();//enable usage of the PIT
    SIM->SCGC2 = DAC_SIM;//activates clock for use of PIT
    DAC0->C0 = 0xC0;//Resets DAC output value
}
