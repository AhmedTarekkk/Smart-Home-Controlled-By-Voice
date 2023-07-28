#include "HAL/KEYPAD/keypad.h"
#include "HAL/LCD/lcd.h"
#include "HAL/MOTOR/motor.h"
#include "HAL/LED/led.h"
#include "HAL/BUZZER/buzzer.h"
#include "MCAL/TIMER0/timer0.h"
#include "MCAL/UART/uart.h"
#include <avr/eeprom.h>
#include "avr/interrupt.h"
#include "util/delay.h"
#include "string.h"

#define PasswordFlagAddress		(uint8 *)0x0010
#define PasswordAddress			(uint8 *)0x0000
#define PasswordIsSet			0xC3

#define PASSWORD_SIZE			2
#define TRIES_ALLOWED			3
#define KEYPAD_DELAY			500
#define ENTER_KEY				'A'
#define ALARM_TIME				10
#define OPEN_DOOR_TIME			4
#define CLOSE_DOOR_TIME			4
#define OPENED_DOOR				2
#define TIMER0_TICKS_TO_SEC		32


uint8 Password[PASSWORD_SIZE];
uint8 Password2[PASSWORD_SIZE];
uint8 PasswordsMatched;
volatile uint16 g_ticks0 = 0;
uint16 g_ticks2 = 0;

Timer0_ConfigType TIMER0_Configuration = {0,250,TIMER0_FCPU_1024,COMPARE0}; /* 32 ticks = 1 second */

void APP_setPassword();
void APP_updatePassword();
uint8 APP_checkPassword();
void APP_door();
void APP_changePassword();
void APP_alarm();

ISR(TIMER0_COMP_vect)
{
	g_ticks0++;
}

char String[20]; // Global variable to store the char received from UART

ISR(USART_RXC_vect)
{
	static uint8 counter ;
	String[counter] = UDR;
	if(String[counter] == '#')
	{
		String[counter] = '\0';
		counter = 0 ; // to receive new string in the same buffer
	    if((strcmp(String,"*light") == 0) || (strcmp(String,"*Light") == 0))
		{
			LED_TOGGLE(RED);
		}
	    else if((strcmp(String,"*turn on the fan") == 0))
	    {
	    	FanMotor_Rotate(DcMotor_CW);
	    }
	    else if((strcmp(String,"*turn off the fan") == 0))
	    {
	    	FanMotor_Rotate(DcMotor_STOP);
	    }
	}
	else
	{
		counter++;
	}
}

int main(void)
{
	LED_Init();
	UART_init(9600);
	DoorMotor_Init();
	FanMotor_Init();
	BUZZER_init();
	KEYPAD_init();
	LCD_init();
	sei();

	if(eeprom_read_byte(PasswordFlagAddress) != PasswordIsSet)
	{
		APP_setPassword();
	}

	while(1)
	{
		LCD_clearScreen();
		LCD_displayStringRowColumn(0, 0, "* : Open Door");
		LCD_displayStringRowColumn(1, 0, "# : Change Pass");
		uint8 menuKey;
		do
		{
			menuKey = KEYPAD_getPressedKey();
		}while((menuKey != '*') && (menuKey != '#'));
		switch(menuKey)
		{
		case '*':
			APP_door();
			break;
		case '#':
			APP_changePassword();
			break;
		}
	}
}

void APP_setPassword()
{
	do
	{
		PasswordsMatched = TRUE;
		LCD_clearScreen();
		LCD_displayStringRowColumn(0, 0, "Enter New Pass: ");
		LCD_moveCursor(1, 0);
		for(uint8 i = 0 ; i < PASSWORD_SIZE ; i++)
		{
			uint8 key = KEYPAD_getPressedKey();
			if(key >= '0' && key <= '9')
			{
				Password[i] = key;
				LCD_displayCharacter(key);//LCD_displayCharacter('*');
			}
			else
			{
				i--;
			}
			_delay_ms(KEYPAD_DELAY);
		}
		while(KEYPAD_getPressedKey() != ENTER_KEY);

		LCD_clearScreen();
		LCD_displayStringRowColumn(0, 0, "Enter Pass again");
		LCD_moveCursor(1, 0);
		for(uint8 i = 0 ; i < PASSWORD_SIZE ; i++)
		{
			uint8 key = KEYPAD_getPressedKey();
			if(key >= '0' && key <= '9')
			{
				Password2[i] = key;
				LCD_displayCharacter(key);//LCD_displayCharacter('*');
			}
			else
			{
				i--;
			}
			_delay_ms(KEYPAD_DELAY);
		}
		while(KEYPAD_getPressedKey() != ENTER_KEY);

		for(uint8 i = 0 ; i < PASSWORD_SIZE ; i++)
		{
			if(Password[i] != Password2[i])
			{
				PasswordsMatched = FALSE;
				LCD_clearScreen();
				LCD_displayStringRowColumn(0, 3, "UnMatched");
				LCD_displayStringRowColumn(1, 0, "Try again");
				_delay_ms(1000);
				break;
			}
		}
	}while(PasswordsMatched == FALSE);
	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 3, "Matched");
	LCD_displayStringRowColumn(1, 0, "Password Saved");
	_delay_ms(1000);
	eeprom_write_block(Password,PasswordAddress,PASSWORD_SIZE);
	eeprom_write_byte(PasswordFlagAddress,PasswordIsSet);
}

