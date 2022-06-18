

#include "Timer.h"

//#define OVERFLOW_MODE_INTERRUPT_DISABLED
//#define OVERFLOW_MODE_INTERRUPT_ENABLED
//#define CTC_MODE_TOGGLE_PIN
//#define PWM_MODE_CLEAR
#define PWM_MODE_SET
/****************************************
 * 										*
 *  OVERFLOW MODE, INTERRUPT DISABLED	*
 *                                      *
 ***************************************/

/* The purpose of the following test is to validate the behavior of the functions used in polling _checkFlag and _clearFlag*/

#ifdef OVERFLOW_MODE_INTERRUPT_DISABLED

int main (void)
{
	TIMER0_CONFIGURATION Timer_configStr={OVERFLOW_MODE, DISABLE, 0,0,P1024, DISABLE_INTERRUPT};
	Timer0_init(&Timer_configStr);
	static uint8 OVFcounter = 0;
	Timer0_start();

	while(1)
	{
		while(!Timer0_checkFlag());
		Timer0_clearFlag();
		OVFcounter++;

		if (OVFcounter ==61)
		{
		TOGGLE_BIT(PORTC,PC1);
		OVFcounter =0 ;
		}
	}
}

#endif //OVERFLOW_MODE_INTERRUPT_DISABLED

/****************************************
 * 										*
 *  OVERFLOW MODE, INTERRUPT ENABLED	*
 *                                      *
 ***************************************/

#ifdef OVERFLOW_MODE_INTERRUPT_ENABLED

ISR (TIMER0_OVF_vect)
{
	static uint8 OVFcounter = 0;
	OVFcounter++;
	if (OVFcounter == 61)
	{
		OVFcounter= 0 ;
		TOGGLE_BIT(PORTC,PC1);
	}
}

int main (void)
{
	TIMER0_CONFIGURATION Timer_configStr = {OVERFLOW_MODE, DISABLE, 0,0,P256, ENABLE_INTERRUPT};
	Timer0_init(&Timer_configStr);
	sei();
	Timer0_start();

	while(1)
	{

	}
}

#endif //OVERFLOW_MODE_INTERRUPT_ENABLED

/****************************************
 * 										*
 * 	  CTC MODE, INTERRUPT ENABLED		*
 *                                      *
 ***************************************/

#ifdef CTC_MODE_TOGGLE_PIN

ISR(TIMER0_COMPA_vect)
{
	TOGGLE_BIT(PORTC,PC1);
}



int main(void)
{
	TIMER0_CONFIGURATION Timer_configStr={CTC_MODE, TOGGLE, 0,128,P8, ENABLE_INTERRUPT};
		Timer0_init(&Timer_configStr);
		Timer0_start();
		while(1)
		{

		}
}

#endif //CTC_MODE_TOGGLE_PIN

#ifdef PWM_MODE_CLEAR

int main(void)
{
	TIMER0_CONFIGURATION Timer_configStr={FAST_PWM_MODE, CLEAR, 0,50,P64, DISABLE_INTERRUPT};
		Timer0_init(&Timer_configStr);
		Timer0_start();
		while(1)
		{

		}
}


#endif //PWM_MODE_CLEAR



#ifdef PWM_MODE_SET

int main(void)
{
	TIMER0_CONFIGURATION Timer_configStr={FAST_PWM_MODE, SET, 0,75,P64, DISABLE_INTERRUPT};
		Timer0_init(&Timer_configStr);
		Timer0_start();
		while(1)
		{

		}
}


#endif //PWM_MODE_SET

