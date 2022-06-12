

#include "Timer.h"
uint8 counter;

/*ISR (TIMER0_OVF_vect)
{
	counter++;
}*/

int main (void)
{
	TIMER0_CONFIGURATION Timer_configStr={OVERFLOW_MODE, DISABLE, 0,0, DISABLE_INTERRUPT};
	Timer0_init(&Timer_configStr);
	sei();
	Timer0_start(P1024);

	while(1)
	{
		while(!Timer0_checkFlag());
		counter++;
		//_delay_ms(500);
		if (counter ==50)
		{
		TOGGLE_BIT(PORTC,1);
		counter =0 ;
		}
	}
}
