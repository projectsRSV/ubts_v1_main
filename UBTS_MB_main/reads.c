#include "reads.h"



void read_commandUART() {
	static uint16_t i=0;
	if (i++ == 0x0fff) {
		//if (!utils_isFifoEmpty(&FIFO_recUART)) {
		command_exec(commands_decoder(&FIFO_recUART, &COMMAND));
		//}
		i=0;
	}
}
void read_adc() {
	static uint16_t i=0;
	if (i++ == 0x007f) {
		adc_readData(&_ADCB, ADC_CH_6);				//pa1 bw
		adc_readData(&_ADCB, ADC_CH_7);				//pa1 out
		adc_readData(&_ADCA, ADC_CH_2);				//pa2 out
		adc_readData(&_ADCA, ADC_CH_3);				//pa2 bw
		adc_readData(&_ADCA, ADC_CH_4);				//pa3 out
		adc_readData(&_ADCA, ADC_CH_5);				//pa3 bw
		//adc_readData(&_ADCA, ADC_CH_6);				//pa4 bw
		//adc_readData(&_ADCA, ADC_CH_7);				//pa4 out
		i=0;
	}
}

static void read_sendW5200State(uint8_t ch){
	uint8_t status;
	status = w5200_readStatus(ch);
	switch(status){
		case _SOCK_CLOSED:{
			utils_sendDebugPGM(DEBUG_CH, _CLOSE, 0, 0);
			w5200_openSocket(ch);
			if(ch == MAIN_CH) ISR_W5200.conMain = 0;
			else if(ch == DEBUG_CH) ISR_W5200.conDebug = 0;
			else if(ch == NM_CH) ISR_W5200.conNm = 0;
			else if(ch == GPS_CH) ISR_W5200.conGps = 0;
			break;
		}
		case _SOCK_LISTEN:{
			//blinkFuncPtr = (fpStatusLed)(blinkLedTable[2]);
			break;
		}
		case _SOCK_ESTABL:{
			if(ch == MAIN_CH) {
				if (ISR_W5200.conMain == 0) {
					ISR_W5200.conMain = 1;
					utils_sendDebugPGM(DEBUG_CH, _CONN_MAIN, 0, 0);
				}
				w5200_sendDataFifo(ch, &FIFO_mainChTx);
				w5200_recvDataFifo(ch, &FIFO_mainChRx);
			}
			else if(ch == GPS_CH) {
				if (ISR_W5200.conGps == 0) {
					ISR_W5200.conGps = 1;
					utils_sendDebugPGM(DEBUG_CH, _CONN_GPS, 0, 0);
				}
				if (((FIFO_gpsCh.head - FIFO_gpsCh.tail) & 0xff) >= 200){
					w5200_sendDataFifo(ch, &FIFO_gpsCh);
				}
			}
			else if(ch == DEBUG_CH) {
				if (ISR_W5200.conDebug == 0) {
					ISR_W5200.conDebug = 1;
					utils_sendDebugPGM(DEBUG_CH, _CONN_DEBUG, 0, 0);
				}
				w5200_sendDataFifo(ch, &FIFO_debugChTx);
				w5200_recvDataFifo(ch, &FIFO_debugChRx);
			}
			else if(ch == NM_CH) {
				if (ISR_W5200.conNm == 0) {
					ISR_W5200.conNm = 1;
					utils_sendDebugPGM(DEBUG_CH, _CONN_NM, 0, 0);
				}
				w5200_sendDataFifo(ch, &FIFO_nmChTx);
				w5200_recvDataFifo(ch, &FIFO_nmChTx);
			}
			break;
		}
		case _SOCK_UDP:{
			w5200_recvDataFifoUDP(ch, &FIFO_udpChRx);
			//w5200_sendDataFifoUDP(ch, &FIFO_udpChTx, &FIFO_udpIp);
			//w5200_sendDataFifoUDP(ch, &FIFO_udpChTx, &FIFO_udpIp);
			break;
		}
		case _SOCK_CLOSE_WAIT:{
			//blinkFuncPtr = (fpStatusLed)(blinkLedTable[0]);
			w5200_discSocket(ch);
			break;
		}
	}
}
void read_udpCommand(){
	static uint16_t i=0;
	if (i++ >= 0x00ff) {
		read_sendW5200State(UDP_CH);
		command_exec(commands_decoder(&FIFO_udpChRx, &COMMAND));
		i = 0;
	}
}
void read_sendGps() {
	static uint16_t i=0;
	if (i++ >= 0x00ef) {
		read_sendW5200State(GPS_CH);
		i = 0;
	}
}
void read_mainCommand() {
	static uint16_t i=0;
	if (i++ >= 0x01ff) {
		read_sendW5200State(MAIN_CH);
		command_exec(commands_decoder(&FIFO_mainChRx, &COMMAND));
		i=0;
	}
}
void read_debugCommand() {
	static uint16_t i=0;
	if (i++ >= 0x02ff) {
		read_sendW5200State(DEBUG_CH);
		command_exec(commands_decoder(&FIFO_debugChRx, &COMMAND));
		i=0;
	}
}
void read_nmCommand() {
	static uint8_t i=0;
	if (i++ >= 0x00df) {
		read_sendW5200State(NM_CH);
		if (!utils_isFifoEmpty(&FIFO_nmChRx)) {
			USARTD0.CTRLA |= USART_DREINTLVL0_bm;
		}
		i=0;
	}
}
uint8_t read_eeprByte(uint16_t addr) {
	cli();
	uint8_t temp;
	EEPROM_DisableMapping();
	temp = EEPROM_ReadByte(EEPR_PAGE_ADDR_start, addr);
	EEPROM_EnableMapping();
	sei();
	return temp;
}
void read_eeprBuff(uint16_t addr,uint8_t* buff, uint8_t length) {
	cli();
	EEPROM_DisableMapping();
	for (uint8_t i=0; i<length; i++) {
		//buff[i]=eeprom_read_byte((uint8_t*)(addr+i));
		buff[i]=EEPROM_ReadByte(EEPR_PAGE_ADDR_start, addr+i);
	}
	EEPROM_EnableMapping();
	sei();
}
void read_writeEEPROMByte(uint16_t addr, uint8_t byte) {
	cli();
	EEPROM_DisableMapping();
	EEPROM_WriteByte(EEPR_PAGE_ADDR_start, addr, byte);
	EEPROM_EnableMapping();
	sei();
}
void read_writeEEPROMBuff(uint16_t addr, uint8_t* buff, uint8_t length) {
	cli();
	EEPROM_DisableMapping();
	for (uint8_t i=0; i<length; i++) {
		EEPROM_WriteByte(EEPR_PAGE_ADDR_start, addr+i , buff[i]);
	}
	EEPROM_EnableMapping();
	sei();
}
void read_eeprom() {
	read_eeprBuff(SERIAL_NUM, buffer_serialNum, 4);
	read_eeprBuff(IP_SOURCE, buffer_ip, 4);
	read_eeprBuff(SUBNET_MASK, buffer_mask, 4);
	read_eeprBuff(GATEWAY_ADDR, buffer_gate, 4);
	read_eeprBuff(SOCKET+1, &buffer_SOCKET_main[0], 1);
	read_eeprBuff(SOCKET, &buffer_SOCKET_main[1], 1);
	/*read_eeprBuff(LENGTH_3d,&COMMAND_3d.length,1);
	read_eeprBuff(STRING_3d,COMMAND_3d.buffer,COMMAND_3d.length);
	read_eeprBuff(LENGTH_21,&COMMAND_21.length,1);
	read_eeprBuff(STRING_21,COMMAND_21.buffer,COMMAND_21.length);*/
	read_eeprBuff(LENGTH_e8, &COMMAND_e8.length, 1);
	read_eeprBuff(STRING_e8, COMMAND_e8.buffer, COMMAND_e8.length);
	read_eeprBuff(MAC_EEP, buffer_mac, 6);
	
	PA1.addrTWI = read_eeprByte(I2C_PA1_EEPR);
	PA2.addrTWI = read_eeprByte(I2C_PA2_EEPR);
	PA3.addrTWI = read_eeprByte(I2C_PA3_EEPR);
	//PA4.addrTWI = read_eeprByte(I2C_PA3_EEPR);
	
	PA1.band = read_eeprByte(BAND_PA1_EEPR);
	PA2.band = read_eeprByte(BAND_PA2_EEPR);
	PA3.band = read_eeprByte(BAND_PA3_EEPR);
	//PA4.band = read_eeprByte(BAND_PA3_EEPR);
	
	PA1.isValid = read_eeprByte(VALID_PA1_EEPR);
	PA2.isValid = read_eeprByte(VALID_PA2_EEPR);
	PA3.isValid = read_eeprByte(VALID_PA3_EEPR);
	//PA4.isValid = read_eeprByte(VALID_PA3_EEPR);
	
	COMMUTATOR.sreg4_state_att = read_eeprByte(ATT_1_EEPR) | read_eeprByte(ATT_3_EEPR) << 8;
	COMMUTATOR.sreg5_state_att = read_eeprByte(ATT_2_EEPR) | read_eeprByte(ATT_4_EEPR) << 8;
	
	REGISTERS.nmGpsWifiPpsState = read_eeprByte(WIFI_ALWAYS_ON) << 6;
}
void read_twiSensors() {
	const uint16_t COUNT = 0x4fff;
	static uint16_t i;
	
	if (i++ == 0){
		/////////////////////////////////////ina bts//////////////////////////////////////
		TRANSFER.pointer = INA_CURRENT_REG;
		twi_start(&TWIE, &INA_BTS, true, 0);
		twi_start(&TWIE, &INA_BTS, false, 2);

		TRANSFER.pointer = INA_VOLT_REG;
		twi_start(&TWIE, &INA_BTS, true, 0);
		twi_start(&TWIE, &INA_BTS, false, 2);
		
		TRANSFER.pointer = INA_POWER_REG;
		twi_start(&TWIE, &INA_BTS, true, 0);
		twi_start(&TWIE, &INA_BTS, false, 2);
		/////////////////////////////////////ina periphery////////////////////////////////
		TRANSFER.pointer = INA_CURRENT_REG;
		twi_start(&TWIE, &INA_PERIPHERY, true, 0);
		twi_start(&TWIE, &INA_PERIPHERY, false, 2);
		
		TRANSFER.pointer = INA_VOLT_REG;
		twi_start(&TWIE, &INA_PERIPHERY, true, 0);
		twi_start(&TWIE, &INA_PERIPHERY, false, 2);
		
		TRANSFER.pointer = INA_POWER_REG;
		twi_start(&TWIE, &INA_PERIPHERY, true, 0);
		twi_start(&TWIE, &INA_PERIPHERY, false, 2);
		/////////////////////////////////////temperature/////////////////////////////////
		TRANSFER.pointer = TEMP_base;
		twi_start(&TWID, &PA1, false, 2);
		twi_start(&TWID, &PA2, false, 2);
	}
	else if (i == COUNT / 3){
		twi_start(&TWIF, &PA3, false, 1);
		//twi_start(&TWIF, &PA4, false, 1);
	}
	else if (i == COUNT / 2){
		twi_start(&TWIC, &BOARD, false, 1);
	}
	else if (i == COUNT) {
		i = 0;
	}
}