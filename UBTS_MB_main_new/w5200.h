
#ifndef W5200_H_
#define W5200_H_

#include "defines.h"
//#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "w5200_defines.h"
#include "spi.h"
#include "usart.h"
#include "structures.h"
#include "utils.h"


extern uint8_t buffer_gate[];
extern uint8_t buffer_mask[];
extern uint8_t buffer_ip[];
extern uint8_t buffer_SOCKET_main[];
extern uint8_t buffer_mac[6];								//ff-ff-ff-ff-ff-ff-ff-ff
extern uint16_t animePause;
extern uint8_t *pGate, *pMask, *pIp;

void w5200_readData(uint16_t addr,uint16_t length,uint8_t* buffer);
void w5200_writeData(uint16_t addr,uint16_t length,uint8_t* buff);
void w5200_writeByte(uint16_t addr, uint8_t data);
uint8_t w5200_readByte(uint16_t addr);
void w5200_recvDataFifo(uint8_t ch,fifo_t *fifo);
void w5200_recvDataFifoUDP(uint8_t ch,fifo_t *fifo);
void w5200_sendDataFifoUDP(uint8_t ch, fifo_t *buff, fifo_t *addr);
void w5200_sendDataFifo(uint8_t ch,fifo_t *buff);
uint16_t getSn_RegValue(uint16_t reg);
uint16_t w5200_recvData(uint8_t ch,uint8_t *);
extern void readSpiSendUart(USART_t* usart, uint8_t length, uint8_t* buffer, uint16_t addr);
void w5200_init(void);


uint8_t w5200_readStatus(uint8_t ch);
uint8_t w5200_readSn_IR(uint8_t ch);
uint8_t w5200_readInterChann();
uint8_t w5200_readInterrupt();
void w5200_openSocket(uint8_t ch);
void w5200_closeSocket(uint8_t ch);
void w5200_discSocket(uint8_t ch);




#endif /* W5200_H_ */