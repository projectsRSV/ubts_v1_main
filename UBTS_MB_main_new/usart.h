#ifndef _USART_H_
#define _USART_H_

//#include <avr/io.h>
#include <stdbool.h>
#include <avr/pgmspace.h>
#include "defines.h"
#include "utils.h"

void usart_init(USART_t *usart, uint32_t baud);
void usart_putChar(USART_t *usart,uint8_t c);
uint8_t usart_getChar(USART_t *usart);
void usart_sendData(USART_t * usart,uint8_t* buffer,uint8_t length);
void usart_sendDataPGM(USART_t* usart,const uint8_t* buffer);
void usart_sendDataToAscii(USART_t * usart, uint16_t length, uint8_t* buffer);
void usart_sendDataFifo(USART_t* usart, fifo_t* fifo);


static inline void usart_rx_enable(USART_t *usart){
	(usart)->CTRLB |= USART_RXEN_bm;
}

static inline void usart_rx_disable(USART_t *usart){
	(usart)->CTRLB &= ~USART_RXEN_bm;
}

static inline void usart_tx_enable(USART_t *usart){
	(usart)->CTRLB |= USART_TXEN_bm;
}

static inline void usart_tx_disable(USART_t *usart){
	(usart)->CTRLB &= ~USART_TXEN_bm;
}

static inline bool usart_data_register_is_empty(USART_t * usart){
	return (usart)->STATUS & USART_DREIF_bm;
}

static inline bool usart_rx_is_complete(USART_t * usart){
	return (usart)->STATUS & USART_RXCIF_bm;
}

static inline bool usart_tx_is_complete(USART_t * usart){
	return (usart)->STATUS & USART_TXCIF_bm;
}

static inline void usart_clear_tx_complete(USART_t * usart){
	(usart)->STATUS = USART_TXCIF_bm;
}

static inline void usart_clear_rx_complete(USART_t *usart){
	(usart)->STATUS = USART_RXCIF_bm;
}

static inline void usart_put(USART_t * usart, uint8_t txdata){
	(usart)->DATA = txdata;
}

static inline uint8_t usart_get(USART_t * usart){
	return (usart)->DATA;
}

#endif // _USART_H_
