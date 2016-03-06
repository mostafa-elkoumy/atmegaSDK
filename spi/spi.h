/*
 * spi.h
 *
 * Created: 2/10/2016 1:34:51 PM
 *  Author: Mostafa El-Koumy
 */ 


#ifndef SPI_H_
#define SPI_H_

#include "spi_config.h"

typedef struct
{
	unsigned char clkPol	: 1;
	unsigned char clkPh		: 1;
	unsigned char opMode	: 1;
	unsigned char clkDiv	: 3;
	unsigned char dataOrder	: 1;
	unsigned char interuptEn  : 1; 
}spi_t;

/* CE Configuration */
inline void spiPinInitMaster(void)
{
	SET_BIT(SPI_DDR, SPI_CE_OFFSET); 
	SET_BIT(SPI_DDR, SPI_MOSI_OFFSET);
	SET_BIT(SPI_DDR, SPI_SCK_OFFSET);
	CLR_BIT(SPI_DDR, SPI_MISO_OFFSET);
}
							
inline void spiPinInitSlave(void)
{
	CLR_BIT(SPI_DDR, SPI_CE_OFFSET);
	CLR_BIT(SPI_DDR, SPI_MOSI_OFFSET);
	CLR_BIT(SPI_DDR, SPI_SCK_OFFSET); 
	SET_BIT(SPI_DDR, SPI_MISO_OFFSET);
}
#define ENABLE_SPI_CE		CLR_BIT(SPI_PORT, SPI_CE_OFFSET)
#define DISABLE_SPI_CE		SET_BIT(SPI_PORT, SPI_CE_OFFSET)

/*SPCR */

#define SPIE_OFFSET		7
#define SPE_OFFSET		6
#define DORD_OFFSET		5
#define MSTR_OFFSET		4
#define CPOL_OFFSET		3
#define CPHA_OFFSET		2
#define SPR_OFFSET		0

/* SPSR */
#define SPIF_OFFSET		7
#define WCOL_OFFSET		6
#define SPI2X_OFFSET	0


/* SPCR values */
#define DORD_MSB		0
#define DORD_LSB		1

#define MODE_MASTER		1
#define MODE_SLAVE		0

#define CPOL_BASE0		0
#define CPOL_BASE1		1

#define CPHA_LEADING	0
#define CPHA_TRAILING	1

#define CLK_DIV_2		8
#define CLK_DIV_4		0
#define CLK_DIV_8		9
#define CLK_DIV_16		1
#define CLK_DIV_32		10
#define CLK_DIV_64		2
#define CLK_DIV_128		3

/* SPSR values */
#define SPI_COMPLETED	(1<<SPIF_OFFSET)


void spiInitialize(spi_t* pSpi);

void spiSendByte(spi_t* pSpi, unsigned char data);

void spiRecvByte(spi_t* pSpi, unsigned char* pByte);

void spiSendBuffer(spi_t* pSpi, unsigned char* pBuf, unsigned int bufSize);

#endif /* SPI_H_ */