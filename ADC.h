#ifndef ADC_H_
#define ADC_H_

#include "DataTypeDefinitions.h"

//To select low or normal power
typedef enum{
    NORMAL_POWER,
    LOW_POWER
}ADC_CFG1_DLPC;

//To select clk mode
typedef enum{
    CLOCK1,
    CLOCK2,
    CLOCK4,
    CLOCK8
}ADC_CFG1_ADIV;

//Type of sample time
typedef enum{
    S_SHORT,
    S_LONG
}ADC_CFG1_ADLSMP;

//to select bit mode
typedef enum{
    ADC_8Bits,
    ADC_12Bits,
    ADC_10Bits,
    ADC_16Bits
}ADC_CFG1_MODE;

//to select the clk
typedef enum{
    BUS_CLOCK,
    AT_CLOCK_2,
    AT_CLOCK,
    AS_CLOCK
}ADC_CFG1_ADICLK;

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
     \brief Parametric select of the adc configuration of the SC1 and setup of the high sample rate and a hardware sampling enable and mode
     \param[in]  power selects between normal and low power mode.
     \param[in]  div selects the value the clk will be divided by.
     \param[in]  sample selects between a short or long sample time.
     \param[in]  mode selects between the different adc bitmodes ranges from 8 to 16.
     \param[in]  clk selects which clk will be used
     \return void
 */
void ADC_init();
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
     \brief  This function converts values the adc is reading and saves it on a 16 bit variable when the transmision stops.
     \return the values the adc read.
 */
uint16 ADC_Values();
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
     \brief  This function converts values the adc read and converts them into degrees.
     \return the values the adc read.
 */
uint16 convertRead();

#endif /* ADC_H_ */
