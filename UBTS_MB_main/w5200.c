#include "w5200.h"

void w5200_init(void){
	uint8_t reset = 0x80;
	uint8_t IMR = 0x00;					//0x1f
	uint8_t buffer_RTR[] = {0x00,0xff};
	uint8_t buffer_RCR[] = {0x02};
	uint8_t IMR2 = 0x00;
	uint8_t PHY = 0x00;
	uint8_t MR_TCP = 0x01;
	uint8_t MR_UDP = 0x02 | 0x00;
	
	//uint8_t buffer_INTLEVEL[]={0x00,0xff};
	
	//uint8_t buffer_MAC[] = {0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa};

	uint8_t	buffer_GATE_def[] = {192,168,6,1};
	uint8_t	buffer_SUB_def[] = {255,255,255,0};
	uint8_t	buffer_IP_source_def[] = {192, 168, 6, 10};
	//uint8_t	buffer_IP_destUDP[] = {192, 168, 6, 41};
	
	
	uint8_t buffer_SOCKET_main[] = {MAIN_PORT >> 8, (uint8_t)MAIN_PORT};					//5000
	uint8_t buffer_SOCKET_debug[] = {DEBUG_POR >> 8, (uint8_t)DEBUG_POR};					//5001
	uint8_t buffer_SOCKET_gps[] = {GPS_PORT >> 8, (uint8_t)GPS_PORT};						//4000
	uint8_t buffer_SOCKET_nm[] = {NM_PORT >> 8, (uint8_t)NM_PORT};							//6000
	
	_delay_ms(1);
	w5200_writeData(MR_W5200, 1, &reset);						//reset
	_delay_ms(200);
	
	w5200_writeData(IMR_W5200, 1, &IMR);
	w5200_writeData(IMR2_W5200, 1, &IMR2);
	w5200_writeData(PHY_STATUS, 1, &PHY);
	
	w5200_writeData(MAC, 6, buffer_mac);						//set mac address
	//w5200_writeData(INT_W5200, 2, buffer_INTLEVEL);
	w5200_writeData(RTR_W5200,2,buffer_RTR);
	w5200_writeData(RCR_W5200,2,buffer_RCR);
	
	if (buffer_ip[0] == 0xff){
		pGate = buffer_GATE_def;
		pMask = buffer_SUB_def;
		pIp = buffer_IP_source_def;
	}

	w5200_writeData(GATEWAY, 4, pGate);
	w5200_writeData(SUBNET, 4, pMask);
	w5200_writeData(IP_source, 4, pIp);

	w5200_writeData(Sn_MR(NM_CH), 1, &MR_TCP);							//0x01 set TCP mode
	w5200_writeData(Sn_PORT(NM_CH), 2, buffer_SOCKET_nm);				//set source port number (socket)
	
	w5200_writeData(Sn_MR(MAIN_CH),1,&MR_TCP);							//0x01 set TCP mode
	w5200_writeData(Sn_PORT(MAIN_CH), 2, buffer_SOCKET_main);			//set source port number (socket)
	
	w5200_writeData(Sn_MR(DEBUG_CH), 1, &MR_TCP);						//0x01 set TCP mode
	w5200_writeData(Sn_PORT(DEBUG_CH), 2, buffer_SOCKET_debug);			//set source port number (socket)
	
	w5200_writeData(Sn_MR(GPS_CH), 1, &MR_TCP);							//0x01 set TCP mode
	w5200_writeData(Sn_PORT(GPS_CH), 2, buffer_SOCKET_gps);				//set source port number (socket)
	
	w5200_writeData(Sn_MR(UDP_CH), 1, &MR_UDP);							//0x02 set UDP mode
	w5200_writeData(Sn_PORT(UDP_CH), 2, buffer_SOCKET_main);			//set source port number (socket)
	
	w5200_writeData(Sn_DPORT0(UDP_CH), 2, buffer_SOCKET_main);			//set destination port number (socket)
	//w5200_writeData(Sn_DIPR0(UDP_CH), 4, pIp);						//set destination ip for udp
	//w5200_writeData(Sn_DIPR0(UDP_CH), 4, buffer_IP_destUDP);			//set destination ip for udp
}

