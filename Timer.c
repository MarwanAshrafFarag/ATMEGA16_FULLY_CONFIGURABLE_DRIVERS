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

/* Description:
 *
 *
 */
void Timer0_init (TIMER0_CONFIGURATION *TIMER0_CONFIGURATION_PTR)
{

	/****************************************
	 *			NORMAL OVERFLOW MODE		*
	 ****************************************/

	if(TIMER0_CONFIGURATION_PTR->mode == OVERFLOW_MODE)
	{
		TCCR0A = 0;
		TCCR0B = 0;
		TCNT0 = TIMER0_CONFIGURATION_PTR->starting_ticks;

		if (TIMER0_CONFIGURATION_PTR->interrupt_select == ENABLE_INTERRUPT)
			TIMSK0= ENABLE_INTERRUPT;
	}

	/****************************************
	 *				CTC MODE				*
	 ****************************************/

	else if(TIMER0_CONFIGURATION_PTR->mode ==CTC_MODE)
	{

		// RESETTING CONTROL REGISTERS
		TCCR0A=0;
		TCCR0B = 0;

		SET_BIT(TCCR0A, WGM01);							// SET WAVEFORM GENERATION TO CTC MDOE
		TCCR0A|= TIMER0_CONFIGURATION_PTR->pin_mode; 	// SET OCR0A BEHAVIOR
		SET_BIT(TCCR0B, FOC0A);							// SETTING FOC0A DURING NON PWM MODE

		TCNT0 = TIMER0_CONFIGURATION_PTR->starting_ticks;
		OCR0A = TIMER0_CONFIGURATION_PTR->compare_time;

		if (TIMER0_CONFIGURATION_PTR->interrupt_select == ENABLE_INTERRUPT)
			TIMSK0= ENABLE_INTERRUPT;
	}

	/****************************************
	 *				PWM MODE				*
	 ****************************************/

	else if(TIMER0_CONFIGURATION_PTR->mode ==FAST_PWM_MODE)
	{
		TCCR0A=0;
		TCCR0B=0;

		SET_BIT(TCCR0A, WGM00); SET_BIT(TCCR0A, WGM01); SET_BIT(TCCR0B, WGM02);

		TCCR0A|= TIMER0_CONFIGURATION_PTR->pin_mode; // OCR0A pin mode

		TCNT0 = TIMER0_CONFIGURATION_PTR->starting_ticks;
		OCR0A = TIMER0_CONFIGURATION_PTR->compare_time;
		if (TIMER0_CONFIGURATION_PTR->interrupt_select == ENABLE_INTERRUPT)
			TIMSK0= ENABLE_INTERRUPT;
	}

}

/* Description:
 *
 *
 */
void Timer0_start(CLOCK_SOURCE clk)
{

			TCCR0B |= clk;

}
