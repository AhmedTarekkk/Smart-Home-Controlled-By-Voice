/******************************************************************************
*  File name:		timer0.c
*  Author:			NOV 12, 2022
*  Author:			Ahmed Tarek
*******************************************************************************/

/*******************************************************************************
*                        		Inclusions                                     *
*******************************************************************************/
#include "timer0.h"
#include "avr/interrupt.h"
#include "avr/io.h"

/*******************************************************************************
*                           Global Variables                                  *
*******************************************************************************/
static volatile void (*g_callBackPtr1)(void) = NULL_PTR; /* to store the address of the function */
static volatile void (*g_callBackPtr2)(void) = NULL_PTR; /* to store the address of the function */

/*******************************************************************************
*                      Functions Definitions                                   *
*******************************************************************************/
//ISR(TIMER0_COMP_vect)
//{
//	if(g_callBackPtr1 != NULL_PTR)
//	{
//		(*g_callBackPtr1)();
//	}
//}

ISR(TIMER0_OVF_vect)
{
	if(g_callBackPtr2 != NULL_PTR)
	{
		(*g_callBackPtr2)();
	}
}

void TIMER0_init(Timer0_ConfigType * Config_Ptr)
{
	TCCR0 = (1<<FOC0) | (Config_Ptr->mode << WGM01);
	TCCR0 = (TCCR0 & 0xF8) | (Config_Ptr->prescaler);

	TCNT0 = Config_Ptr->initial_value;
	if(Config_Ptr->mode == COMPARE0)
	{
		OCR0 = Config_Ptr->compare_value;
		TIMSK |= (1<<OCIE0) ;
	}
	else
	{
		TIMSK |= (1<<TOIE0) ;
	}
}

void TIMER0_deInit()
{
	TCCR0 = 0;
	TCNT0 = 0;
	OCR0 = 0;
}

void TIMER0_COMP_setCallBack( void(*a_ptr)(void) )
{
	g_callBackPtr1 = a_ptr;
}

void TIMER0_OVF_setCallBack( void(*a_ptr)(void) )
{
	g_callBackPtr2 = a_ptr;
}

