/******************************************************************************
*  File name:		motor.c
*  Author:			Oct 5, 2022
*  Author:			Ahmed Tarek
*******************************************************************************/

/*******************************************************************************
*                        		Inclusions                                     *
*******************************************************************************/

#include "motor.h"
#include "../../MCAL/GPIO/gpio.h"
#include "../../LIB/common_macros.h"


void DoorMotor_Init(void)
{
	/* setting the direction of the motor pins */
	GPIO_setupPinDirection(DCMOTOR_IN1_PORT_ID, DCMOTOR_PIN_IN1, PIN_OUTPUT); /* Input1 */
	GPIO_setupPinDirection(DCMOTOR_IN2_PORT_ID, DCMOTOR_PIN_IN2, PIN_OUTPUT); /* Inupt2 */

	/* Stop the motor */
	GPIO_writePin(DCMOTOR_IN1_PORT_ID, DCMOTOR_PIN_IN1, LOGIC_LOW);
	GPIO_writePin(DCMOTOR_IN2_PORT_ID, DCMOTOR_PIN_IN2, LOGIC_LOW);
	GPIO_writePin(DCMOTOR_E_PORT_ID, DCMOTOR_PIN_E, LOGIC_HIGH);
}

void FanMotor_Init(void)
{
	/* setting the direction of the motor pins */
	GPIO_setupPinDirection(DCMOTOR2_IN3_PORT_ID, DCMOTOR2_PIN_IN3, PIN_OUTPUT); /* Input1 */
	GPIO_setupPinDirection(DCMOTOR2_IN4_PORT_ID, DCMOTOR2_PIN_IN4, PIN_OUTPUT); /* Inupt2 */

	/* Stop the motor */
	GPIO_writePin(DCMOTOR2_IN3_PORT_ID, DCMOTOR2_PIN_IN3, LOGIC_LOW);
	GPIO_writePin(DCMOTOR2_IN4_PORT_ID, DCMOTOR2_PIN_IN4, LOGIC_LOW);
	GPIO_writePin(DCMOTOR2_E_PORT_ID, DCMOTOR_PIN2_E, LOGIC_HIGH);
}

void DoorMotor_Rotate(DcMotor_State state)
{
	/* clearing the motor so we can change it state */
	GPIO_writePin(DCMOTOR_IN1_PORT_ID, DCMOTOR_PIN_IN1, LOGIC_LOW);
	GPIO_writePin(DCMOTOR_IN2_PORT_ID, DCMOTOR_PIN_IN2, LOGIC_LOW);

	GPIO_writePin(DCMOTOR_IN1_PORT_ID, DCMOTOR_PIN_IN1, GET_BIT(state,0));
	GPIO_writePin(DCMOTOR_IN2_PORT_ID, DCMOTOR_PIN_IN2, GET_BIT(state,1));
}

void FanMotor_Rotate(DcMotor_State state)
{
	/* clearing the motor so we can change it state */
	GPIO_writePin(DCMOTOR2_IN3_PORT_ID, DCMOTOR2_PIN_IN3, LOGIC_LOW);
	GPIO_writePin(DCMOTOR2_IN4_PORT_ID, DCMOTOR2_PIN_IN4, LOGIC_LOW);

	GPIO_writePin(DCMOTOR2_IN3_PORT_ID, DCMOTOR2_PIN_IN3, GET_BIT(state,0));
	GPIO_writePin(DCMOTOR2_IN4_PORT_ID, DCMOTOR2_PIN_IN4, GET_BIT(state,1));
}
