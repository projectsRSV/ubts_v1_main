#include "w5200.h"

void w5200_init(void){
	uint8_t reset = 0x80;
	uint8_t IMR = 0x1f;
	//uint8_t buffer_RTR[]={0x01,0xe8};
	//uint8_t buffer_RCR[]={0x08};
	uint8_t IMR2 = 0x00;
	uint8_t MR_TCP = 0x01;
	uint8_t MR_UDP = 0x02 | 0x00;
	
	//uint8_t buffer_INTLEVEL[]={0x00,0x64};
	
	uint8_t buffer_MAC[] = {0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa};
	//uint8_t	bufferGroupMac[]={0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	//uint8_t	bufferUdpDestinIp[] = {192, 168, 6, 145};

	uint8_t	buffer_GATE_def[] = {192,168,6,1};
	uint8_t	buffer_SUB_def[] = {255,255,255,0};
	uint8_t	buffer_IP_source_def[] = {192, 168, 6, 10};
	
	uint8_t buffer_SOCKET_main[] = {0x13,0x88};					//5000
	uint8_t buffer_SOCKET_debug[] = {0x13,0x89};				//5001
	uint8_t buffer_SOCKET_gps[] = {0x0f,0xa0};					//4000
	uint8_t buffer_SOCKET_nm[] = {0x17,0x70};					//6000
	uint8_t buffer_SOCKET_UDP[] = {0x1b,0x58};					//7000	-	UDP
	
	//_delay_ms(1);
	w5200_writeData(MR_W5200, 1, &reset);						//reset
	_delay_ms(1);
	w5200_writeData(IMR_W5200, 1, &IMR);
	w5200_writeData(IMR2_W5200, 1, &IMR2);
	w5200_writeData(PHY_STATUS, 1, &IMR2);
	w5200_writeData(MAC, 6, buffer_MAC);						//set mac address
	//w5200_writeData(0x3031,2,buffer_INTLEVEL);
	//w5200_writeData(RTR_W5200,2,buffer_RTR);
	//w5200_writeData(RCR_W5200,2,buffer_RCR);
	
	if (buffer_IP_source[0] == 0xff){
		pGate = buffer_GATE_def;
		pSub = buffer_SUB_def;
		pIpSource = buffer_IP_source_def;
	}

	w5200_writeData(GATEWAY, 4, pGate);
	w5200_writeData(SUBNET, 4, pSub);
	w5200_writeData(IP_source, 4, pIpSource);

	w5200_writeData(Sn_MR(NM_CH), 1, &MR_TCP);							//0x01 set TCP mode
	w5200_writeData(Sn_PORT(NM_CH), 2, buffer_SOCKET_nm);				//set source port number (socket)
	
	w5200_writeData(Sn_MR(MAIN_CH),1,&MR_TCP);							//0x01 set TCP mode
	w5200_writeData(Sn_PORT(MAIN_CH), 2, buffer_SOCKET_main);			//set source port number (socket)
	
	w5200_writeData(Sn_MR(DEBUG_CH), 1, &MR_TCP);						//0x01 set TCP mode
	w5200_writeData(Sn_PORT(DEBUG_CH), 2, buffer_SOCKET_debug);			//set source port number (socket)
	
	w5200_writeData(Sn_MR(GPS_CH), 1, &MR_TCP);							//0x01 set TCP mode
	w5200_writeData(Sn_PORT(GPS_CH), 2, buffer_SOCKET_gps);				//set source port number (socket)
	
	w5200_writeData(Sn_MR(UDP_CH), 1, &MR_UDP);							//0x02 set UDP mode
	w5200_writeData(Sn_DPORT0(UDP_CH), 2, buffer_SOCKET_UDP);			//set destination port number (socket)
	w5200_writeData(Sn_PORT(UDP_CH), 2, buffer_SOCKET_UDP);				//set source port number (socket)
	//w5200_writeData(Sn_DIRP0(UDP_CH), 4, bufferUdpDestinIp);			//set destination ip for udp
	
	w5200_openSocket(MAIN_CH);
	w5200_openSocket(DEBUG_CH);
	w5200_openSocket(GPS_CH);
	w5200_openSocket(NM_CH);
	w5200_openSocket(UDP_CH);
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
		buff->data[buff->head++]=spi_sendData(&SPIE,0x00);
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
void w5200_writeDataFifo(uint16_t addr,uint16_t length,fifo_t* buff){
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
	CS_ON;
	spi_sendData(&SPIE,(addr)>>8);				//addr upper byte
	spi_sendData(&SPIE,addr);					//addr lower byte
	spi_sendData(&SPIE,(_READ));				//data length upper byte
	spi_sendData(&SPIE,(0x01));					//data length lower byte
	uint8_t data=spi_sendData(&SPIE,0x00);
	CS_OFF;
	return data;
}
uint16_t getSn_RegValue(uint16_t reg){
	uint16_t val=0,val1=0;
	do
	{
		val = w5200_readByte(reg);
		val = (val << 8) + w5200_readByte(reg + 1);
		if (val != 0){
			val1 = w5200_readByte(reg);
			val1 = (val1 << 8) + w5200_readByte(reg + 1);
		}
	} while (val != val1);
	return val;
}
void w5200_sendData(uint8_t ch,uint8_t *buff, uint16_t length){
	uint16_t ptr;
	uint16_t upperSizeByte;
	uint16_t dst_ptr;
	uint16_t dst_mask;
	
	ptr=getSn_RegValue(Sn_TX_WR(ch));
	dst_mask=ptr & BUFFER_MASK;
	dst_ptr = TX_BASE_ADDR(ch) + dst_mask;								//physical start address
	
	if( ((uint32_t)dst_mask + length) > (BUFFER_MASK+1)){
		upperSizeByte = (BUFFER_MASK+1) - dst_mask;
		w5200_writeData(dst_ptr,upperSizeByte,buff);
		buff += upperSizeByte;
		upperSizeByte = length - upperSizeByte;
		dst_ptr = TX_BASE_ADDR(ch);										//physical base start address
		w5200_writeData(dst_ptr,upperSizeByte,buff);
	}
	else{
		w5200_writeData(dst_ptr,length,buff);
	}
	ptr +=length;
	w5200_writeByte(Sn_TX_WR(ch),ptr>>8);
	w5200_writeByte(Sn_TX_WR(ch) + 1,ptr);
	w5200_writeByte(Sn_CR(ch),0x20);									//send command
}
void w5200_sendDataFifo(uint8_t ch,fifo_t *buff){
	uint16_t ptr;
	uint16_t upperSizeByte;
	uint16_t dst_ptr;
	uint16_t dst_mask;
	uint16_t length = (buff->head - buff->tail) & 0x00ff;
	
	ptr = getSn_RegValue(Sn_TX_WR(ch));
	dst_mask = ptr & BUFFER_MASK;
	dst_ptr = TX_BASE_ADDR(ch) + dst_mask;								//physical start address
	
	if( ((uint32_t)dst_mask + length) > (BUFFER_MASK+1)){
		upperSizeByte = (BUFFER_MASK+1) - dst_mask;
		w5200_writeDataFifo(dst_ptr,upperSizeByte,buff);
		//buff += upperSizeByte;
		upperSizeByte = length - upperSizeByte;
		dst_ptr = TX_BASE_ADDR(ch);										//physical base start address
		w5200_writeDataFifo(dst_ptr,upperSizeByte,buff);
	}
	else{
		w5200_writeDataFifo(dst_ptr,length,buff);
	}
	ptr +=length;
	w5200_writeByte(Sn_TX_WR(ch),ptr>>8);
	w5200_writeByte(Sn_TX_WR(ch) + 1,ptr);
	w5200_writeByte(Sn_CR(ch),0x20);									//send command
}
uint16_t w5200_recvData(uint8_t ch,uint8_t *buff){
	uint16_t ptr;
	uint16_t length;
	uint16_t upperSizeByte;
	uint16_t src_ptr;
	uint16_t src_mask;

	length=getSn_RegValue(Sn_RX_RSR(ch));
	ptr=getSn_RegValue(Sn_RX_RD(ch));
	src_mask=ptr & BUFFER_MASK;
	src_ptr = RX_BASE_ADDR(ch) + src_mask;								//physical start address
	if( (src_mask + length) > (BUFFER_MASK+1)){
		upperSizeByte = (BUFFER_MASK+1) - src_mask;
		w5200_readData(src_ptr,upperSizeByte,buff);
		buff += upperSizeByte;
		upperSizeByte = length - upperSizeByte;
		src_ptr = RX_BASE_ADDR(ch);										//physical start address
		w5200_readData(src_ptr,upperSizeByte,buff);
	}
	else{
		w5200_readData(src_ptr,length,buff);
	}
	
	ptr +=length;
	w5200_writeByte(Sn_RX_RD(ch),ptr>>8);
	w5200_writeByte(Sn_RX_RD(ch) + 1,ptr);
	w5200_writeByte(Sn_CR(ch),0x40);									//receive command
	return length;
}
void w5200_recvDataFifo(uint8_t ch,fifo_t *fifo){
	uint16_t ptr;
	uint16_t length;
	uint16_t upperSizeByte;
	uint16_t src_ptr;
	uint16_t src_mask;

	length=getSn_RegValue(Sn_RX_RSR(ch));
	ptr=getSn_RegValue(Sn_RX_RD(ch));
	src_mask=ptr & BUFFER_MASK;
	src_ptr = RX_BASE_ADDR(ch) + src_mask;								//physical start address
	if( (src_mask + length) > (BUFFER_MASK+1)){
		upperSizeByte = (BUFFER_MASK+1) - src_mask;
		w5200_readDataFifo(src_ptr,upperSizeByte,fifo);
		upperSizeByte = length - upperSizeByte;
		src_ptr = RX_BASE_ADDR(ch);										//physical start address
		w5200_readDataFifo(src_ptr,upperSizeByte,fifo);
	}
	else{
		w5200_readDataFifo(src_ptr,length,fifo);
	}
	
	ptr +=length;
	w5200_writeByte(Sn_RX_RD(ch),ptr>>8);
	w5200_writeByte(Sn_RX_RD(ch) + 1,ptr);
	w5200_writeByte(Sn_CR(ch),0x40);									//receive command
}
void w5200_closeSocket(uint8_t ch){
	w5200_writeByte(Sn_CR(ch),0x10);									//close command
}
void w5200_discSocket(uint8_t ch){
	w5200_writeByte(Sn_CR(ch),0x08);									//disconnect command
}
void w5200_openSocket(uint8_t ch){
	w5200_writeByte(Sn_CR(ch),0x01);									//open command
	w5200_writeByte(Sn_CR(ch),0x02);									//listen command
}
uint8_t w5200_readSocketInt(uint8_t ch){
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
void w5200_sendDataPGM(uint8_t ch,const uint8_t *buff){
	uint8_t temp;
	while(pgm_read_byte(buff)){
		temp=pgm_read_byte(buff++);
		FIFO_mainChTx.data[FIFO_mainChTx.head++]=temp;
		//FIFO_mainChTx.head &= BUFFER_SIZE-1;
	}
	w5200_sendDataFifo(ch,&FIFO_mainChTx);
}
void readSpiSendUart(USART_t* usart, uint8_t length, uint8_t* buff, uint16_t addr){
	w5200_readData(addr,length,buff);
	usart_sendDataToAscii(usart,length,buff);
	usart_sendData(&USARTE0,(uint8_t*)"\n",1);
}