void w5200_readData(uint16_t addr,uint16_t length, uint8_t* buff){
	CS_ON;
	spi_sendData(&SPIE,(addr)>>8);					//addr upper byte
	spi_sendData(&SPIE,(addr));						//addr lower byte
	spi_sendData(&SPIE,_READ|(length>>8));			//data length upper byte
	spi_sendData(&SPIE,(length));					//data length lower byte
	for (uint16_t i=0;i<length;i++){
		buff[i]=spi_sendData(&SPIE,0x00);
	}
	CS_OFF;
}
void w5200_readDataFifo(uint16_t addr,uint16_t length,fifo_t* buff){
	CS_ON;
	spi_sendData(&SPIE,(addr)>>8);					//addr upper byte
	spi_sendData(&SPIE,(addr));						//addr lower byte
	spi_sendData(&SPIE,_READ|(length>>8));			//data length upper byte
	spi_sendData(&SPIE,(length));					//data length lower byte
	for (uint16_t i=0;i<length;i++){
		buff->data[buff->head++] = spi_sendData(&SPIE,0x00);
		//buff->head &=(BUFFER_SIZE-1);
	}
	CS_OFF;
}
void w5200_writeData(uint16_t addr, uint16_t length, uint8_t* buff){
	CS_ON;
	spi_sendData(&SPIE,(addr)>>8);				//addr upper byte
	spi_sendData(&SPIE,addr);					//addr lower byte
	spi_sendData(&SPIE,(_WRITE)|(length>>8));	//data length upper byte
	spi_sendData(&SPIE,(length));				//data length lower byte
	for (uint16_t i=0;i<length;i++){
		spi_sendData(&SPIE,buff[i]);
	}
	CS_OFF;
}
void w5200_writeDataFifo(uint16_t addr, uint16_t length, fifo_t* buff){
	CS_ON;
	spi_sendData(&SPIE,(addr)>>8);				//addr upper byte
	spi_sendData(&SPIE,addr);					//addr lower byte
	spi_sendData(&SPIE,(_WRITE)|(length>>8));	//data length upper byte
	spi_sendData(&SPIE,(length));				//data length lower byte
	for (uint8_t i=0; i<length; i++){
		//usart_putChar(&USARTE0, buff->data[buff->tail]);
		spi_sendData(&SPIE, buff->data[buff->tail++]);
		//buff->tail &=BUFFER_SIZE-1;
	}
	CS_OFF;
}
void w5200_writeByte(uint16_t addr, uint8_t data){
	CS_ON;
	spi_sendData(&SPIE,(addr)>>8);				//addr upper byte
	spi_sendData(&SPIE,addr);					//addr lower byte
	spi_sendData(&SPIE,(_WRITE));				//data length upper byte
	spi_sendData(&SPIE,(0x01));					//data length lower byte
	spi_sendData(&SPIE,data);
	CS_OFF;
}
uint8_t w5200_readByte(uint16_t addr){
	uint8_t data = 0;
	CS_ON;
	spi_sendData(&SPIE,(addr)>>8);				//addr upper byte
	spi_sendData(&SPIE,addr);					//addr lower byte
	spi_sendData(&SPIE,(_READ));				//data length upper byte
	spi_sendData(&SPIE,(0x01));					//data length lower byte
	data = spi_sendData(&SPIE,0x00);
	CS_OFF;
	return data;
}
uint16_t getSn_RegValue(uint16_t reg){
	uint16_t val=0, val1 = 0;
	do
	{
		val = w5200_readByte(reg) << 8;
		val |= w5200_readByte(reg + 1);
		if (val != 0){
			val1 = w5200_readByte(reg) << 8;
			val1 |= w5200_readByte(reg + 1);
		}
	} while (val != val1);
	return val;
}
void w5200_sendDataFifo(uint8_t ch, fifo_t *buff){
	uint16_t ptr;
	uint16_t upperSizeByte;
	uint16_t dst_ptr;
	uint16_t dst_mask;
	uint16_t length = (buff->head - buff->tail) & 0xff;
	
	if (length > 0){
		while (getSn_RegValue(Sn_TX_FSR(ch)) < length){};

		dst_mask = getSn_RegValue(Sn_TX_WR(ch)) & RX_MASK;
		dst_ptr = TX_BASE(ch) + dst_mask;								//physical start address
		

		if( (dst_mask + length) > (RX_MASK + 1)){
			upperSizeByte = (RX_MASK + 1) - dst_mask;
			w5200_writeDataFifo(dst_ptr, upperSizeByte, buff);
			upperSizeByte = length - upperSizeByte;
			//dst_ptr = TX_BASE(ch);										//physical base start address
			w5200_writeDataFifo(TX_BASE(ch), upperSizeByte, buff);
		}
		else{
			w5200_writeDataFifo(dst_ptr, length, buff);
		}
		ptr = getSn_RegValue(Sn_TX_WR(ch)) + length;
		
		w5200_writeByte(Sn_TX_WR(ch), ptr >> 8);
		w5200_writeByte(Sn_TX_WR(ch) + 1, ptr);
		w5200_writeByte(Sn_CR(ch), _SEND_COMMAND);								//send command
		//_delay_ms(2);
	}
}
void w5200_sendDataFifoUDP(uint8_t ch, fifo_t *buff, fifo_t *addr){
	uint16_t ptr;
	uint16_t upperSizeByte;
	uint16_t dst_ptr;
	uint16_t dst_mask;
	uint16_t length = (buff->head - buff->tail) & 0xff;
	
	if (length > 0 && (FIFO_udpIp.head - FIFO_udpIp.tail) != 0){
		while (getSn_RegValue(Sn_TX_FSR(ch)) < length){};

		dst_mask = getSn_RegValue(Sn_TX_WR(ch)) & RX_MASK;
		dst_ptr = TX_BASE(ch) + dst_mask;								//physical start address
		
		w5200_writeDataFifo(Sn_DIPR0(ch), 4, addr);				//set destination ip for udp

		if( (dst_mask + length) > (RX_MASK + 1)){
			upperSizeByte = (RX_MASK + 1) - dst_mask;
			w5200_writeDataFifo(dst_ptr, upperSizeByte, buff);
			upperSizeByte = length - upperSizeByte;
			//dst_ptr = TX_BASE(ch);									//physical base start address
			w5200_writeDataFifo(TX_BASE(ch), upperSizeByte, buff);
		}
		else{
			w5200_writeDataFifo(dst_ptr, length, buff);
		}
		ptr = getSn_RegValue(Sn_TX_WR(ch)) + length;
		
		w5200_writeByte(Sn_TX_WR(ch), ptr >> 8);
		w5200_writeByte(Sn_TX_WR(ch) + 1, ptr);
		w5200_writeByte(Sn_CR(ch), _SEND_COMMAND);								//send command
		//_delay_ms(2);
	}
}
void w5200_recvDataFifo(uint8_t ch,fifo_t *fifo){
	uint16_t ptr;
	uint16_t length;
	uint16_t upperSizeByte;
	uint16_t src_ptr;
	uint16_t src_mask;

	length = getSn_RegValue(Sn_RX_RSR(ch));
	
	if (length > 0){
		src_mask = getSn_RegValue(Sn_RX_RD(ch)) & RX_MASK;
		src_ptr = RX_BASE(ch) + src_mask;								//physical start address
		
		if((src_mask + length) > (RX_MASK + 1)){
			upperSizeByte = (RX_MASK + 1) - src_mask;
			w5200_readDataFifo(src_ptr, upperSizeByte, fifo);
			upperSizeByte = length - upperSizeByte;
			//src_ptr = RX_BASE(ch);										//physical start address
			w5200_readDataFifo(RX_BASE(ch), upperSizeByte, fifo);
		}
		else{
			w5200_readDataFifo(src_ptr, length, fifo);
		}
		ptr = getSn_RegValue(Sn_RX_RD(ch)) + length;
		
		w5200_writeByte(Sn_RX_RD(ch), ptr >> 8);
		w5200_writeByte(Sn_RX_RD(ch) + 1, ptr);
		w5200_writeByte(Sn_CR(ch), _RECV_COMMAND);							//receive command
	}
}
void w5200_recvDataFifoUDP(uint8_t ch,fifo_t *fifo){
	uint16_t ptr;
	uint16_t length;
	uint16_t upperSizeByte;
	uint16_t src_ptr;
	uint16_t src_mask;
	//uint8_t startSourceIp;
	
	//startSourceIp = fifo->head;

	length = getSn_RegValue(Sn_RX_RSR(ch));
	
	if (length > 0){
		src_mask = getSn_RegValue(Sn_RX_RD(ch)) & RX_MASK;
		src_ptr = RX_BASE(ch) + src_mask;									//physical start address
		
		if((src_mask + length) > (RX_MASK + 1)){
			upperSizeByte = (RX_MASK + 1) - src_mask;
			w5200_readDataFifo(src_ptr, upperSizeByte, fifo);
			upperSizeByte = length - upperSizeByte;
			w5200_readDataFifo(RX_BASE(ch), upperSizeByte, fifo);
		}
		else{
			w5200_readDataFifo(src_ptr, length, fifo);
		}
		ptr = getSn_RegValue(Sn_RX_RD(ch)) + length;
		
		w5200_writeByte(Sn_RX_RD(ch), ptr >> 8);
		w5200_writeByte(Sn_RX_RD(ch) + 1, ptr);
		w5200_writeByte(Sn_CR(ch), _RECV_COMMAND);								//receive command
		
		/*for (uint8_t i=0; i<4; i++){
			FIFO_udpIp.data[FIFO_udpIp.head++] = fifo->data[startSourceIp++];
		}*/
	}
}
void w5200_closeSocket(uint8_t ch){
	w5200_writeByte(Sn_CR(ch), 0x10);											//close command
	_delay_ms(1);
}
void w5200_discSocket(uint8_t ch){
	w5200_writeByte(Sn_CR(ch), _DISCONNECT_COMMAND);
	//if (w5200_readStatus(ch) == _SOCK_CLOSED) w5200_writeByte(Sn_CR(ch), _CLOSE_COMMAND);		//close
}

