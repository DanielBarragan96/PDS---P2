

#include "DataTypeDefinitions.h"
#include "MK64F12.h"
#include "PIT.h"

#ifndef DAC_H_
#define DAC_H_

#define DAC_SIM 0x1000U

void DACFunction(PIT_Timer_t pitIn, uint16 actualVal);

uint16 getIndex();

void initDAC();

#endif
