/******************************************************************************
*  File name:		timer0.h
*  Author:			NOV 12, 2022
*  Author:			Ahmed Tarek
*******************************************************************************/

#ifndef MCAL_TIMER0_TIMER0_H_
#define MCAL_TIMER0_TIMER0_H_

/*******************************************************************************
*                        		Inclusions                                     *
*******************************************************************************/
#include "../../LIB/std_types.h"

/*******************************************************************************
*                         Types Declaration                                   *
*******************************************************************************/

/*******************************************************************************
* Name: Timer0_Mode
* Type: Enumeration
* Description: Data type to represent the timer mode
********************************************************************************/
typedef enum
{
	NORMAL0,
	COMPARE0
}Timer0_Mode;

/*******************************************************************************
* Name: Timer0_Prescaler
* Type: Enumeration
* Description: Data type to represent the timer prescaler
********************************************************************************/
typedef enum
{
	TIMER0_OFF,
	TIMER0_FCPU_1,
	TIMER0_FCPU_8,
	TIMER0_FCPU_64,
	TIMER0_FCPU_256,
	TIMER0_FCPU_1024
}Timer0_Prescaler;

/*******************************************************************************
* Name: Timer0_ConfigType
* Type: Structure
* Description: Data type to dynamic configure the timer module
********************************************************************************/
typedef struct {
 uint16 initial_value;
 uint16 compare_value; // it will be used in compare mode only.
 Timer0_Prescaler prescaler;
 Timer0_Mode mode;
} Timer0_ConfigType;

/*******************************************************************************
*                      Functions Prototypes                                   *
*******************************************************************************/

/*******************************************************************************
* Function Name:		TIMER0_init
* Description:			Function to dynamic configure the timer module
* Parameters (in):    	Pointer to structure of type Timer1_ConfigType
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/
void TIMER0_init(Timer0_ConfigType * Config_Ptr);

/*******************************************************************************
* Function Name:		TIMER0_deInit
* Description:			Function to de-initialize the timer module and stop it
* Parameters (in):    	None
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/
void TIMER0_deInit();

/*******************************************************************************
* Function Name:		TIMER0_COMP_setCallBack
* Description:			Function to set the ISR for timer in case using compare mode
* Parameters (in):    	Pointer to function to be the ISR
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/
void TIMER0_COMP_setCallBack( void(*a_ptr)(void) );

/*******************************************************************************
* Function Name:		TIMER0_OVF_setCallBack
* Description:			Function to set the ISR for timer in case using overflow mode
* Parameters (in):    	Pointer to function to be the ISR
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/
void TIMER0_OVF_setCallBack( void(*a_ptr)(void) );

#endif /* MCAL_TIMER0_TIMER0_H_ */