void w5200_openSocket(uint8_t ch){
	uint8_t temp;
	
	w5200_writeByte(Sn_CR(ch), _OPEN_COMMAND);															//open
	temp = w5200_readStatus(ch);
	switch(temp){
		case _SOCK_INIT:{
			w5200_writeByte(Sn_CR(ch), _LISTEN_COMMAND);												//listen
			temp = w5200_readStatus(ch);
			if (temp != _SOCK_LISTEN) w5200_writeByte(Sn_CR(ch), _CLOSE_COMMAND);						//close
			break;
		}
		case _SOCK_UDP:{
			break;
		}
		case _SOCK_LISTEN:{
			break;
		}
		default:{
			w5200_writeByte(Sn_CR(ch), _CLOSE_COMMAND);													//close
			break;
		}
	}
}

uint8_t w5200_readSn_IR(uint8_t ch){
	return w5200_readByte(Sn_IR(ch));
}
uint8_t w5200_readInterChann(){
	return w5200_readByte(IR2_W5200);
}
uint8_t w5200_readInterrupt(){
	return w5200_readByte(IR_W5200);
}
uint8_t w5200_readStatus(uint8_t ch){
	return w5200_readByte(Sn_SR(ch));
}
void readSpiSendUart(USART_t* usart, uint8_t length, uint8_t* buff, uint16_t addr){
	w5200_readData(addr, length, buff);
	usart_sendDataToAscii(usart, length, buff);
	usart_sendData(&USARTE0, (uint8_t*)"\n", 1);
}
