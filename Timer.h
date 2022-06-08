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
	DISABLE, TOGGLE, CLEAR, SET
}PIN_OPERATION;

typedef enum{
	NO_CLOCK, P1 , P8, P64, P256, P1024, EXTERNAL_FALLING, EXTERNAL_RISING
}CLOCK_SOURCE;

typedef enum{
	DISABLE_INTERRUPT, ENABLE_INTERRUPT
}TIMER0_INTERRUPT_STATE;


typedef struct{
	TIMER0_MODE 			mode;
	PIN_OPERATION 			pin_mode;
	CLOCK_SOURCE			clock_select;
	uint8 					starting_ticks;
	uint8 					compare_time;
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
uint8 Timer0_checkFlag(void);


/* Description:
 *
 *
 */
void Timer0_clearFlag(void);

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
