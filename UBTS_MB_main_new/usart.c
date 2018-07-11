#include "usart.h"


void usart_init(USART_t *usart, uint32_t baud){
	uint32_t cpu_hz=F_CPU;
	int8_t bscale=0;
	uint32_t bsel=0;
	uint32_t limit=0;
	uint32_t ratio=0;

	if (!((usart)->CTRLB & USART_CLK2X_bm)) {
		baud *= 2;
	}
	limit = 0xfffU >> 4;;
	ratio = cpu_hz / baud;
	for (bscale = -7; bscale < 7; bscale++) {
		if (ratio < limit)	break;
		limit <<= 1;
		if (bscale < -3) {
			limit |= 1;
		}
	}
	if(bscale<0){
		cpu_hz -=8*baud;
		if (bscale <= -3)		{
			bsel=((cpu_hz<<(-bscale-3))+baud/2)/baud;
		}
		else{
			baud<<=bscale+3;
			bsel=(cpu_hz+baud/2)/baud;
		}
	}
	else{
		baud <<= bscale + 3;
		bsel = (cpu_hz + baud / 2) / baud - 1;
	}

	usart->BAUDCTRLB=(uint8_t)(((bsel >> 8) & 0x0f) | (bscale<<4));
	usart->BAUDCTRLA=(uint8_t)bsel;
	if(usart==&USARTC0 || usart==&USARTE0) usart->CTRLA=USART_RXCINTLVL0_bm;
	else if(usart==&USARTD0) usart->CTRLA=USART_RXCINTLVL0_bm | USART_DREINTLVL0_bm;
	else usart->CTRLA=0;
	usart->CTRLC=USART_CHSIZE_8BIT_gc;
	usart->STATUS=0;
	
	usart_rx_enable(usart);
	usart_tx_enable(usart);
}
void usart_putChar(USART_t* usart, uint8_t c){
	while (usart_data_register_is_empty(usart) == false) {}
	usart->DATA = c;
	while (usart_tx_is_complete(usart) == false) {}
	usart_clear_tx_complete(usart);
}
uint8_t usart_getChar(USART_t* usart){
	while (usart_rx_is_complete(usart) == false) {}
	return usart->DATA;
}
void usart_sendData(USART_t* usart,uint8_t* buffer,uint8_t length){
	for (uint8_t i=0;i<length;i++){
		usart_putChar(usart,*buffer++);
	}
	//while(*buffer){
	//usart_putchar(usart,*buffer++);
	//}
}
void usart_sendDataFifo(USART_t* usart, fifo_t* fifo){
	while (fifo->head != fifo->tail){
		usart_putChar(usart, fifo->data[fifo->tail++]);
	}
}
void usart_sendDataPGM(USART_t* usart,const uint8_t* buffer){
	while(pgm_read_byte(buffer)){
		usart_putChar(usart,pgm_read_byte(buffer++));
	}
}

void usart_sendDataToAscii(USART_t* usart, uint16_t length, uint8_t* buffer){
	for (uint16_t i=0; i<length; i++){
		usart_sendData(usart,utils_hex8ToAscii16(*buffer++),2);
	}
	//usart_sendDataPGM(usart,_LINE_FEED);
}

/*
sendString("Hello World!\n\r");
void sendString(char *text)
{
while(*text)
{
sendChar(*text++);
}
}*/
