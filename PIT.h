/*
 * PIT.h
 *
 *  Created on: 16/08/2017
 *      Author: jlpe
 */

#ifndef PIT_H_
#define PIT_H_

#include "DataTypeDefinitions.h"

//the system clock of the Kinetis
#define SYSTEM_CLOCK 21000000

static uint8 PIT_INTR_FLAG = FALSE;

#define PIT_CLOCK_GATING 0x800000


/*! This enumerated constant are used to select the PIT to be used*/
typedef enum {PIT_0,PIT_1,PIT_2,PIT_3} PIT_Timer_t;

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function is to handle the PIT interrupts, it stops the clock for the
 	 interrupts, masks the flag value, resolves a bug with a useless variable and sets
 	 PIT_INTR_FLAG to TRUE.
 	 \return void
 */
void PIT_IRQHandler(void);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function configure the PIT to generate a delay base on the system clock.
 	 Internally it configures the clock gating and enables the PIT module.
 	 It is important to note that this strictly is not device driver since everything is
 	 contained in a single function, but in general you have to avoid this practices, this only
 	 for the propose of the homework

 	 \param[in]  pitTimer is the enumerated constant of PIT to be used.
 	 \param[in] systemClock is one of the required values to calculate the LDVAL trigger.
 	 \param[in] period one of the required values to calculate the LDVAL trigger.
 	 \return void
 */
void PIT_delay(PIT_Timer_t pitTimer,float systemClock ,float period);


/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function is to configure the clock gating which is used to save power when the
 	 device is off and activate to enable the clock bit (SIM->SCGC6).
 	 \return void
 */
void PIT_clockGating(void);

uint8 PIT_interruptFlagStatus(void);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function is to get the status flag of the PIT which is activated when PIT_IRQHandler
 	 is in use.
 	 \return PIT_INTR_FLAG;
 */
uint8 PIT_getIntrStutus(void);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function is to make the status flag of the interrupt value FALSE which we .
 	 activate in the PIT_IRQHandler.
 	  \param[in] pitTimer is the enumerated constant of PIT to be used.
 	 \return void
 */
void PIT_clear(PIT_Timer_t pitTimer);


#endif /* PIT_H_ */
