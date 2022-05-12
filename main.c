/*
 * practice7.c
 *
 * Created: 11/5/2022 18:05:57
 * Author : jcjua
 */ 


#include "sam.h"
#include "spi.h"
#include "myprintf.h"
#include "uart.h"

int main(void)
{
	SystemInit();
	spiInit();
	UARTInit();
	volatile uint8_t rData;
	volatile uint8_t sData = 85;
	while (1) {
		REG_PORT_OUTCLR0 = PORT_PA18; //initiate transaction by SS_low
		rData = spiSend( sData );
		REG_PORT_OUTSET0 = PORT_PA18; //finish transaction by SS_high
	}
}
