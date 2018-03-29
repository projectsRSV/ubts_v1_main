#include "reads.h"



void read_commandUART() {
	static uint16_t i=0;
	if (i++ == 0x0fff) {
		if (!utils_isFifoEmpty(&FIFO_recUART)) {
			//w5200_sendDataFifo(DEBUG_CH,&FIFO_recUART);
			command_exec(commands_decoder(&FIFO_recUART));
		}
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
void read_isrW5200() {
	if (ISR_W5200.connect) {
		if(ISR_W5200.main) {
			utils_sendDebugPGM(MAIN_CH, _START, 0, 0);
			ISR_W5200.main = 0;
		}
		if(ISR_W5200.debug) {
			utils_sendDebugPGM(DEBUG_CH, _START, 0, 0);
			ISR_W5200.debug = 0;
		}
		ISR_W5200.connect = 0;
	}
	if (ISR_W5200.nm) {
		w5200_recvDataFifo(NM_CH, &FIFO_nmChRx);
		ISR_W5200.nm = 0;
	}
	if (ISR_W5200.main) {
		w5200_recvDataFifo(MAIN_CH, &FIFO_mainChRx);
		ISR_W5200.main = 0;
	}
	if (ISR_W5200.debug) {
		w5200_recvDataFifo(DEBUG_CH, &FIFO_mainChRx);
		ISR_W5200.debug = 0;
	}
	if (ISR_W5200.udp) {
		w5200_recvDataFifo(UDP_CH, &FIFO_mainChRx);
		ISR_W5200.udp = 0;
	}
}
void read_gps() {
	static uint16_t i=0;
	if (i++ == 0x07ff) {
		if(!utils_isFifoEmpty(&FIFO_gpsCh)) {
			w5200_sendDataFifo(GPS_CH,&FIFO_gpsCh);
		}
		i=0;
	}
}
void read_sendNMCommand() {
	static uint8_t i=0;
	if (i++ == 0xff) {
		if (!utils_isFifoEmpty(&FIFO_nmChRx)) {
			USARTD0.CTRLA |= USART_DREINTLVL0_bm;
		}
		i=0;
	}
}
void read_sendNMAnswer() {
	static uint8_t i=0;
	if (i++ == 0xff) {
		if (!utils_isFifoEmpty(&FIFO_nmChTx)) {
			//usart_sendDataFifo(&USARTE0, &FIFO_nmChTx);
			w5200_sendDataFifo(NM_CH, &FIFO_nmChTx);
		}
		i=0;
	}
}
void read_mainCommand() {
	static uint8_t i=0;
	if (i++ == 0x7f) {
		if (!utils_isFifoEmpty(&FIFO_mainChRx)) {
			command_exec(commands_decoder(&FIFO_mainChRx));
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
void read_eeprBuff(uint8_t addr,uint8_t* buff, uint8_t length) {
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
	read_eeprBuff(SERIAL_NUM,buffer_serialNum,4);
	read_eeprBuff(IP_SOURCE,buffer_IP_source,4);
	read_eeprBuff(SUBNET_MASK,buffer_SUB,4);
	read_eeprBuff(GATEWAY_ADDR,buffer_GATE,4);
	read_eeprBuff(SOCKET+1,&buffer_SOCKET_main[0],1);
	read_eeprBuff(SOCKET,&buffer_SOCKET_main[1],1);
	/*read_eeprBuff(LENGTH_3d,&COMMAND_3d.length,1);
	read_eeprBuff(STRING_3d,COMMAND_3d.buffer,COMMAND_3d.length);
	read_eeprBuff(LENGTH_21,&COMMAND_21.length,1);
	read_eeprBuff(STRING_21,COMMAND_21.buffer,COMMAND_21.length);*/
	read_eeprBuff(LENGTH_e8,&COMMAND_e8.length,1);
	read_eeprBuff(STRING_e8,COMMAND_e8.buffer,COMMAND_e8.length);
	
	PA1.addrTWI = read_eeprByte(I2C_PA0_EEPR);
	PA2.addrTWI = read_eeprByte(I2C_PA1_EEPR);
	PA3.addrTWI = read_eeprByte(I2C_PA2_EEPR);
	//PA4.addrTWI = read_eeprByte(I2C_PA3_EEPR);
	
	PA1.band = read_eeprByte(BAND_PA0_EEPR);
	PA2.band = read_eeprByte(BAND_PA1_EEPR);
	PA3.band = read_eeprByte(BAND_PA2_EEPR);
	//PA4.band = read_eeprByte(BAND_PA3_EEPR);
	
	PA1.isValid = read_eeprByte(VALID_PA0_EEPR);
	PA2.isValid = read_eeprByte(VALID_PA1_EEPR);
	PA3.isValid = read_eeprByte(VALID_PA2_EEPR);
	//PA4.isValid = read_eeprByte(VALID_PA3_EEPR);
	
	COMMUTATOR.sreg4_state_att = read_eeprByte(ATT_1_EEPR) | read_eeprByte(ATT_3_EEPR) << 8;
	COMMUTATOR.sreg5_state_att = read_eeprByte(ATT_2_EEPR) | read_eeprByte(ATT_4_EEPR) << 8;
	
	REGISTERS.nmGpsWifiPpsState = read_eeprByte(WIFI_ALWAYS_ON) << 6;
}
void read_twiSensors() {
	const uint16_t COUNT = 0x3fff;
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