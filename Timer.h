/* Module: ATMEGA 16 Timers
 * File: Timer.h
 * Description: Header file for declaring the function used in the driver
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
	OVERFLOW=0x80, PWM_PHASE_CORRECT=0x40, CTC=0x88, FAST_PWM=0x48
}TIMER0_MODE;



/**Behavior of OCR0A PIN**/
typedef enum{
	DISABLE, TOGGLE= 0x10, CLEAR=0x20, SET=0x30
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

/* **********************************************************
 * Description: Function to configure the use of TIMER0 	*
 * Arguments: Pointer to the TIMER0_CONFIGURATION structure *
 * Return: Function returns nothing							*
 ************************************************************/
void Timer0_init (TIMER0_CONFIGURATION *TIMER0_CONFIGURATION_PTR);


/* **********************************************************
 * Description: Set the clock source to start the timer	*
 * Arguments: VOID											*
 * Return: Function returns nothing							*
 ************************************************************/
void Timer0_start();


/* **********************************************************
 * Description: Clear the clock source to stop the timer	*
 * Arguments: VOID											*
 * Return: Function returns nothing							*
 ************************************************************/
void Timer0_stop(void);


/* **********************************************************
 * Description: Check the flag to use in polling			*
 * Arguments: VOID											*
 * Return: Function returns the status of the flag register	*
 ************************************************************/
uint8 Timer0_checkFlag(void);


/* **********************************************************
 * Description: clears the interrupt flag manually			*
 * Arguments: VOID											*
 * Return: Function returns nothing							*
 ************************************************************/
void Timer0_clearFlag(void);


#endif /* TIMER_H_ */
