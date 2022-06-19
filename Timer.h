/*
 * Timer.h
 *
 *  Created on: Jun 8, 2022
 *      Author: Marwan Ashraf Farag
 */

#ifndef TIMER_H_
#define TIMER_H_

/*******************************************************************************
 *                          	   File Inclusions                             *
 *******************************************************************************/


#include "CPU.h"


/*******************************************************************************
 *                          	  Type Declaration                             *
 *******************************************************************************/

/**TIMER MODES**/
typedef enum{
	OVERFLOW_MODE, CTC_MODE, FAST_PWM_MODE
}TIMER0_MODE;



/**Behavior of OCR0A PIN**/
typedef enum{
	DISABLE, TOGGLE= 0x40, CLEAR=0x80, SET=0xC0
}PIN_OPERATION;



/**CLOCK SOURCE**/
typedef enum{
	 P1=1 , P8, P64, P256, P1024, EXTERNAL_FALLING, EXTERNAL_RISING
}CLOCK_SOURCE;



/**Choose weather to enable or disable the use of ISR**/
typedef enum{
	DISABLE_INTERRUPT, ENABLE_INTERRUPT
}TIMER0_INTERRUPT_STATE;




/**Configuration structure for TIMER0A**/

typedef struct{
	TIMER0_MODE 			mode;
	PIN_OPERATION 			pin_mode;
	uint8 					starting_ticks;
	uint8 					compare_time;	/* This member is used to hold the duty cycle during FAST_PWM_MODE*/
	CLOCK_SOURCE			clk;
	TIMER0_INTERRUPT_STATE	interrupt_select;
}TIMER0_CONFIGURATION;

/*******************************************************************************
 *                            Variable Declaration                             *
 ******************************************************************************/

static volatile CLOCK_SOURCE clk_holder = 0;

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
void Timer0_init (TIMER0_CONFIGURATION *TIMER0_CONFIGURATION_PTR);

/* Description:
 *Function to start the timer by setting the appropriate clock source
 *Returns nothing as it only sets the appropriate bits
 */

void Timer0_start();
/* Description:
 * Function to use in case of polling
 * Returns the status of the interrupt flag register
 */
uint8 Timer0_checkFlag(void);

/* Description:
 *Clears the interrupt flags by setting them to 1
 *
 */
void Timer0_clearFlag(void);

/* Description:
 * Stops the timer by clearing the appropriate clock select bits
 *
 */
void Timer0_stop(void);

/* Description:
 *Sets the callback pointer to function
 *
 */
void TIMER0_setCallBack(void(*a_ptr)(void));

#endif /* TIMER_H_ */
