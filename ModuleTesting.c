

#include "Servo_Motor.h"
#include "Register_Macros.h"

int main (void)
{
	DDRD |= (1<<PD5);	/* Make OC1A pin as output */

	while(1)
	{
		Timer1_Fast_PWM_Init(124);	/* Set Servo shaft at 0° position by 1 ms pulse */
		_delay_ms(1500);
		Timer1_Fast_PWM_Init(187);	/* Set Servo shaft at 90° position by 1.5 ms pulse */
		_delay_ms(1500);
		Timer1_Fast_PWM_Init(250);	/* Set Servo shaft at 180° position by 2 ms pulse */
		_delay_ms(1500);
	}
	return 0;
}
