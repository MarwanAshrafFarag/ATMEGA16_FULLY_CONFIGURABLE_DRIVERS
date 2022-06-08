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


void Timer0_init (TIMER0_CONFIGURATION *TIMER0_CONFIGURATION_PTR){

	if(TIMER0_CONFIGURATION_PTR->mode == OVERFLOW_MODE)
	{
		TCCR0A = 0;
		TCCR0B = 0;
		TCNT0 = TIMER0_CONFIGURATION_PTR->starting_ticks;

		if (TIMER0_CONFIGURATION_PTR->interrupt_select == ENABLE_INTERRUPT)
			TIMSK0= ENABLE_INTERRUPT;
	}

	else if(TIMER0_CONFIGURATION_PTR->mode ==CTC_MODE)
	{
		TCCR0A=0;
		SET_BIT(TCCR0A, WGM01);

		switch(TIMER0_CONFIGURATION_PTR->pin_mode)
		{
		case DISABLE:
			/* Do nothing as COM0A1,2 are already 0*/
			break;

		case TOGGLE:
			SET_BIT(TCCR0A, COM0A0);
			break;

		case CLEAR:
			SET_BIT(TCCR0A, COM0A1);
			break;

		case SET:
			SET_BIT(TCCR0A, COM0A0); SET_BIT(TCCR0A, COM0A1);
			break;
		}

		TCCR0B = 0;
		SET_BIT(TCCR0B, FOC0A);
		TCNT0 = TIMER0_CONFIGURATION_PTR->starting_ticks;
		OCR0A = TIMER0_CONFIGURATION_PTR->compare_time;
	}

	else if(TIMER0_CONFIGURATION_PTR->mode ==FAST_PWM_MODE)
	{

	}

	TCCR0B = TIMER0_CONFIGURATION_PTR->clock_select; /* Start the timer using the clock configuration*/
}
