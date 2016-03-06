/*
 * atmega32_SDK.c
 *
 * Created: 2/10/2016 1:34:16 PM
 * Author : Mostafa
 */ 

#include <avr/io.h>
#include "gpio/gpio.h"
#include <util/delay.h>

#ifdef F_CPU
#undef F_CPU
#define F_CPU 8000000UL
#endif



int main(void)
{
	pin_t led;
	led.port = PORT_B;
	led.bit = 7;
	led.dir = DIR_OUT;
	
	led.lastDir = 1;
	
	pin_t sw;
	sw.bit = 1;
	sw.dir = DIR_IN;
	sw.port = PORT_A;
	sw.lastDir = 1;
	
    /* Replace with your application code */
    while (1) 
    {
		pinUpdate(&sw);
		if (sw.val == 0)
		{
			led.val = 1;
			pinUpdate(&led);
		}
		else
		{
			led.val = 0;
			pinUpdate(&led);
		}
    }
}

