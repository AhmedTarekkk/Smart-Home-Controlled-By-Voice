/*
 * led.h
 *
 *  Created on: Oct 12, 2022
 *      Author: Ahmed Tarek
 */

#ifndef HAL_LED_LED_H_
#define HAL_LED_LED_H_
#include "../../LIB/std_types.h"

#define LEDS_PORT_ID			PORTD_ID
#define	LEDS_FIRST_PIN_ID		PIN5_ID

typedef enum
{
	RED
}LEDS;

void LED_Init(void);

void LED_ON(LEDS color);

void LED_OFF(LEDS color);

void LED_TOGGLE(LEDS color);

#endif /* HAL_LED_LED_H_ */
