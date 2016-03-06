#include "uart.h"

void uartInit(uart_t* pUart)
{	
	unsigned long ubrrValue = 0;
	UCSRB = (1<<TXEN_OFFSET) | (1<<RXEN_OFFSET) | (pUart->nBitsSymbol == CHAR_SIZE_NINE) ? (1<<NINTH_BIT_ENABLE_UCSZ) : (0);
	UCSRC = (1<<URSEL_OFFSET) | (pUart->parity<<PARITY_OFFSET) | 
			(pUart->nStopBits<<USBS_OFFSET) | (pUart->nBitsSymbol<<UCSZ_OFFSET) | 
			(pUart->mode == MODE_ASYNC) ? (1<<UMSEL_OFFSET) : (0);
	
	if(pUart->mode == MODE_ASYNC)
		ubrrValue = pUart->freq / 16 * pUart->baudrate - 1;
	else
		ubrrValue = pUart->freq / 2 * pUart->baudrate - 1;
	
	UBRRL = ubrrValue;
	UBRRH = ubrrValue>>8;
}

void uartTrans(uart_t* pUart, void* pData)
{
	unsigned int temp=0;
	while(UCSRA & ~(1<<UDRE_OFFSET));
	if(pUart->nBitsSymbol)
	{
		temp = (unsigned int*)pData;
		UDR = (unsigned char)temp;
		UCSRB &= ((temp >> (8-TXB8_OFFSET)) & (1<<TXB8_OFFSET));
	}
	else
		UDR = (unsigned char*)pData;
	/* optional to be sure data had been sent */
	while(UCSRA & ~(1<<TXC_OFFSET));
}

unsigned int uartRecv(uart_t* pUart, void* pData)
{
	unsigned int temp, status = 0;
	while(UCSRA & ~(1<<RXC_OFFSET));
	status = (UCSRA & ((1<<FE_OFFSET) | (1<<DOR_OFFSET) | (1<<PE_OFFSET)));
	temp = UDR;
	if(pUart->nBitsSymbol == CHAR_SIZE_NINE)
	{
		temp |= (UCSRB & (1<<RXB8_OFFSET))<<(9-RXB8_OFFSET);
	}
	memcpy(pData, &temp, (pUart->nBitsSymbol == CHAR_SIZE_NINE) ? (2) : (1));
	
	return status;
}