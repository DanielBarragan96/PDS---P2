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

//the system clock of the Kinetis
#define SYSTEM_CLOCK CLOCK_GetBusClkFreq()
//period for the pit to get 1 second
#define PERIOD 1/41000.00
//pit number to count
#define LDVAL_trigger  (SYSTEM_CLOCK * PERIOD)

adc16_config_t adc16ConfigStruct;
adc16_channel_config_t adc16ChannelConfigStruct;
ADC_Type *base = ADC0;
uint32_t channelGroup = 0;

void PIT0_IRQHandler ()
{
    PIT_ClearStatusFlags (PIT, kPIT_Chnl_0, kPIT_TimerFlag);

    uint32_t read = ADC16_GetChannelConversionValue(base, channelGroup);
    printf(" %d\n",read);

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

    // Input pin PORT configuration P-833 SDK
    const port_pin_config_t config =
            {
                kPORT_PullDisable,
                kPORT_FastSlewRate,
                kPORT_PassiveFilterDisable,
                kPORT_OpenDrainDisable,
                kPORT_LowDriveStrength,
                kPORT_MuxAsGpio,
                kPORT_UnlockRegister,
            };

    PORT_SetPinConfig(PORTE, 2, &config);//BLUE

    pit_config_t pit_config =  { true };
    PIT_Init (PIT, &pit_config);
    PIT_EnableInterrupts (PIT, kPIT_Chnl_0, kPIT_TimerInterruptEnable);
    EnableIRQ (PIT0_IRQn);

    ADC16_GetDefaultConfig (&adc16ConfigStruct);
    ADC16_Init (ADC0, &adc16ConfigStruct);
    ADC16_SetChannelConfig (ADC0, 1, &adc16ChannelConfigStruct); //PTE2 ADC0_DP2

    PIT_SetTimerPeriod (PIT, kPIT_Chnl_0, LDVAL_trigger);
    PIT_StartTimer (PIT, kPIT_Chnl_0);

    while (1)
    {

    }
    return 0;
}
