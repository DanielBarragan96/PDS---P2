/**
 \file FIFO.h
 \brief
 This is the header file for using a FIFO with the UART.
 \author Daniel Barragán
 \date	05/11/2017
 */
#ifndef FIFO_H_
#define FIFO_H_

#define FIFO_LENGHT 7//limit size of FIFO
#define ENTER 13 //ENTER key value
#define SPACE 32 //ENTER key value
#define FIRST_ELEMENT 0//The first element of the FIFO is in the index 0

#include "DataTypeDefinitions.h"

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 \brief	 This function deletes the first value IN.
 \return If it was possible to eliminate the first value return TRUE, else return FALSE
 */
sint8 pop ();
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 \brief	 This function add a new value to the FIFO.
 \param[in]  newVal will be added to the FIFO.
 \return If it was possible to add the value return TRUE, else return FALSE
 */
BooleanType push (sint8 newVal);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 \brief	 This is the function sends the current FIFO (first element) direction.
 \return sint8* the direction of the FIFO
 */
sint8* getFIFO ();
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 \brief	 This is the function clears the FIFO for new FIFOs
 \return If it was possible to eliminate the FIFO values return TRUE, else return FALSE
 */
BooleanType clearFIFO ();
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 \brief	 This is the function returns the sizze of the FIFO.
 \return the size of the FIFO.
 */
sint8 getFIFOIndex ();

#endif /* FIFO_H_ */

