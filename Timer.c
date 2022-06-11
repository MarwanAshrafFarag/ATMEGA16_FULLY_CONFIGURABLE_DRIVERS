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
 * Function to configure the use of TIMER0A
 * Its argument is pointer to the configuration structure that has 5 members
 * the function returns nothing
 * It only sets the appropriate bits in the timer registers based on the user configurations
 *  Function doesnt start the timer
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
			TIMSK0= 0x01;
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
			TIMSK0= 0x02;
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
			TIMSK0= 0x02;
	}

}

/* Description:
 * Function to start the timer by setting the appropriate clock source
 * Returns nothing as it only sets the appropriate bits
 */
void Timer0_start(CLOCK_SOURCE clk)
{

			TCCR0B |= clk;

}

/* Description:
 * Stops the timer by clearing the appropriate clock select bits
 *
 */
void Timer0_stop(void)
{
	TCCR0B &= ~(0x07);
}



/* Description:
 * Function to use in case of polling
 * Returns the status of the interrupt flag register
 */
uint8 Timer0_checkFlag(void)
{
	return TIFR0;
}

/* Description:
 *Clears the interrupt flags by setting them to 1
 *
 */
void Timer0_clearFlag(void)
{
	TIFR0= 0x07;
}

/* Description:
 *Sets the callback pointer to function
 *
 */
void TIMER0_setCallBack(void(*a_ptr)(void))
{
	g_callBackPtr = a_ptr;
}
