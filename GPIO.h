/*
 * GPIO.h
 *
 *  Created on: Jun 8, 2022
 *      Author: Marwan Ashraf Farag
 */

#ifndef GPIO_H_
#define GPIO_H_

/***********************************************************************************
*						      	File Inclusions							      	   *
***********************************************************************************/

#include "std_types.h"
#include <avr/io.h>
#include "Register_Macros.h"

/***********************************************************************************
*						     	   	Definitions								       *
***********************************************************************************/

#define MAX_PORT_NUM 3   // PORTB, PORTC and PORTD
#define MAX_PIN_NUM 8    //8 pins numbered from 0 to 7

#define PORTB_ID               1
#define PORTC_ID               2
#define PORTD_ID               3

#define PIN0_ID                0
#define PIN1_ID                1
#define PIN2_ID                2
#define PIN3_ID                3
#define PIN4_ID                4
#define PIN5_ID                5
#define PIN6_ID                6
#define PIN7_ID                7

/***********************************************************************************
*						    	Types Declaration							       *
***********************************************************************************/

typedef enum{
	PIN_INPUT, PIN_OUTPUT
}GPIO_PIN_DIRECTION;

typedef enum{
	PORT_INPUT, PORT_OUTPUT=0xFF
}GPIO_PORT_DIRECTION;

/***********************************************************************************
*						    	Functions Declaration							       *
***********************************************************************************/

/*
 * Description :
 * Set the direction of the given port input/output.
 * If the input port number is invalid, The function terminates.
 */

void GPIO_SET_PORT_DIRECTION(uint8 port_num, uint8 port_dir);

/*
 * Description :
 * Write the given value to a port  HIGH/LOW.
 * If the input port number is invalid, The function terminates.
 */

void GPIO_PORT_WRITE(uint8 port_num, uint8 value);

/*
 * Description :
 * Returns the value of the required port input/output.
 * If the input port number is invalid, The function returns 0.
 */

uint8 GPIO_PORT_READ(uint8 port_num);

/*
 * Description :
 * Setup the direction of the required pin input/output.
 * If the input port number or pin number are not correct, the function terminates.
 */

void GPIO_SET_PIN_DIRECTION(uint8 port_num, uint8 pin_num, uint8 pin_dir);

/*
 * Description :
 * Write a given value (HIGH or LOW) to a certain pin
 * If the input port number or pin number are not correct, The function terminates.
 * If the pin is input, this function will enable/disable the internal pull-up resistor.
 *
 */

void GPIO_PIN_WRITE(uint8 port_num, uint8 pin_num, uint8 value);

/*
 * Description :
 * Returns the value for the required pin, it should be Logic High or Logic Low.
 * If the input port number or pin number are not correct, The function will return Logic Low.
 */

uint8 GPIO_PIN_READ(uint8 port_num, uint8 pin_num);



#endif /* GPIO_H_ */
