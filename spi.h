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
uint32_t spiXchg(const uint8_t * send_buff, uint32_t bc, uint8_t * receive_buff );

#endif /* SPI_H_ */