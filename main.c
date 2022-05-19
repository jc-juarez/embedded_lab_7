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


void initCycles(void);
#define SIZE_SD_CMD 0x06
#define RXBUFSIZE 0x400
const uint8_t CMD00[SIZE_SD_CMD] ={0x40, 0x00, 0x00, 0x00, 0x00, 0x95};
const uint8_t CMD08[SIZE_SD_CMD] ={0x48, 0x00, 0x00, 0x01, 0xAA, 0x87};
uint8_t CMD17[SIZE_SD_CMD] ={0x51, 0x00, 0x00, 0x00, 0x00, 0x01};
uint8_t CMD172[SIZE_SD_CMD] ={0x51, 0x00, 0x00, 0x08, 0x00, 0x01};
const uint8_t CMD18[SIZE_SD_CMD] ={0x52, 0x00, 0x00, 0x00, 0x00, 0x01};
const uint8_t CMD55[SIZE_SD_CMD] ={0x77, 0x00, 0x00, 0x00, 0x00, 0x65};
const uint8_t CMD41[SIZE_SD_CMD] = {0x69, 0x40, 0x00, 0x00, 0x00, 0x77};
uint8_t RxBuffer[RXBUFSIZE];
int main(void)
{
	//uint32_t temp = 0xFF;
	/* Initialize the SAM system */
	SystemInit();
	UARTInit();
	spiInit();
	initCycles();
	myprintf("\n");
	spiXchg( CMD00, SIZE_SD_CMD, RxBuffer ); /* reset instruction */
	myprintf("\n");
	//Write your code here
 
	uint32_t sdReady = spiXchg( CMD08, SIZE_SD_CMD, RxBuffer );
	myprintf("\n");
	
	if (sdReady == 0){
		myprintf("\nError with SD card");
	}
	else{
		sdReady = 0;
		uint32_t sdReady2 = 0;
		
		while (sdReady2 == 0){
			sdReady = spiXchg( CMD55, SIZE_SD_CMD, RxBuffer );
			myprintf("\n");
			sdReady2 = spiXchg( CMD41, SIZE_SD_CMD, RxBuffer );
			myprintf("\n");
		}
		myprintf("\nSD card ready");
	}
	
	uint32_t addrSD = 0;
	uint32_t numBytes = 512;
	
	rcvr_datablock(CMD17, addrSD, RxBuffer, numBytes);
	
	
 
	myprintf("\nDone");
}
void initCycles(void){
uint32_t i;
REG_PORT_OUTSET0 = PORT_PA18;
REG_PORT_OUTSET0 = PORT_PA16;
for(i=0;i<76;i++)
spiSend(0xFF);
}

void rcvr_datablock(const uint8_t * send_buff, uint32_t lba, uint8_t * receive_buff, uint32_t bs ) {
	uint8_t temp = 0xFF;
	uint32_t i;
	
	REG_PORT_OUTCLR0 = PORT_PA18;
	myprintf("\n\n");
	
	temp = send_buff[0];
	temp = spiSend(temp);
	myprintf(" %x", temp); 
	temp = ((uint8_t*)&lba)[3];
	temp = spiSend(temp);
	myprintf(" %x", temp);
	
	// Complete the code that is missing
	temp = ((uint8_t*)&lba)[2];
	temp = spiSend(temp);
	myprintf(" %x", temp);
	temp = ((uint8_t*)&lba)[1];
	temp = spiSend(temp);
	myprintf(" %x", temp);
	temp = ((uint8_t*)&lba)[0];
	temp = spiSend(temp);
	myprintf(" %x", temp);
	
	temp = send_buff[5];
	temp = spiSend(temp);
	myprintf(" %x", temp);
	
	// Reading to find the beginning of the sector
	
	temp = spiSend(0xFF);
	while(temp != 0xFE){
		temp = spiSend(0xFF);
		myprintf(" %x", temp);
	}
	
	// Receiving the memory sector/block
	
	myprintf("\n\n");
	for(i=0; i< bs; i++) {
		while(SERCOM1->SPI.INTFLAG.bit.DRE == 0);
		SERCOM1->SPI.DATA.reg = 0xFF;
		while(SERCOM1->SPI.INTFLAG.bit.TXC == 0);
		while(SERCOM1->SPI.INTFLAG.bit.RXC == 0);
		temp = SERCOM1->SPI.DATA.reg;
		*(receive_buff++) = temp;
		myprintf(" %x", temp);
	}
	REG_PORT_OUTSET0 = PORT_PA18;
	myprintf("\n\n");
}