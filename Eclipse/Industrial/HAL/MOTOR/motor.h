/******************************************************************************
*  File name:		motor.h
*  Author:			Oct 5, 2022
*  Author:			Ahmed Tarek
*******************************************************************************/

#ifndef MOTOR_H_
#define MOTOR_H_

/*******************************************************************************
*                        		Inclusions                                     *
*******************************************************************************/

#include "../../LIB/std_types.h"

/*******************************************************************************
*                        		Definitions                                    *
*******************************************************************************/

#define DCMOTOR_IN1_PORT_ID				PORTD_ID
#define	DCMOTOR_PIN_IN1					PIN7_ID
#define DCMOTOR_IN2_PORT_ID				PORTC_ID
#define	DCMOTOR_PIN_IN2					PIN0_ID

#define DCMOTOR2_IN3_PORT_ID			PORTC_ID
#define	DCMOTOR2_PIN_IN3				PIN2_ID
#define DCMOTOR2_IN4_PORT_ID			PORTC_ID
#define	DCMOTOR2_PIN_IN4				PIN3_ID

#define DCMOTOR_E_PORT_ID				PORTD_ID
#define	DCMOTOR_PIN_E					PIN6_ID

#define DCMOTOR2_E_PORT_ID			PORTC_ID
#define DCMOTOR_PIN2_E					PIN1_ID

/*******************************************************************************
*                         Types Declaration                                   *
*******************************************************************************/

/*******************************************************************************
* Name: DcMotor_State
* Type: Enumeration
* Description: Data type to represent the different states of the motor
********************************************************************************/

typedef enum
{
	DcMotor_STOP,
	DcMotor_CW,
	DcMotor_CCW
}DcMotor_State;

/*******************************************************************************
*                      Functions Prototypes                                   *
*******************************************************************************/

/*******************************************************************************
* Function Name:		DcMotor_Init
* Description:			Function to initialize the motor for the Door and the fan
* Parameters (in):    	None
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/

void DoorMotor_Init(void);
void FanMotor_Init(void);

/*******************************************************************************
* Function Name:		DcMotor_Rotate
* Description:			Function to control the motor direction and its speed
* Parameters (in):    	Required direction and speed
* Parameters (out):   	None
* Return value:      	void
********************************************************************************/

void DoorMotor_Rotate(DcMotor_State state);
void FanMotor_Rotate(DcMotor_State state);

#endif /* MOTOR_H_ */
