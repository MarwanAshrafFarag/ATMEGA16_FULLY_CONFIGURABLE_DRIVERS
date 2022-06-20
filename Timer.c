/*
 * Name:Timer.c
 *
 *  Created on: Jun 8, 2022
 *      Author: Marwan Ashraf Farag
 */

#include "Timer.h"

/*******************************************************************************
 *                               Global Variables                              *
 *******************************************************************************/

						/*NO GLOBAL VARIABLES DECLARED*/

/*******************************************************************************
 *                          Function Definitions                               *
 *******************************************************************************/

/* **********************************************************
 * Description: Function to configure the use of TIMER0 	*
 * Arguments: Pointer to the TIMER0_CONFIGURATION structure *
 * Return: Function returns nothing							*
 ************************************************************/
void Timer0_init (TIMER0_CONFIGURATION *TIMER0_CONFIGURATION_PTR)
{
	/* RESETTING The control and interrupt bits before configuring */
	TCCR0 = 0;
	TIMSK = 0;

	/* Setting the appropriate bits in the timer control registers */
	TCCR0 |= TIMER0_CONFIGURATION_PTR->mode;

	/*Loading TCNT0 with the starting tick*/
	TCNT0 = TIMER0_CONFIGURATION_PTR->starting_ticks;

	/*Saving the clock select value in its holder*/
	clk_holder = TIMER0_CONFIGURATION_PTR->clk;


	/****************************************
	 *			NORMAL OVERFLOW MODE		*
	 ****************************************/
	/************************************************************************
	 * All Waveform Generation Mode bits are set to 0						*
	 * Setting Force output compare bit for non PWM modes					*
	 * These bits are saved in its enumeration value 0x80					*
	 * This mode does not utilize OCx pin or OCRx register					*
	 * Any configuration regarding output compare will be discarded			*
	 * Setting TOIE0 bit in case the configuration required the interrupt   *
	 ************************************************************************/
	if(TIMER0_CONFIGURATION_PTR->mode == OVERFLOW)
	{
		// Interrupt configuration
		if (TIMER0_CONFIGURATION_PTR->interrupt_select == ENABLE_INTERRUPT)
			SET_BIT(TIMSK, TOIE0);
	}


	/****************************************
	 *				CTC MODE				*
	 ****************************************/
	/************************************************************************
	 * Waveform generation bit 00 is cleared while 01 is set				*
	 * Setting Force output compare bit for non PWM modes					*
	 * These bits are saved in its enumeration value 0x88					*
	 * Configuring the operation of OC0A pin is required for this mode		*
	 * Loading the OCRx register with the required compare value			*
	 * Setting OCIE0A bit in case the configuration required the interrupt	*
	 ************************************************************************/
	else if(TIMER0_CONFIGURATION_PTR->mode ==CTC)
	{

		/* Load the OCRx register with the compare ticks*/
		OCR0 = TIMER0_CONFIGURATION_PTR->compare_time;
		/* Set the operation of OCx pin*/
		TCCR0|= TIMER0_CONFIGURATION_PTR->pin_mode;
		/* Interrupt configuration */
		if (TIMER0_CONFIGURATION_PTR->interrupt_select == ENABLE_INTERRUPT)
			SET_BIT(TIMSK, OCIE0);
	}

	/****************************************
	 *				PWM MODE				*
	 ****************************************/
	/************************************************************************
	 * Waveform generation bits 00 is set									*
	 * Waveform generation bits 01 is clear in phase correct mode			*
	 * Waveform generation bits 01 is set in fast PWM mode					*
	 * CLEARING Force output compare bit for PWM modes						*
	 * These bits are saved in the enumeration values 0x48 and 0x40			*
	 * Configuring the operation of OC0A pin								*
	 * Compare time in the config. structure is replaced with duty cycle	*
	 * The duty cycle equation is calculated based on inversion of OCx		*
	 * Setting OCIE0A bit in case the configuration required the interrupt	*
	 ************************************************************************/

	else if(TIMER0_CONFIGURATION_PTR->mode == FAST_PWM || TIMER0_CONFIGURATION_PTR->mode == PWM_PHASE_CORRECT )
	{

		/* Return from the function if duty cycle specified is larger than 100%
		 * This condition is to be edited later
		 * The goal is to prevent the compilation of this program
		 */
		if(TIMER0_CONFIGURATION_PTR->compare_time > 100)
			return;

		/*Checking the inversion of the mode*/
		switch(TIMER0_CONFIGURATION_PTR->pin_mode)
		{
			case DISABLE: 	// If OCx is disabled
				break;		// Disconnected by default so do nothing

			case TOGGLE:	// Toggle is reserved
				break;		// return the default action of disabling the pin, this is to be edited later with the goal of creating a compiler error

			case CLEAR:		// non inverting, duty cycle  as it is
				OCR0 = (uint8)(((255)*(TIMER0_CONFIGURATION_PTR->compare_time))/100);
				break;

			case SET:		// inverting, duty cycle is 1- the input
				OCR0 = (uint8)((255)*(1-((TIMER0_CONFIGURATION_PTR->compare_time)/100)));
				break;
		}

		/* Interrupt configuration */
		if (TIMER0_CONFIGURATION_PTR->interrupt_select == ENABLE_INTERRUPT)
			SET_BIT(TIMSK, OCIE0);
	}
}
/**********************  END OF INITIALIZATION FUNCTION  **********************/



/* **********************************************************
 * Description: Set the clock source to start the timer	*
 * Arguments: VOID											*
 * Return: Function returns nothing							*
 ************************************************************/
void Timer0_start(void)
{
		TCCR0 |= clk_holder;
}


/* **********************************************************
 * Description: Clear the clock source to stop the timer	*
 * Arguments: VOID											*
 * Return: Function returns nothing							*
 ************************************************************/
void Timer0_stop(void)
{
	TCCR0 &= ~(0x07);
}


/* **********************************************************
 * Description: Check the flag to use in polling			*
 * Arguments: VOID											*
 * Return: Function returns the status of the flag register	*
 ************************************************************/
uint8 Timer0_checkFlag(void)
{
	return TIFR;
}

/* **********************************************************
 * Description: clears the interrupt flag manually			*
 * Arguments: VOID											*
 * Return: Function returns nothing							*
 ************************************************************/
void Timer0_clearFlag(void)
{
	TIFR= 0x03;
}


/*******************************************************************************
 *     END OF THE IMPLEMENTATION OF CONFIGURABLE ATMEGA16 TIMER0               *
 *******************************************************************************/
