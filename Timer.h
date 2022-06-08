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

#include "std_types.h"
#include "CPU.h"
#include <avr/io.h>
#include "Register_Macros.h"

/*******************************************************************************
 *                          	  Type Declaration                             *
 *******************************************************************************/
typedef enum{
	OVERFLOW_MODE, CTC_MODE, FAST_PWM_MODE
}TIMER0_MODE;

typedef enum{
	DISABLE,TOGGLE, SET, CLEAR
}PIN_OPERATION;

typedef enum{
	NO_CLOCK, P0, P8, P64, P256, P1024
}CLOCK_SOURCE;

typedef enum{
	ENABLE_INTERRUPT, DISABLE_INTERRUPT
}TIMER0_INTERRUPT_STATE;


typedef struct{
	TIMER0_MODE 			mode;
	PIN_OPERATION 			pin_mode;
	CLOCK_SOURCE			clock_select;
	uint8 					starting_time;
	uint8 					compare_val;
	TIMER0_INTERRUPT_STATE	interrupt_select;
}TIMER0_CONFIGURATION;


/*******************************************************************************
 *                          Function Definitions                               *
 *******************************************************************************/

/* Description:
 *
 *
 */
void Timer0_init (TIMER0_CONFIGURATION *TIMER0_CONFIGURATION_PTR);

/* Description:
 *
 *
 */
void Timer0_start(void);

/* Description:
 *
 *
 */
uint8 Timer0_checkFlag(void);

/* Description:
 *
 *
 */
void Timer0_stop(void);

/* Description:
 *
 *
 */
void Timer0_deinit(void);

/* Description:
 *
 *
 */



void TIMER0_setCallBack(void(*a_ptr)(void));

#endif /* TIMER_H_ */
