#include "gpio.h"

void pinInitialize(unsigned char port, unsigned char bit, pin_t* pPin)
{
	memset(pPin, 0, sizeof(pin_t));
	
	if(port < PORT_VALID)
		pPin->port = port;
	if(bit < (sizeof(bit)*8))
		pPin->bit = bit;
}
	
void pinSetInp(pin_t* pPin)
{
	/* any pin is set input by default due to memset in the initialize function*/
	
	unsigned char tempPin = 0, tempPort = 0, tempBit;
	
	memcpy(&tempPin, pPin, sizeof(tempPin));
	
	tempBit  = (tempPin>>3) & MASK(3);
	tempPort = (tempPin>>1) & MASK(2);
	
	if(tempPort == PORT_A)
		CLR_BIT(DDRA, tempBit);
	else if(tempPort == PORT_B)
		CLR_BIT(DDRB, tempBit);
	else if(tempPort == PORT_C)
		CLR_BIT(DDRC, tempBit);
	else
		CLR_BIT(DDRD, tempBit);
	
}
void pinSetOut(pin_t* pPin)
{
	
	unsigned char tempPin = 0, tempPort = 0, tempBit;
	
	memcpy(&tempPin, pPin, sizeof(tempPin));
	
	tempBit  = (tempPin>>3) & MASK(3);
	tempPort = (tempPin>>1) & MASK(2);
	
	if(tempPort == PORT_A)
		SET_BIT(DDRA, tempBit);
	else if(tempPort == PORT_B)
		SET_BIT(DDRB, tempBit);
	else if(tempPort == PORT_C)
		SET_BIT(DDRC, tempBit);
	else
		SET_BIT(DDRD, tempBit);
	
	/* This line will take only 1 scan cycle */
	pPin->dir = DIR_OUT;
	
	/* This will take more scan cycle to be executed so this is ignored
	
	tempPin |= 1;
	memcpy(pin, &tempPin, sizeof(tempPin));
	
	*/
}

void pinWriteOn(pin_t* pPin)
{
	unsigned char tempPin = 0, tempPort = 0, tempBit;
	
	memcpy(&tempPin, pPin, sizeof(tempPin));
	
	tempBit  = (tempPin>>3) & MASK(3);
	tempPort = (tempPin>>1) & MASK(2);
	
	if(tempPort == PORT_A)
		SET_BIT(PORTA, tempBit);
	else if(tempPort == PORT_B)
		SET_BIT(PORTB, tempBit);
	else if(tempPort == PORT_C)
		SET_BIT(PORTC, tempBit);
	else
		SET_BIT(PORTD, tempBit);
	
	/* This line will take only 1 scan cycle */
	pPin->val = 1;
}
void pinWriteOff(pin_t* pPin)
{
	unsigned char tempPin = 0, tempPort = 0, tempBit;
	
	memcpy(&tempPin, pPin, sizeof(tempPin));
	
	tempBit  = (tempPin>>3) & MASK(3);
	tempPort = (tempPin>>1) & MASK(2);
	
	if(tempPort == PORT_A)
		CLR_BIT(PORTA, tempBit);
	else if(tempPort == PORT_B)
		CLR_BIT(PORTB, tempBit);
	else if(tempPort == PORT_C)
		CLR_BIT(PORTC, tempBit);
	else
		CLR_BIT(PORTD, tempBit);
	
	/* This line will take only 1 scan cycle */
	pPin->val = 0;
}

unsigned char pinReadInp(pin_t* pPin)
{
	unsigned char tempVal = 0;
	unsigned char tempPin = 0, tempPort = 0, tempBit;
	
	memcpy(&tempPin, pPin, sizeof(tempPin));
	
	tempBit  = (tempPin>>3) & MASK(3);
	tempPort = (tempPin>>1) & MASK(2);
	
	if(tempPort == PORT_A)
		tempVal = (PINA>>tempBit) & 0x1;
	else if(tempPort == PORT_B)
		tempVal = (PINB>>tempBit) & 0x1;
	else if(tempPort == PORT_C)
		tempVal = (PINC>>tempBit) & 0x1;
	else
		tempVal = (PIND>>tempBit) & 0x1;
	
	
	pPin->val = tempVal;

	return tempVal;
}

int blindInit(pin_t* pPin)
{
	unsigned char tempDir, tempPort, tempBit, tempPin;

	if(!(*(unsigned char*)pPin))
		return -1;
	
	memcpy(&tempPin, pPin, sizeof(tempPin));
	
	tempDir  = tempPin & 1;
	tempPort = (tempPin>>1) & MASK(2);
	tempBit  = (tempPin>>3) & MASK(3);
	
	if(tempPort == PORT_A)
	{
		if(tempDir == DIR_IN)
		{
			CLR_BIT(DDRA, tempBit);
		}
		else
		{
			SET_BIT(DDRA, tempBit);
		}
	}
	else if(tempPort == PORT_B)
	{
		if(tempDir == DIR_IN)
		{
			CLR_BIT(DDRB, tempBit);
		}
		else
		{
			SET_BIT(DDRB, tempBit);
		}
	}
	else if(tempPort == PORT_C)
	{
		if(tempDir == DIR_IN)
		{
			CLR_BIT(DDRC, tempBit);
		}
		else
		{
			SET_BIT(DDRC, tempBit);
		}
	}
	else
	{
		if(tempDir == DIR_IN)
		{
			CLR_BIT(DDRD, tempBit);
		}
		else
		{
			SET_BIT(DDRD, tempBit);
		}
	}
		
	pPin->lastDir = pPin->dir;
	return 0;
}

unsigned char blindExecutePin(pin_t* pPin)
{
	unsigned char tempDir, tempPort, tempBit, tempPin, tempVal;
	
	if(!(*(unsigned char*)pPin))
		return -1;
	
	memcpy(&tempPin, pPin, sizeof(tempPin));
	
	tempDir  = tempPin & 1;
	tempPort = (tempPin>>1) & MASK(2);
	tempBit  = (tempPin>>3) & MASK(3);
	tempVal  = (tempPin & (1<<7)) ? (1) : (0);
	
	if(tempPort == PORT_A)
	{
		if(tempDir == DIR_IN)
		{
			tempVal = (PINA>>tempBit) & 1;
		}
		else
		{
			PORTA = (PORTA & (~(1<<tempBit)) | (tempVal<<tempBit));
			tempVal = 0;
		}
	}
	else if(tempPort == PORT_B)
	{
		if(tempDir == DIR_IN)
		{
			tempVal = (PINB>>tempBit) & 1;
		}
		else
		{
			PORTB = (PORTB & (~(1<<tempBit)) | (tempVal<<tempBit));
		}
	}
	else if(tempPort == PORT_C)
	{
		if(tempDir == DIR_IN)
		{
			tempVal = (PINC>>tempBit) & 1;
		}
		else
		{
			PORTC = (PORTC & (~(1<<tempBit)) | (tempVal<<tempBit));
		}
	}
	else
	{
		if(tempDir == DIR_IN)
		{
			tempVal = (PIND>>tempBit) & 1;
		}
		else
		{
			PORTD = (PORTD & (~(1<<tempBit)) | (tempVal<<tempBit));
		}
	}
		
	pPin->val =  tempVal;
		
}

void pinUpdate(pin_t* pPin)
{
	if(pPin->lastDir != pPin->dir)
	{
		blindInit(pPin);
	}
	blindExecutePin(pPin);
}