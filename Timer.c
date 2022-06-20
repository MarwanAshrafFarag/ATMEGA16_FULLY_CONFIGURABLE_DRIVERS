/*
 * Timer.c
 *
 *  Created on: Jun 8, 2022
 *      Author: Marwan Ashraf Farag
 */

#include "Timer.h"

/*******************************************************************************
 *                               Global Variables                              *
 *******************************************************************************/

void (*g_callBackPtr)(void) = NULL_PTR;


/*******************************************************************************
 *                          Function Definitions                               *
 *******************************************************************************/

/* Description: Function to configure the use of TIMER0
 * Arguments: Pointer to the TIMER0_CONFIGURATION structure
 * Return: Function returns nothing
 */
void Timer0_init (TIMER0_CONFIGURATION *TIMER0_CONFIGURATION_PTR)
{
	/* RESETTING The control and interrupt bits before configuring */
	TCCR0 = 0;
	TIMSK = 0;

	/****************************************
	 *			NORMAL OVERFLOW MODE		*
	 ****************************************/
	/************************************************************************
	 * All Waveform Generation Mode bits are set to 0						*
	 * Setting Force output compare bit for non PWM modes					*
	 * This mode does not utilize OCx pin, so it should be always disabled	*
	 * This mode does not utilize the OCRx register							*
	 * Any configuration regarding output compare will be discarded			*
	 * Setting TOIE0 bit in case the configuration required the interrupt   *
	 ************************************************************************/
	if(TIMER0_CONFIGURATION_PTR->mode == OVERFLOW_MODE)
	{
		// Setting Waveform Generation Mode and Compare Output Mode bits
		TCCR0 |= TIMER0_CONFIGURATION_PTR->mode;
		// Interrupt configuration
		if (TIMER0_CONFIGURATION_PTR->interrupt_select == ENABLE_INTERRUPT)
			SET_BIT(TIMSK, TOIE0);
	}

	/****************************************
	 *		  PHASE CORRECT PWM MODE		*
	 ****************************************/
	/************************************************************************
	 * Waveform generation bits 00 and 02 are cleared while 01 is set		*
	 * Setting Force output compare bit for non PWM modes					*
	 * Configuring the operation of OC0A pin								*
	 * Loading the OCRx register with the required compare value			*
	 * Setting OCIE0A bit in case the configuration required the interrupt	*
	 ************************************************************************/
	else if(TIMER0_CONFIGURATION_PTR->mode == PWM_PHASE_CORRECT)
	{

	}

	/****************************************
	 *				CTC MODE				*
	 ****************************************/
	/************************************************************************
	 * Waveform generation bits 00 and 02 are cleared while 01 is set		*
	 * Setting Force output compare bit for non PWM modes					*
	 * Configuring the operation of OC0A pin								*
	 * Loading the OCRx register with the required compare value			*
	 * Setting OCIE0A bit in case the configuration required the interrupt	*
	 ************************************************************************/
	else if(TIMER0_CONFIGURATION_PTR->mode ==CTC_MODE)
	{
		// Setting Waveform Generation Mode and Compare Output Mode bits
		SET_BIT(TCCR0, WGM01);SET_BIT(TCCR0, FOC0);
		// Load the OCRx register with the compare ticks
		OCR0 = TIMER0_CONFIGURATION_PTR->compare_time;
		// Set the operation of OCx pin
		TCCR0|= TIMER0_CONFIGURATION_PTR->pin_mode;
		// Interrupt configuration
		if (TIMER0_CONFIGURATION_PTR->interrupt_select == ENABLE_INTERRUPT)
			SET_BIT(TIMSK, OCIE0);
	}

	/****************************************
	 *				PWM MODE				*
	 ****************************************/
	/************************************************************************
	 * Waveform generation bits 00 and 02 are cleared while 01 is set		*
	 * Setting Force output compare bit for non PWM modes					*
	 * Configuring the operation of OC0A pin								*
	 * Loading the OCRx register with the required compare value			*
	 * Setting OCIE0A bit in case the configuration required the interrupt	*
	 ************************************************************************/
	else if(TIMER0_CONFIGURATION_PTR->mode ==FAST_PWM_MODE)
	{
		SET_BIT(TCCR0, WGM00); SET_BIT(TCCR0, WGM01);
		if(TIMER0_CONFIGURATION_PTR->compare_time > 100)
			OCR0 = TIMER0_CONFIGURATION_PTR->compare_time;	// The Compare ticks

		else
			OCR0 = (uint8)(((255)*(TIMER0_CONFIGURATION_PTR->compare_time))/100);

		if (TIMER0_CONFIGURATION_PTR->interrupt_select == ENABLE_INTERRUPT)
			SET_BIT(TIMSK, OCIE0);
	}


	TCNT0 = TIMER0_CONFIGURATION_PTR->starting_ticks;	// The ticks at which the timer starts
	clk_holder = TIMER0_CONFIGURATION_PTR->clk;
}

/* Description:
 * Function to start the timer by setting the appropriate clock source
 * Returns nothing as it only sets the appropriate bits
 */
void Timer0_start()
{
		TCCR0 |= clk_holder;
}


/* Description:
 * Stops the timer by clearing the appropriate clock select bits
 *
 */
void Timer0_stop(void)
{
	TCCR0 &= ~(0x07);
}



/* Description:
 * Function to use in case of polling
 * Returns the status of the interrupt flag register
 */
uint8 Timer0_checkFlag(void)
{
	return TIFR;
}

/* Description:
 *Clears the interrupt flags by setting them to 1
 *
 */
void Timer0_clearFlag(void)
{
	TIFR= 0x07;
}

/* Description:
 *Sets the callback pointer to function
 *
 */
void TIMER0_setCallBack(void(*a_ptr)(void))
{
	g_callBackPtr = a_ptr;
}