void APP_updatePassword()
{
	for(int i = 0 ; i < PASSWORD_SIZE ; i++)
	{
		Password[i] = eeprom_read_byte(PasswordAddress+i);
	}
}

uint8 APP_checkPassword()
{
	APP_updatePassword();
	uint8 Lives = TRIES_ALLOWED;
	do
	{
		LCD_clearScreen();
		LCD_displayString("Plz Enter Pass");
		PasswordsMatched = TRUE;
		LCD_moveCursor(1, 0);
		for(uint8 i = 0 ; i < PASSWORD_SIZE ; i++)
		{
			uint8 key = KEYPAD_getPressedKey();
			if(key >= '0' && key <= '9')
			{
				Password2[i] = key;
				LCD_displayCharacter(key);//LCD_displayCharacter('*');
			}
			else
			{
				i--;
			}
			_delay_ms(KEYPAD_DELAY);
		}
		while(KEYPAD_getPressedKey() != ENTER_KEY);

		for(uint8 i = 0 ; i < PASSWORD_SIZE ; i++)
		{
			if(Password[i] != Password2[i])
			{
				PasswordsMatched = FALSE;
				Lives--;
				LCD_clearScreen();
				LCD_displayStringRowColumn(0, 3, "UnMatched");
				LCD_displayStringRowColumn(1, 0, "Tires Left = ");
				LCD_intgerToString(Lives);
				_delay_ms(1000);
				break;
			}
		}
		if(PasswordsMatched == TRUE)
		{
			LCD_clearScreen();
			LCD_displayStringRowColumn(0, 3, "Matched");
			_delay_ms(1000);
			return TRUE;
		}
	}while(Lives > 0);
	return FALSE;
}

void APP_door()
{
	if(APP_checkPassword() == TRUE)
	{
		TIMER0_init(&TIMER0_Configuration);
//		TIMER0_COMP_setCallBack(TIMER0_ISR);
		LCD_clearScreen();
		LCD_displayString("Opening the Door");
		g_ticks0 = 0;
		DoorMotor_Rotate(DcMotor_CW);
		while(g_ticks0 != TIMER0_TICKS_TO_SEC * OPEN_DOOR_TIME){}

		LCD_clearScreen();
		LCD_displayString("Door is Opened");
		g_ticks0 = 0;
		DoorMotor_Rotate(DcMotor_STOP);
		while(g_ticks0 != TIMER0_TICKS_TO_SEC*OPENED_DOOR){}
		LCD_clearScreen();
		LCD_displayString("Closing the Door");
		g_ticks0 = 0;
		DoorMotor_Rotate(DcMotor_CCW);
		while(g_ticks0 != TIMER0_TICKS_TO_SEC*CLOSE_DOOR_TIME){}
		g_ticks0 = 0;
		DoorMotor_Rotate(DcMotor_STOP);
		TIMER0_deInit();
	}
	else
	{
		APP_alarm();
	}
}

void APP_changePassword()
{
	if(APP_checkPassword() == TRUE)
	{
		APP_setPassword();
	}
	else
	{
		APP_alarm();
	}
}

void APP_alarm()
{
	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 3, "ERROR !!!");
	LCD_displayStringRowColumn(1, 0, "Try Again Later");
	TIMER0_init(&TIMER0_Configuration);
	g_ticks0 = 0;
	BUZZER_on();
	while(g_ticks0 != TIMER0_TICKS_TO_SEC*ALARM_TIME){}
	BUZZER_off();
}
