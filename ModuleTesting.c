

#include "Timer.h"
uint8 counter;


/****************************************
 * 										*
 *  OVERFLOW MODE, INTERRUPT DISABLED	*
 *                                      *
 ***************************************/



int main (void)
{
	TIMER0_CONFIGURATION Timer_configStr={OVERFLOW_MODE, DISABLE, 0,0, DISABLE_INTERRUPT};
	Timer0_init(&Timer_configStr);
	Timer0_start(P1024);

	while(1)
	{
		while(!Timer0_checkFlag());
		Timer0_clearFlag();
		counter++;

		if (counter ==61)
		{
		TOGGLE_BIT(PORTC,1);
		counter =0 ;
		}
	}
}





