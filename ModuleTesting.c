

#include "Timer.h"
#include "Register_Macros.h"

int main (void)
{
	DDRC = 0x01;
	Timer0_init(OVERFLOW_MODE, DISABLE, 10, 0, DISABLE_INTERRUPT);
	Timer0_start(P1024);

	while(1)
	{
		while(!Timer0_checkFlag());
		TOGGLE_BIT(PORTC,1);
		Timer0_clearFlag();
	}
}
