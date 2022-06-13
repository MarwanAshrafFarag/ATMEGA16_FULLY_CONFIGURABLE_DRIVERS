

#include "Timer.h"

#define CTC_MODE_INTERRUPT_ENABLED

/****************************************
 * 										*
 *  OVERFLOW MODE, INTERRUPT DISABLED	*
 *                                      *
 ***************************************/

/* The purpose of the following test is to validate the behavior of the functions used in polling _checkFlag and _clearFlag*/

#ifdef OVERFLOW_MODE_INTERRUPT_DISABLED

int main (void)
{
	TIMER0_CONFIGURATION Timer_configStr={OVERFLOW_MODE, DISABLE, 0,0, DISABLE_INTERRUPT};
	Timer0_init(&Timer_configStr);
	static uint8 OVFcounter = 0;
	Timer0_start(P1024);

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

#endif

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
	TIMER0_CONFIGURATION Timer_configStr = {OVERFLOW_MODE, DISABLE, 0,0, ENABLE_INTERRUPT};
	Timer0_init(&Timer_configStr);
	sei();
	Timer0_start(P1024);

	while(1)
	{

	}
}

#endif

/****************************************
 * 										*
 * 	  CTC MODE, INTERRUPT ENABLED		*
 *                                      *
 ***************************************/

#ifdef CTC_MODE_INTERRUPT_ENABLED

ISR(TIMER0_COMPA_vect)
{
	TOGGLE_BIT(PORTC,PC1);
}



int main(void)
{
	TIMER0_CONFIGURATION Timer_configStr={CTC_MODE,  TOGGLE, 0,128, ENABLE_INTERRUPT};
		Timer0_init(&Timer_configStr);
		Timer0_start(P1024);
		while(1)
		{

		}
}

#endif
