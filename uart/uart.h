/*
 * uart.h
 *
 * Created: 2/10/2016 1:35:06 PM
 *  Author: Mostafa El-Koumy
 */ 
#ifndef UART_H_
#define UART_H_

#include <avr/io.h>

typedef struct
{
	unsigned long baudrate;
	unsigned long freq;
	unsigned char parity;
	unsigned char nBitsSymbol;
	unsigned char nStopBits;
	unsigned char mode;
	unsigned char channel; 		//optional in multi-channel uart(s)
}uart_t;

/* UCSRA */
#define RXC_OFFSET				7
#define TXC_OFFSET				6
#define UDRE_OFFSET				5
#define FE_OFFSET				4
#define DOR_OFFSET				3
#define PE_OFFSET				2
#define U2X_OFFSET				1
#define MPCM_OFFSET				0
/* UCSRB */
#define RXCIE_OFFSET			7
#define TXCIE_OFFSET			6
#define UDRIE_OFFSET			5
#define RXEN_OFFSET				4
#define TXEN_OFFSET				3
#define NINTH_BIT_ENABLE_UCSZ	2
#define RXB8_OFFSET				1
#define TXB8_OFFSET				0
/* UCSRC */
#define URSEL_OFFSET			7
#define UMSEL_OFFSET			6
#define PARITY_OFFSET			4
#define USBS_OFFSET				3
#define UCSZ_OFFSET				1
#define UCPOL_OFFSET			0


#define PARITY_NONE				0
#define PARITY_EVEN				2
#define PARITY_ODD				3

#define ONE_STOP_BIT			0
#define TWO_STOP_BITS			1

#define CHAR_SIZE_FIVE			0
#define CHAR_SIZE_SIX			1
#define CHAR_SIZE_SEVEN			2
#define CHAR_SIZE_EIGHT			3
#define CHAR_SIZE_NINE			4

#define MODE_SYNC				1
#define MODE_ASYNC				0

#define STATUS_OK				0
#define STATUS_FAIL				0xF0002
#define STATUS_ERROR_PARITY		0xF0003
#define STATUS_ERROR_FRAME		0xF0004
#define STATUS_ERROR_DOR		0xF0005



void uartInit(uart_t* pUart);

void uartTrans(uart_t* pUart, void* pData);

unsigned int uartRecv(uart_t* pUart, void* pData);

#endif