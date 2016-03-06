/*
 * spi_config.h
 *
 * Created: 2/10/2016 1:35:06 PM
 *  Author: Mostafa El-Koumy
 */ 


#ifndef SPI_CONFIG_H_
#define SPI_CONFIG_H_

#include <avr/io.h>

/* CE pin */
#define SPI_PORT			PORTB
#define SPI_DDR				DDRB
#define SPI_PIN				PINB
#define SPI_CE_OFFSET		4

#define SPI_MOSI_OFFSET		5
#define SPI_MISO_OFFSET		6
#define SPI_SCK_OFFSET		7


#endif /* SPI_CONFIG_H_ */