/*
 * PIT.h
 *
 *  Created on: Jan 29, 2015
 *      Author: Luis Pizano
 *  Edited on: Feb 28, 2019
 *      Editors: Andrea Perez & Alvaro A. Rocha Robles.
 */

#ifndef PIT_H_
#define PIT_H_

#include "stdint.h"
#include "MK64F12.h"

typedef float PIT_float_t;

/*! This enumerated constant are used to select the PIT to be used*/
typedef enum {PIT_0,PIT_1,PIT_2,PIT_3} PIT_timer_t;


/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/

void PIT1_callback_update(void (*handler)(void));
void PIT2_callback_update(void (*handler)(uint8_t));

/*!
 	 \brief This function handles an interrupt event in the PIT.CHANNEL[0]
 	 \param[in] void.
 	 \return void.
 */
void PIT0_IRQHandler(void);

/*!
 	 \brief This function handles an interrupt event in the PIT.CHANNEL[1]
 	 \param[in] void.
 	 \return void.
 */
void PIT1_IRQHandler();

/*!
 	 \brief	 This function configure the PIT to generate a delay base on the system clock.
 	 It is important to note that this strictly is not device driver since everything is
 	 contained in a single function,  in general you have to avoid this practices, this only
 	 for the propose of the homework
 	 \param[in]  pit_timer channel to be used.
	 \param[in]  system_clock system clock use in the K64 (defult = 21e6).
	 \param[in]  delay the amount of time the delay the microcontroller
 	 \return void
 */
void PIT_delay(PIT_timer_t pit_timer, PIT_float_t system_clock , PIT_float_t delay);

/********************************************************************************************/
/*!
 	 \brief	 This function enable the clock signal of the pit
 	 \param[in]  void.
 	 \return void
 */
void PIT_clock_gating(void);

/********************************************************************************************/
/*!
 	 \brief	It return the status of the interrupt flag. This flag is a variable created by the programmer.
 	 It is not the flag related with bit TIF in PIT->CHANNEL[0].TFLG |= PIT_TFLG_TIF_MASK;
 	 \param[in]  void.
 	 \return uint8_t flag status
 */
uint8_t PIT_get_interrupt_flag_status(PIT_timer_t pit);

/********************************************************************************************/
/*!
 	 \brief	It return clears the interrupt flag. This flag is a variable created by the programmer.
 	 It is not the flag related with bit TIF in PIT->CHANNEL[0].TFLG |= PIT_TFLG_TIF_MASK;
 	 \param[in]  void.
 	 \return uint8_t flag status
 */
void PIT_clear_interrupt_flag(PIT_timer_t pit);

/********************************************************************************************/
/*!
 	 \brief	It Enables the PIT module.
 	 \param[in]  void.
 	 \return uint8_t flag status
 */
void PIT_enable(void);

/********************************************************************************************/
void PIT_enable_interrupt(PIT_timer_t pit);
void PIT_disable_interrupt(PIT_timer_t pit);

/*Disables timer*/
void PIT_stop(PIT_timer_t pit);

#endif /* PIT_H_ */
