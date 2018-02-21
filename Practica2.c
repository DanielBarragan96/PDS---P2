/*
 * Copyright (c) 2017, NXP Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file    Practica2.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK64F12.h"
#include "fsl_pit.h"
#include "fsl_adc16.h"
#include "ADC.h"
#include "FIFO.h"
#include "PIT.h"
#include "DAC.h"
#include "fsl_dac.h"

//the system clock of the Kinetis
#define SYSTEM_CLOCK CLOCK_GetBusClkFreq()
//period for the pit to get 1 second
#define PERIOD 1/41000.00
//pit number to count
#define LDVAL_trigger  (SYSTEM_CLOCK * PERIOD)/20

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

uint8_t contador=0;
int8_t conv[7] = {0};

adc16_config_t adc16ConfigStruct;
adc16_channel_config_t adc16ChannelConfigStruct;
ADC_Type *base = ADC0;
uint32_t channelGroup = 0;
dac_config_t dacConfigStruct;

void PIT0_IRQHandler ()
{
    PIT_ClearStatusFlags (PIT, kPIT_Chnl_0, kPIT_TimerFlag);

    sint8 read = (sint8) ADC_Values();
    for(contador;contador<7;contador++){
    	conv[contador] = read*h1[contador];

        DACFunction(PIT_0, (uint8) conv[contador]);
    }
    contador=0;
    //printf(" %d\n",read);
    //push (read);

    PIT_SetTimerPeriod (PIT, kPIT_Chnl_0, LDVAL_trigger);
    PIT_StartTimer (PIT, kPIT_Chnl_0);
}

int main (void)
{
    /* Init board hardware. */
    BOARD_InitBootPins ();
    BOARD_InitBootClocks ();
    BOARD_InitBootPeripherals ();
    /* Init FSL debug console. */
    BOARD_InitDebugConsole ();

    adc16ChannelConfigStruct.channelNumber = 31;
    adc16ChannelConfigStruct.enableDifferentialConversion = true;
    adc16ChannelConfigStruct.enableInterruptOnConversionCompleted = false;

    CLOCK_EnableClock (kCLOCK_PortE);

    ADC_init();
    initDAC();

    pit_config_t pit_config =  { true };
    PIT_Init (PIT, &pit_config);
    PIT_EnableInterrupts (PIT, kPIT_Chnl_0, kPIT_TimerInterruptEnable);
    EnableIRQ (PIT0_IRQn);

    PIT_SetTimerPeriod (PIT, kPIT_Chnl_0, LDVAL_trigger);
    PIT_StartTimer (PIT, kPIT_Chnl_0);

//    Configures the DAC.
//    DAC_GetDefaultConfig(&dacConfigStruct);
//    DAC_Init(DAC0, &dacConfigStruct);
//    DAC_Enable(DAC0, true);
//    DAC_SetBufferReadPointer(DAC0, 0U);

    while (1)
    {

    }
    return 0;
}
