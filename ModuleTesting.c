

#include "Timer.h"
#include "Register_Macros.h"

int main (void)
{
	TIMER0_CONFIGURATION Timer_configStr={OVERFLOW_MODE, DISABLE, 10,0, DISABLE_INTERRUPT};
	DDRC = 0x01;
	Timer0_init(&Timer_configStr);
	Timer0_start(P1024);

	while(1)
	{
		while(!Timer0_checkFlag());
		TOGGLE_BIT(PORTC,1);
		Timer0_clearFlag();

	}
}
