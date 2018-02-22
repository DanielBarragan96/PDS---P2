/*
 * ADC.c
 *
 *  Created on: 22/10/2017
 *      Author: ALEX
 */

#include "MK64F12.h"
#include "ADC.h"
#include "DataTypeDefinitions.h"
#include "GlobalFunctions.h"

void ADC_init ()
{
    SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK; //starts clock gating for adc0
    ADC0->CFG1 = ADC_CFG1_MODE(1); //parametric setup of config register 1
    ADC0->SC1[0] |= ADC_SC1_ADCH(31); // configures the channel for the adc
    //enables the hardware average function and sets it in its fourth mode where it samples 32 times and makes the average
    ADC0->SC3 = ADC_SC3_AVGE_MASK | ADC_SC3_AVGS(3);
}

uint16 ADC_Values ()
{
    uint16 values = 0; //variable created to save adc read values
    ADC0->SC1[0] = 0x1 & ADC_SC1_ADCH_MASK; // configures the channel for the adc
    while (0 == (ADC0->SC1[0] & ADC_SC1_COCO_MASK))
        ; // comparison to see when the adc finished transmiting with its mask
    values = ADC0->R[0]; //assigns the read values to values
    return values;
}

uint16 convertRead ()
{
    return ((ADC_Values () * 0.00060566) / (.010)); //Convert the read value to the Degrees Scale (3.3V/2^12)/.010
}
