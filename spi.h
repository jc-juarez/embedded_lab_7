/*
 * spi.c
 *
 * Created: 11/5/2022 18:05:48
 *  Author: jcjua
 */ 

#ifndef SPI_H_
#define SPI_H_

#define BAUDRATE 9600

void spiInit( void );
uint8_t spiSend( uint8_t data );

#endif /* SPI_H_ */