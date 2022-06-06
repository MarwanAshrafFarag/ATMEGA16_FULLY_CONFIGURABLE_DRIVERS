/*
 * CPU.h
 *
 *  Created on: Jun 6, 2022
 *      Author: bulls
 */

#ifndef CPU_H_
#define CPU_H_

#include <avr/io.h>		/* Include AVR std. library file */
#include <avr/interrupt.h>
#include <util/delay.h>		/* Include Delay header file */

#ifdef F_CPU
#undef F_CPU
#define F_CPU 16000000UL
//#define __OPTIMIZE__

#endif /* F_CPU */

#endif /* CPU_H_ */
