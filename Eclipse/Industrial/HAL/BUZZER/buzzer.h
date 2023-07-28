/******************************************************************************
*  File name:		buzzer.h
*  Author:			Oct 11, 2022
*  Author:			Ahmed Tarek
*******************************************************************************/

#ifndef HAL_BUZZER_BUZZER_H_
#define HAL_BUZZER_BUZZER_H_

/*******************************************************************************
*                        		Inclusions                                     *
*******************************************************************************/

#include "../../LIB/std_types.h"


/*******************************************************************************
*                        		Definitions                                    *
*******************************************************************************/

#define BUZZER_PORT_ID					PORTD_ID
#define	BUZZER_PIN_ID					PIN4_ID

/*******************************************************************************
*                      Functions Prototypes                                   *
*******************************************************************************/

/*******************************************************************************
* Function Name:		BUZZER_init
* Description:			Function to initialize the buzzer pin
* Parameters (in):    	None
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/

void BUZZER_init(void);

/*******************************************************************************
* Function Name:		BUZZER_on
* Description:			Function to turn the buzzer on
* Parameters (in):    	None
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/

void BUZZER_on(void);

/*******************************************************************************
* Function Name:		BUZZER_off
* Description:			Function to turn the buzzer off
* Parameters (in):    	None
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/

void BUZZER_off(void);

#endif /* HAL_BUZZER_BUZZER_H_ */
