/*
 * GPIO.c
 *
 *  Created on: Jun 8, 2022
 *      Author: Marwan Ashraf Farag
 */


#include "GPIO.h"

/*
 * Description :
 * Set the direction of the given port input/output.
 * If the input port number is invalid, The function terminates.
 */

void GPIO_SET_PORT_DIRECTION(uint8 port_num, uint8 port_dir){

	if (port_num < MAX_PORT_NUM)
	{
		switch (port_num)
		{

		case PORTB_ID:
			DDRB = port_dir;
			break;

		case PORTC_ID:
			DDRC = port_dir;
			break;

		case PORTD_ID:
			DDRD = port_dir;
			break;

		}
	}

	else{

		/*terminate the function*/

		}
}


/*
 * Description :
 * Write the given value to a port  HIGH/LOW.
 * If the input port number is invalid, The function terminates.
 */

void GPIO_PORT_WRITE(uint8 port_num, uint8 value){

	if (port_num < MAX_PORT_NUM)
	{
		switch (port_num)
		{

		case PORTB_ID:
			PORTB = value;
			break;

		case PORTC_ID:
			PORTC = value;
			break;

		case PORTD_ID:
			PORTD = value;
			break;
		}
	}

	else{
			/* terminate the function */
		}
}


/*
 * Description :
 * Returns the value of the required port input/output.
 * If the input port number is invalid, The function returns 0.
 */

uint8 GPIO_PORT_READ(uint8 port_num)
{

	if (port_num < MAX_PORT_NUM)
	{
		switch (port_num)
		{

		case PORTB_ID:
			return PINB;

		case PORTC_ID:
			return PINC;

		case PORTD_ID:
			return PIND;
		}

	}
	else
	{
		/*DO NOTHING*/
	}
	return 0;
}


/*
 * Description :
 * Setup the direction of the required pin input/output.
 * If the input port number or pin number are not correct, the function terminates.
 */

void GPIO_SET_PIN_DIRECTION(uint8 port_num, uint8 pin_num, uint8 pin_dir){

	if(port_num < MAX_PORT_NUM &&  pin_num < MAX_PIN_NUM)
	{
		switch (port_num)
		{

		case PORTB_ID:
			if (pin_dir == PIN_INPUT)
				CLEAR_BIT(DDRB, pin_num);
			else
				SET_BIT(DDRB,pin_num);
			break;

		case PORTC_ID:
			if (pin_dir == PIN_INPUT)
			{
				CLEAR_BIT(DDRC,pin_num);
			}
			else
			{
				SET_BIT(DDRC,pin_num);
			}
			break;

		case PORTD_ID:
			if (pin_dir == PIN_INPUT)
			{
				CLEAR_BIT(DDRD,pin_num);
			}
			else
			{
				SET_BIT(DDRD,pin_num);
			}
			break;
		}
	}
	else
	{
		/*Terminate*/
	}
}

/*
 * Description :
 * Write a given value (HIGH or LOW) to a certain pin
 * If the input port number or pin number are not correct, The function terminates.
 * If the pin is input, this function will enable/disable the internal pull-up resistor.
 *
 */

void GPIO_PIN_WRITE(uint8 port_num, uint8 pin_num, uint8 value){

	if (port_num < MAX_PORT_NUM && pin_num < MAX_PIN_NUM)
	{
			switch (port_num)
			{

			case PORTB_ID:
				if (value == 1)
					SET_BIT(PORTB,pin_num);

				else if (value == 0)
					CLEAR_BIT(PORTB,pin_num);

				break;

			case PORTC_ID:
				if (value == 1)
					SET_BIT(PORTC,pin_num);

				else if (value == 0)
					CLEAR_BIT(PORTC,pin_num);

				break;

			case PORTD_ID:
				if (value == 1)
					SET_BIT(PORTD,pin_num);

				else if (value == 0)
					CLEAR_BIT(PORTD,pin_num);

				break;
			}
		}
		else
		{
			/* Do Nothing */
		}
}

/*
 * Description :
 * Returns the value for the required pin, it should be Logic High or Logic Low.
 * If the input port number or pin number are not correct, The function will return Logic Low.
 */

uint8 GPIO_PIN_READ(uint8 port_num, uint8 pin_num){

	if (port_num < MAX_PORT_NUM && pin_num < MAX_PIN_NUM)
	{
		switch (port_num)
		{

		case PORTB_ID:
			return BIT_IS_SET(PINB, pin_num);

		case PORTC_ID:
			return BIT_IS_SET(PINC, pin_num);

		case PORTD_ID:
			return BIT_IS_SET(PIND, pin_num);
		}
	}

	else
	{
		/*do nothing*/
	}

	return 0;

}













