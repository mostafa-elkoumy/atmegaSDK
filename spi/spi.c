/*
 * spi.c
 *
 * Created: 2/10/2016 3:14:43 PM
 *  Author: Mostafa El-Koumy
 */ 
#include "spi.h"
#include "spi_config.h"
#include "../commonDefs.h"
#include <stdio.h>


void spiInitialize(spi_t* pSpi)
{
	unsigned char tempSpi;
	memcpy(&tempSpi, pSpi, sizeof(tempSpi));
	
	SPCR =	((tempSpi & (1<<7))			<< SPIF_OFFSET)		|
			((tempSpi & (1<<6))			<< DORD_OFFSET)		|
			((tempSpi & (MASK(2) << 3)) << SPR_OFFSET)		|
			((tempSpi & (1<<2))			<< MSTR_OFFSET)		|
			((tempSpi & (1<<1))			<< CPHA_OFFSET)		|
			((tempSpi & 1)				<< CPOL_OFFSET)		;
			
	SPSR |= ((tempSpi & (1<<5)) << SPI2X_OFFSET);
	
	(tempSpi & (1<<2)) ? (spiPinInitMaster()) : (spiPinInitSlave());
}

void spiSendByte(spi_t* pSpi, unsigned char data)
{
	unsigned char tempSpi;
	memcpy(&tempSpi, pSpi, sizeof(tempSpi));
	
	(tempSpi & (1<<2)) ? (ENABLE_SPI_CE) : (DISABLE_SPI_CE);	
	
	SPDR = data;
	while(SPSR & SPI_COMPLETED);
}

void spiRecvByte(spi_t* pSpi, unsigned char* pByte)
{
	while(SPI_PIN & (1<<SPI_CE_OFFSET));
	while(SPSR & SPI_COMPLETED);
	*pByte = SPDR;
	DISABLE_SPI_CE;
}

void spiSendBuffer(spi_t* pSpi, unsigned char* pBuf, unsigned int bufSize)
{
	while(bufSize--)
	{
		spiSendByte(pSpi, *pBuf++);
	}
}