/******************************************************************************
*  File name:		uart.h
*  Author:			Oct 12, 2022
*  Author:			Ahmed Tarek
*******************************************************************************/

/*******************************************************************************
*                        		Inclusions                                     *
*******************************************************************************/

#include "uart.h"
#include "avr/io.h"
#include "../../LIB/common_macros.h"
#include "avr/interrupt.h"

/*******************************************************************************
*                           Global Variables                                  *
*******************************************************************************/

static uint8 g_endStringChar; /* to store the special char to end sting at */
static volatile void (*g_callBackPtr)(void) = NULL_PTR; /* to store the address of the function */

/*******************************************************************************
*                      Functions Definitions                                   *
*******************************************************************************/

void UART_init(unsigned long baud)
{
	/*1 - Choose baud rate that will be used by sender and receiver by writing to UBRRL/UBRRH*/
	unsigned short UBRR ;
	UBRR=(F_CPU/(16*baud))-1 ;
	UBRRH=(unsigned char)(UBRR>>8);
	UBRRL=(unsigned char)UBRR;
	/*2 - Enable USART Sender & Receiver*/
	SET_BIT(UCSRB,TXEN);
	SET_BIT(UCSRB,RXEN);
	SET_BIT(UCSRB,RXCIE);
	/*3 - Choose number of data bits to be sent,parity and stop bits from UCSRC
	, We will work with 8 bits data,1 stop bit and no parity bits*/
	UCSRC=(1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);
}

void UART_sendByte(const uint8 data)
{
	while(BIT_IS_CLEAR(UCSRA,UDRE)){}

	UDR = data;
}

uint8 UART_receiveByte()
{
	while(BIT_IS_CLEAR(UCSRA,RXC)){}

	return UDR;
}

void UART_sendString(const uint8 *Str)
{
	uint8 i ;
	for(i = 0 ; Str[i] != '\0' ; i++)
	{
		UART_sendByte(Str[i]);
	}
}

void UART_receiveString(uint8 *Str)
{
	uint8 i = 0;

	/* Receive the first byte */
	Str[i] = UART_receiveByte();

	/* Receive the whole string until the '#' */
	while(Str[i] != g_endStringChar)
	{
		i++;
		Str[i] = UART_receiveByte();
	}

	/* After receiving the whole string plus the '#', replace the '#' with '\0' */
	Str[i] = '\0';

}

void UART_setCallBack( void(*a_ptr)(void) )
{
	g_callBackPtr = a_ptr;
}
