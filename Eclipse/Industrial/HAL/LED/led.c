/*
 * led.c
 *
 *  Created on: Oct 12, 2022
 *      Author: Ahmed Tarek
 */

#include "led.h"
#include "../../MCAL/GPIO/gpio.h"

void LED_Init(void)
{
	GPIO_setupPinDirection(LEDS_PORT_ID, LEDS_FIRST_PIN_ID, PIN_OUTPUT);
}

void LED_ON(LEDS color)
{
	switch(color)
	{
	case RED:
		GPIO_writePin(LEDS_PORT_ID, LEDS_FIRST_PIN_ID, LOGIC_HIGH);
		break;
	}
}

void LED_OFF(LEDS color)
{
	switch(color)
	{
	case RED:
		GPIO_writePin(LEDS_PORT_ID, LEDS_FIRST_PIN_ID, LOGIC_LOW);
		break;
	}
}

void LED_TOGGLE(LEDS color)
{
	switch(color)
	{
	case RED:
		GPIO_togglePin(LEDS_PORT_ID, LEDS_FIRST_PIN_ID, LOGIC_LOW);
		break;
	}
}
