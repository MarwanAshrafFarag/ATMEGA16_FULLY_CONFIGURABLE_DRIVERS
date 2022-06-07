 /******************************************************************************
 *
 * Module: Non...
 *
 * File Name: Register_Macros.h
 *
 * Description: Needed macros for quick register operations
 *
 *******************************************************************************/

#ifndef REGISTER_MACROS_H_
#define REGISTER_MACROS_H_

#define SET_BIT(REG,BIT) (REG|=(1<<BIT))				// Setting the specified bit in any register

#define CLEAR_BIT(REG,BIT) (REG&=(~(1<<BIT)))			// Clearing the specified bit in any register

#define TOGGLE_BIT(REG,BIT) (REG^=(1<<BIT))				// Toggling the specified bit in any register

#define BIT_IS_SET(REG,BIT) ( REG & (1<<BIT) )			// "returns" 1 or true if the bit is set

#define BIT_IS_CLEAR(REG,BIT) ( !(REG & (1<<BIT)) )		// "returns" 1 or true if the bit is clear

#endif
