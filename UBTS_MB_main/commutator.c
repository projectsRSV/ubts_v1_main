#include "commutator.h"




void commutator_decoder(uint8_t address){
	switch(address){
		case 0x00:{
			_1_off();
			_2_off();
			_3_off();
			_4_off();
			setAttCommutator(0, 0);
			break;
		}
		case 0x01:{
			_2_off();
			_3_off();
			_4_off();
			_1_1();
			setAttCommutator(0, 0);
			break;
		}
		case 0x02:{
			_2_off();
			_3_off();
			_4_off();
			_1_2();
			setAttCommutator(0, 0);
			break;
		}
		case 0x03:{
			_2_off();
			_3_off();
			_4_off();
			_1_3();
			setAttCommutator(0, 0);
			break;
		}
		case 0x04:{
			_1_off();
			_3_off();
			_4_off();
			_2_1();
			setAttCommutator(0, 0);
			break;
		}
		case 0x05:{
			_1_off();
			_3_off();
			_4_off();
			_2_2();
			setAttCommutator(0, 0);
			break;
		}
		case 0x06:{
			_1_off();
			_3_off();
			_4_off();
			_2_3();
			setAttCommutator(0, 0);
			break;
		}
		case 0x07:{
			_1_off();
			_2_off();
			_4_off();
			_3_3();
			setAttCommutator(0, 0);
			break;
		}
		case 0x08:{
			_1_off();
			_2_off();
			_3_off();
			_4_3();
			setAttCommutator(0, 0);
			break;
		}
		case 0x09:{
			_4_off();
			_1_1();
			_2_1();
			_3_3();
			setAttCommutator(0x0018, 0x0018);
			break;
		}
		case 0x0a:{
			_3_off();
			_4_off();
			_1_1();
			if (PA1.band == PA3.band && PA3.isValid && PA1.isValid){
				_2_3();
				setAttCommutator(0x0000, 0x0000);
			}
			else{
				_2_1();
				setAttCommutator(0x0018, 0x0018);
			}
			break;
		}
		case 0x0b:{
			_2_off();
			_4_off();
			_1_1();
			_3_3();
			setAttCommutator(0, 0);
			break;
		}
		case 0x0c:{
			_2_off();
			_3_off();
			_1_1();
			_4_3();
			setAttCommutator(0, 0);
			break;
		}
		case 0x0d:{
			_4_off();
			_3_off();
			_1_1();
			_2_2();
			setAttCommutator(0, 0);
			break;
		}
		case 0x0e:{
			_2_off();
			_3_off();
			_1_2();
			_2_1();
			setAttCommutator(0, 0);
			break;
		}
		case 0x0f:{
			_3_off();
			_4_off();
			_1_2();
			_2_3();
			setAttCommutator(0, 0);
			break;
		}
		case 0x10:{
			_2_off();
			_4_off();
			_1_2();
			_3_3();
			setAttCommutator(0, 0);
			break;
		}
		case 0x11:{
			_2_off();
			_3_off();
			_1_2();
			_4_3();
			setAttCommutator(0, 0);
			break;
		}
		case 0x12:{
			if(PA1.band == 0x01){
				_2_off();
				_1_3();
				_3_2100();
				_4_2100();
				setAttCommutator(0x0018, 0x1818);
			}
			else commutator_decoder(0xff);
			break;
		}
		case 0x13:{
			_3_off();
			_4_off();
			_1_2();
			_2_2();
			setAttCommutator(0x0018, 0x0018);
			break;
		}
		case 0x14:{
			_1_off();
			_4_off();
			_2_1();
			_3_3();
			setAttCommutator(0, 0);
			break;
		}
		case 0x15:{
			_1_off();
			_3_off();
			_2_1();
			_4_3();
			setAttCommutator(0, 0);
			break;
		}
		case 0x16:{
			_1_off();
			_4_off();
			_2_2();
			_3_3();
			setAttCommutator(0, 0);
			break;
		}
		case 0x17:{
			_1_off();
			_3_off();
			_2_2();
			_4_3();
			setAttCommutator(0, 0);
			break;
		}
		case 0x18:{
			_1_off();
			_2_2();
			if (PA3.band == 0x01){
				_3_2100();
				_4_2100();
				setAttCommutator(0, 0);
			}
			else{
				_3_3();
				_4_3();
				setAttCommutator(0x1800, 0x1800);
			}
			break;
		}
		case 0x19:{
			_1_off();
			_2_1();
			if (PA3.band == 0x01){
				_3_2100();
				_4_2100();
				setAttCommutator(0, 0);
			}
			else{
				_3_3();
				_4_3();
				setAttCommutator(0x1800, 0x1800);
			}
			break;
		}
		case 0x1a:{
			_2_off();
			_1_1();
			if (PA3.band == 0x01){
				_3_2100();
				_4_2100();
				setAttCommutator(0, 0);
			}
			else{
				_3_3();
				_4_3();
				setAttCommutator(0x1800, 0x1800);
			}
			break;
		}
		case 0x1b:{
			_2_off();
			_1_2();
			if (PA3.band == 0x01){
				_3_2100();
				_4_2100();
				setAttCommutator(0, 0);
			}
			else{
				_3_3();
				_4_3();
				setAttCommutator(0x1800, 0x1800);
			}
			break;
		}
		case 0x1c:{
			_1_off();
			_2_off();
			if (PA3.band == 0x01){
				_3_2100();
				_4_2100();
				setAttCommutator(0, 0);
			}
			else{
				_3_3();
				_4_3();
				setAttCommutator(0x1800, 0x1800);
			}
			break;
		}
		case 0x1d:{
			_3_off();
			_4_off();
			_1_3();
			_2_1();
			setAttCommutator(0, 0);
			break;
		}
		case 0x1e:{
			_3_off();
			_4_off();
			_1_3();
			_2_2();
			setAttCommutator(0, 0);
			break;
		}
		case 0x1f:{
			_3_off();
			_4_off();
			_1_3();
			_2_3();
			setAttCommutator(0x0018, 0x0018);
			break;
		}
		case 0x20:{
			_2_off();
			_3_off();
			_1_3();
			_4_3();
			setAttCommutator(0x0018, 0x1800);
			break;
		}
		case 0x21:{
			_1_off();
			_4_off();
			if (PA1.band == PA3.band && PA3.isValid && PA1.isValid){
				_2_1();
				_3_3();
				setAttCommutator(0x0000, 0x0000);
			}
			else{
				_2_3();
				_3_3();
				setAttCommutator(0x0000, 0x1818);
			}
			break;
		}
		case 0x22:{
			_1_1();
			_2_1();
			if (PA3.band == 0x01){
				_3_2100();
				_4_2100();
				setAttCommutator(0x0018, 0x0018);
			}
			else{
				_3_3();
				_4_3();
				setAttCommutator(0x1818, 0x1818);
			}
			break;
		}
		case 0x23:{
			_1_2();
			_2_2();
			if (PA3.band == 0x01){
				_3_2100();
				_4_2100();
				setAttCommutator(0x0018, 0x0018);
			}
			else{
				_3_3();
				_4_3();
				setAttCommutator(0x1818, 0x1818);
			}
			break;
		}
		case 0x24:{
			_1_1();
			_2_2();
			if (PA3.band == 0x01){
				_3_2100();
				_4_2100();
				setAttCommutator(0x0000, 0x0000);
			}
			else{
				_3_3();
				_4_3();
				setAttCommutator(0x1800, 0x1800);
			}
			break;
		}
		case 0x25:{
			_1_2();
			_2_1();
			if (PA3.band == 0x01){
				_3_2100();
				_4_2100();
				setAttCommutator(0x0000, 0x0000);
			}
			else{
				_3_3();
				_4_3();
				setAttCommutator(0x1800, 0x1800);
			}
			break;
		}
		case 0x26:{
			_2_off();
			_4_off();
			_1_1();
			_3_3();
			setAttCommutator(0x0000, 0x0000);
			break;
		}
		case 0x27:{
			if (PA1.band == 0x01 && PA3.band == 0x01 && PA1.isValid && PA3.isValid){
				_2_off();
				_1_1();
				_3_2100();
				_4_2100();
				setAttCommutator(0x0000, 0x0000);
			}
			else utils_sendAnswerDebug(DEBUG_CH, _COMM_ERR, 0, 0);
			break;
		}
		case 0x28:{
			if (PA1.band == 0x01 && PA3.band == 0x01 && PA1.isValid && PA3.isValid){
				_2_off();
				_3_off();
				_1_1();
				_4_3();
				setAttCommutator(0x0000, 0x0000);
			}
			else utils_sendAnswerDebug(DEBUG_CH, _COMM_ERR, 0, 0);
			break;
		}
		case 0x29:{
			_4_off();
			if (PA1.band == PA3.band && COMMUTATOR.standart_ch_1 == 'L' && COMMUTATOR.standart_ch_2 == 'L' && COMMUTATOR.standart_ch_3 == 'U' && PA1.isValid && PA3.isValid){
				_1_1();
				_2_1();
				_3_3();
				setAttCommutator(0x0018, 0x0018);
			}
			else {
				_1_1();
				_2_3();
				_3_3();
				setAttCommutator(0x1800, 0x0018);
			}
			break;
		}
		case 0x2a:{
			_3_off();
			_4_off();
			_1_1();
			_2_3();
			setAttCommutator(0x0000, 0x0000);
			break;
		}
		case 0x2b:{
			_4_off();
			if (PA1.band == PA3.band && COMMUTATOR.standart_ch_1 == 'L' && COMMUTATOR.standart_ch_2 == 'L' && COMMUTATOR.standart_ch_3 == 'U' && PA1.isValid && PA3.isValid){
				_1_1();
				_2_1();
				_3_3();
				setAttCommutator(0x0018, 0x0018);
			}
			else {
				_1_1();
				_2_3();
				_3_3();
				setAttCommutator(0x1800, 0x0018);
			}
			break;
		}
		
		
		case 0xff:{
			utils_sendAnswerDebug(DEBUG_CH, _COMM_ERR, 0, 0);
			break;
		}
	}
}

uint8_t table_1[] = {0x00, 0x01, 0x02, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00,/*09*/ 0x01, 0x01, 0x01, 0x01, 0x01,/*0e*/ 0x02, 0x02, 0x02, 0x02, 0x04,/*13*/ 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,/*1a*/ 0x01, 0x02, 0x00, 0x04, 0x04, 0x04,/*20*/ 0x04, 0x00, 0x01, 0x02, 0x01, 0x02,/*26*/ 0x01, 0x01, 0x01, 0x01, 0x01, 0x01};

uint8_t table_2[] = {0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x00, 0x00,/*09*/ 0x01, 0x01, 0x00, 0x00, 0x02,/*0e*/ 0x01, 0x04, 0x00, 0x00, 0x00,/*13*/ 0x02, 0x01, 0x01, 0x02, 0x02, 0x02, 0x01,/*1a*/ 0x00, 0x00, 0x00, 0x01, 0x02, 0x04,/*20*/ 0x00, 0x04, 0x01, 0x02, 0x02, 0x01,/*26*/ 0x00, 0x00, 0x00, 0x01, 0x04, 0x04};

uint8_t table_3[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00,/*09*/ 0x04, 0x00, 0x04, 0x00, 0x00,/*0e*/ 0x00, 0x00, 0x04, 0x00, 0x04,/*13*/ 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x04,/*1a*/ 0x04, 0x04, 0x04, 0x00, 0x00, 0x00,/*20*/ 0x00, 0x04, 0x04, 0x04, 0x04, 0x04,/*26*/ 0x04, 0x01, 0x00, 0x01, 0x00, 0x04};

uint8_t table_4[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04,/*09*/ 0x00, 0x00, 0x00, 0x04, 0x00,/*0e*/ 0x00, 0x00, 0x00, 0x04, 0x04,/*13*/ 0x00, 0x00, 0x04, 0x00, 0x04, 0x04, 0x04,/*1a*/ 0x04, 0x04, 0x04, 0x00, 0x00, 0x00,/*20*/ 0x04, 0x00, 0x04, 0x04, 0x04, 0x04,/*26*/ 0x00, 0x01, 0x01, 0x00, 0x00, 0x00};

uint8_t searchCombination(){
	volatile  uint8_t size = sizeof(table_1);
	for (uint8_t i=0; i < size; i++){
		if (table_1[i] == COMMUTATOR.ch_1 && table_2[i] == COMMUTATOR.ch_2 && table_3[i] == COMMUTATOR.ch_3 && table_4[i] == COMMUTATOR.ch_4){
			return i;
		}
	}
	return 0xff;
}
uint8_t findDuplicate(){
	uint8_t size = sizeof(table_1);
	for (uint8_t i=0; i < size; i++){
		for (uint8_t k= i+1; k < size; k++){
			//if (i == k) continue;
			if (table_1[i] == table_1[k] && table_2[i] == table_2[k] && table_3[i] == table_3[k] && table_4[i] == table_4[k] ) return i;
		}
	}
	return 0xff;
}
void _1_1(){
	COMMUTATOR.sreg1_state_tx &= ~0b00011111;
	COMMUTATOR.sreg1_state_tx |=  0b00100000;

	COMMUTATOR.sreg2_state_tx &= ~0b01000011;
	COMMUTATOR.sreg2_state_tx |=  0b10000000;

	COMMUTATOR.sreg3_state_tx &= ~0b0100000;
	COMMUTATOR.sreg3_state_tx |=  0b00010000;
	if (!checkInChannelState()) {
		COMMUTATOR.sreg3_state_tx &= ~0b00001111;
	}

	spi_setReg(&SPID, &PORTF, COMMUTATOR.sreg1_state_tx, TX_SREG_SPI_1);
	spi_setReg(&SPID, &PORTF, COMMUTATOR.sreg2_state_tx, TX_SREG_SPI_2);
	spi_setReg(&SPID, &PORTF, COMMUTATOR.sreg3_state_tx, TX_SREG_SPI_3);
	//******************************************************************
	COMMUTATOR.sreg1_state_rx = 0b00000000;

	COMMUTATOR.sreg2_state_rx &= ~0b00010011;
	COMMUTATOR.sreg2_state_rx |=  0b00100000;

	COMMUTATOR.sreg3_state_rx &= ~0b10000000;
	if (!checkInChannelState()){
		COMMUTATOR.sreg3_state_rx &= ~0b00001111;
	}
	COMMUTATOR.sreg3_state_rx |= 0b00010000;

	spi_setReg(&SPID, &PORTJ, COMMUTATOR.sreg1_state_rx, RX_SREG_SPI_1);
	spi_setReg(&SPID, &PORTJ, COMMUTATOR.sreg2_state_rx, RX_SREG_SPI_2);
	spi_setReg(&SPID, &PORTJ, COMMUTATOR.sreg3_state_rx, RX_SREG_SPI_3);

	utils_sendAnswerDebug(DEBUG_CH, _1_1P, 0, 0);
}
void _1_2(){
	COMMUTATOR.sreg1_state_tx &= ~0b00011111;
	COMMUTATOR.sreg1_state_tx |=  0b01000000;

	COMMUTATOR.sreg2_state_tx &= ~0b00000011;
	COMMUTATOR.sreg2_state_tx |=  0b11000000;

	COMMUTATOR.sreg3_state_tx &= ~0b00010000;
	COMMUTATOR.sreg3_state_tx |=  0b01000000;
	if (!checkInChannelState()) {
		COMMUTATOR.sreg3_state_tx &= ~0b00011111;
	}

	spi_setReg(&SPID, &PORTF, COMMUTATOR.sreg1_state_tx, TX_SREG_SPI_1);
	spi_setReg(&SPID, &PORTF, COMMUTATOR.sreg2_state_tx, TX_SREG_SPI_2);
	spi_setReg(&SPID, &PORTF, COMMUTATOR.sreg3_state_tx, TX_SREG_SPI_3);
	//******************************************************************
	COMMUTATOR.sreg1_state_rx = 0b00000000;

	COMMUTATOR.sreg2_state_rx &= ~0b00000011;
	COMMUTATOR.sreg2_state_rx |=  0b00110000;

	COMMUTATOR.sreg3_state_rx &= ~0b00010000;
	if (!checkInChannelState()){
		COMMUTATOR.sreg3_state_rx &= ~0b00001111;
	}
	COMMUTATOR.sreg3_state_rx |= 0b10000000;

	spi_setReg(&SPID, &PORTJ, COMMUTATOR.sreg1_state_rx, RX_SREG_SPI_1);
	spi_setReg(&SPID, &PORTJ, COMMUTATOR.sreg2_state_rx, RX_SREG_SPI_2);
	spi_setReg(&SPID, &PORTJ, COMMUTATOR.sreg3_state_rx, RX_SREG_SPI_3);

	utils_sendAnswerDebug(DEBUG_CH, _1_2P, 0, 0);
}
void _1_3(){
	COMMUTATOR.sreg1_state_tx &= ~0b00011111;
	COMMUTATOR.sreg1_state_tx |=  0b10000000;

	COMMUTATOR.sreg2_state_tx &= ~0b10000011;
	COMMUTATOR.sreg2_state_tx |=  0b01000000;

	COMMUTATOR.sreg3_state_tx &= ~0b01010010;
	if (!checkInChannelState()) {
		COMMUTATOR.sreg3_state_tx &= ~0b00001100;
	}
	COMMUTATOR.sreg3_state_tx |=  0b00000001;

	spi_setReg(&SPID, &PORTF, COMMUTATOR.sreg1_state_tx, TX_SREG_SPI_1);
	spi_setReg(&SPID, &PORTF, COMMUTATOR.sreg2_state_tx, TX_SREG_SPI_2);
	spi_setReg(&SPID, &PORTF, COMMUTATOR.sreg3_state_tx, TX_SREG_SPI_3);
	//******************************************************************
	COMMUTATOR.sreg1_state_rx = 0b00000000;

	COMMUTATOR.sreg2_state_rx &= ~0b00100011;
	COMMUTATOR.sreg2_state_rx |=  0b00010000;

	COMMUTATOR.sreg3_state_rx &= ~0b10011000;
	if (!checkInChannelState()){
		COMMUTATOR.sreg3_state_rx &= ~0b00000011;
	}
	COMMUTATOR.sreg3_state_rx |= 0b00000100;

	spi_setReg(&SPID, &PORTJ, COMMUTATOR.sreg1_state_rx, RX_SREG_SPI_1);
	spi_setReg(&SPID, &PORTJ, COMMUTATOR.sreg2_state_rx, RX_SREG_SPI_2);
	spi_setReg(&SPID, &PORTJ, COMMUTATOR.sreg3_state_rx, RX_SREG_SPI_3);

	utils_sendAnswerDebug(DEBUG_CH, _1_3P, 0, 0);
}
void _1_off(){
	COMMUTATOR.sreg1_state_tx &= ~0b00011111;
	COMMUTATOR.sreg2_state_tx &= ~0b00010011;
	COMMUTATOR.sreg3_state_tx &= ~0b01010000;
	if (!checkInChannelState()) {
		COMMUTATOR.sreg1_state_tx &= ~0b11100000;
		COMMUTATOR.sreg3_state_tx &= ~0b00001111;
	}
	spi_setReg(&SPID, &PORTF, COMMUTATOR.sreg1_state_tx, TX_SREG_SPI_1);
	spi_setReg(&SPID, &PORTF, COMMUTATOR.sreg2_state_tx, TX_SREG_SPI_2);
	spi_setReg(&SPID, &PORTF, COMMUTATOR.sreg3_state_tx, TX_SREG_SPI_3);
	//******************************************************************
	COMMUTATOR.sreg1_state_rx  =  0b00000000;
	COMMUTATOR.sreg2_state_rx &= ~0b00110011;
	COMMUTATOR.sreg3_state_rx &= ~0b10010000;
	if (!checkInChannelState()){
		COMMUTATOR.sreg3_state_rx &= ~0b00001111;
	}

	spi_setReg(&SPID, &PORTJ, COMMUTATOR.sreg1_state_rx, RX_SREG_SPI_1);
	spi_setReg(&SPID, &PORTJ, COMMUTATOR.sreg2_state_rx, RX_SREG_SPI_2);
	spi_setReg(&SPID, &PORTJ, COMMUTATOR.sreg3_state_rx, RX_SREG_SPI_3);

	utils_sendAnswerDebug(DEBUG_CH, _1_OFF, 0, 0);
}

void _2_1(){
	COMMUTATOR.sreg1_state_tx &= ~0b00011111;
	COMMUTATOR.sreg1_state_tx |=  0b00100000;

	COMMUTATOR.sreg2_state_tx &= ~0b00000011;
	COMMUTATOR.sreg2_state_tx |=  0b00110000;

	COMMUTATOR.sreg3_state_tx &= ~0b10000000;
	COMMUTATOR.sreg3_state_tx |=  0b00100000;
	if (!checkInChannelState()) {
		COMMUTATOR.sreg3_state_tx &= ~0b00001111;
	}

	spi_setReg(&SPID, &PORTF, COMMUTATOR.sreg1_state_tx, TX_SREG_SPI_1);
	spi_setReg(&SPID, &PORTF, COMMUTATOR.sreg2_state_tx, TX_SREG_SPI_2);
	spi_setReg(&SPID, &PORTF, COMMUTATOR.sreg3_state_tx, TX_SREG_SPI_3);
	//******************************************************************
	COMMUTATOR.sreg1_state_rx = 0b00000000;

	COMMUTATOR.sreg2_state_rx &= ~0b00000011;
	COMMUTATOR.sreg2_state_rx |=  0b11000000;

	COMMUTATOR.sreg3_state_rx &= ~0b01000000;
	if (!checkInChannelState()){
		COMMUTATOR.sreg3_state_rx &= ~0b00001111;
	}
	COMMUTATOR.sreg3_state_rx |= 0b00100000;

	spi_setReg(&SPID, &PORTJ, COMMUTATOR.sreg1_state_rx, RX_SREG_SPI_1);
	spi_setReg(&SPID, &PORTJ, COMMUTATOR.sreg2_state_rx, RX_SREG_SPI_2);
	spi_setReg(&SPID, &PORTJ, COMMUTATOR.sreg3_state_rx, RX_SREG_SPI_3);

	utils_sendAnswerDebug(DEBUG_CH, _2_1P, 0, 0);
}
void _2_2(){
	COMMUTATOR.sreg1_state_tx &= ~0b00011111;
	COMMUTATOR.sreg1_state_tx |=  0b01000000;

	COMMUTATOR.sreg2_state_tx &= ~0b00100011;
	COMMUTATOR.sreg2_state_tx |=  0b00010000;

	COMMUTATOR.sreg3_state_tx &= ~0b00100000;
	COMMUTATOR.sreg3_state_tx |=  0b10000000;
	if (!checkInChannelState()) {
		COMMUTATOR.sreg3_state_tx &= ~0b00001111;
	}

	spi_setReg(&SPID, &PORTF, COMMUTATOR.sreg1_state_tx, TX_SREG_SPI_1);
	spi_setReg(&SPID, &PORTF, COMMUTATOR.sreg2_state_tx, TX_SREG_SPI_2);
	spi_setReg(&SPID, &PORTF, COMMUTATOR.sreg3_state_tx, TX_SREG_SPI_3);
	//******************************************************************
	COMMUTATOR.sreg1_state_rx = 0b00000000;

	COMMUTATOR.sreg2_state_rx &= ~0b10000011;
	COMMUTATOR.sreg2_state_rx |=  0b01000000;

	COMMUTATOR.sreg3_state_rx &= ~0b00100000;
	if (!checkInChannelState()){
		COMMUTATOR.sreg3_state_rx &= ~0b00001111;
	}
	COMMUTATOR.sreg3_state_rx |= 0b01000000;

	spi_setReg(&SPID, &PORTJ, COMMUTATOR.sreg1_state_rx, RX_SREG_SPI_1);
	spi_setReg(&SPID, &PORTJ, COMMUTATOR.sreg2_state_rx, RX_SREG_SPI_2);
	spi_setReg(&SPID, &PORTJ, COMMUTATOR.sreg3_state_rx, RX_SREG_SPI_3);

	utils_sendAnswerDebug(DEBUG_CH, _2_2P, 0, 0);
}
void _2_3(){
	COMMUTATOR.sreg1_state_tx &= ~0b00011111;
	COMMUTATOR.sreg1_state_tx |=  0b10000000;

	COMMUTATOR.sreg2_state_tx &= ~0b00110011;

	COMMUTATOR.sreg3_state_tx &= ~0b10101000;
	COMMUTATOR.sreg3_state_tx |=  0b00000100;
	if (!checkInChannelState()) {
		COMMUTATOR.sreg3_state_tx &= ~0b00000011;
	}

	spi_setReg(&SPID, &PORTF, COMMUTATOR.sreg1_state_tx, TX_SREG_SPI_1);
	spi_setReg(&SPID, &PORTF, COMMUTATOR.sreg2_state_tx, TX_SREG_SPI_2);
	spi_setReg(&SPID, &PORTF, COMMUTATOR.sreg3_state_tx, TX_SREG_SPI_3);
	//******************************************************************
	COMMUTATOR.sreg1_state_rx = 0b00000000;

	COMMUTATOR.sreg2_state_rx &= ~0b11000011;

	COMMUTATOR.sreg3_state_rx &= ~0b01100010;
	if (!checkInChannelState()){
		COMMUTATOR.sreg3_state_rx &= ~0b00001100;
	}
	COMMUTATOR.sreg3_state_rx |= 0b00000001;

	spi_setReg(&SPID, &PORTJ, COMMUTATOR.sreg1_state_rx, RX_SREG_SPI_1);
	spi_setReg(&SPID, &PORTJ, COMMUTATOR.sreg2_state_rx, RX_SREG_SPI_2);
	spi_setReg(&SPID, &PORTJ, COMMUTATOR.sreg3_state_rx, RX_SREG_SPI_3);

	utils_sendAnswerDebug(DEBUG_CH, _2_3P, 0, 0);
}
void _2_off(){
	COMMUTATOR.sreg1_state_tx &= ~0b00011111;
	if (!checkInChannelState()) {
		COMMUTATOR.sreg1_state_tx &= ~0x11100000;
	}

	COMMUTATOR.sreg2_state_tx &= ~0b00010011;
	COMMUTATOR.sreg2_state_tx |=  0b00100000;

	COMMUTATOR.sreg3_state_tx &= ~0b10100000;
	if (!checkInChannelState()) {
		COMMUTATOR.sreg3_state_tx &= ~0b00001111;
	}
	spi_setReg(&SPID, &PORTF, COMMUTATOR.sreg1_state_tx, TX_SREG_SPI_1);
	spi_setReg(&SPID, &PORTF, COMMUTATOR.sreg2_state_tx, TX_SREG_SPI_2);
	spi_setReg(&SPID, &PORTF, COMMUTATOR.sreg3_state_tx, TX_SREG_SPI_3);
	//******************************************************************
	COMMUTATOR.sreg1_state_rx  =  0b00000000;
	COMMUTATOR.sreg2_state_rx &= ~0b01000011;
	COMMUTATOR.sreg2_state_tx |=  0b10000000;
	COMMUTATOR.sreg3_state_rx &= ~0b01100000;
	if (!checkInChannelState()){
		COMMUTATOR.sreg3_state_rx &= ~0b00001111;
	}

	spi_setReg(&SPID, &PORTJ, COMMUTATOR.sreg1_state_rx, RX_SREG_SPI_1);
	spi_setReg(&SPID, &PORTJ, COMMUTATOR.sreg2_state_rx, RX_SREG_SPI_2);
	spi_setReg(&SPID, &PORTJ, COMMUTATOR.sreg3_state_rx, RX_SREG_SPI_3);

	utils_sendAnswerDebug(DEBUG_CH, _2_OFF, 0, 0);
}

void _3_1(){
	utils_sendAnswerDebug(DEBUG_CH, _COMM_ERR, 0, 0);
}
void _3_2(){
	utils_sendAnswerDebug(DEBUG_CH, _COMM_ERR, 0, 0);
}
void _3_3(){
	COMMUTATOR.sreg1_state_tx &= ~0b00011111;
	COMMUTATOR.sreg1_state_tx |=  0b10000000;

	COMMUTATOR.sreg2_state_tx &= ~0b00000011;
	COMMUTATOR.sreg2_state_tx |=  0b00001000;

	if (!checkInChannelState()) {
		COMMUTATOR.sreg3_state_tx &= ~0b00001100;
	}
	COMMUTATOR.sreg3_state_tx |=  0b00000011;

	spi_setReg(&SPID, &PORTF, COMMUTATOR.sreg1_state_tx, TX_SREG_SPI_1);
	spi_setReg(&SPID, &PORTF, COMMUTATOR.sreg2_state_tx, TX_SREG_SPI_2);
	spi_setReg(&SPID, &PORTF, COMMUTATOR.sreg3_state_tx, TX_SREG_SPI_3);
	//******************************************************************
	COMMUTATOR.sreg1_state_rx = 0b00000000;

	COMMUTATOR.sreg2_state_rx &= ~0b00000011;
	COMMUTATOR.sreg2_state_rx |=  0b00001000;

	if (!checkInChannelState()){
		COMMUTATOR.sreg3_state_rx &= ~0b00000011;
	}
	COMMUTATOR.sreg3_state_rx |= 0b00001100;

	spi_setReg(&SPID, &PORTJ, COMMUTATOR.sreg1_state_rx, RX_SREG_SPI_1);
	spi_setReg(&SPID, &PORTJ, COMMUTATOR.sreg2_state_rx, RX_SREG_SPI_2);
	spi_setReg(&SPID, &PORTJ, COMMUTATOR.sreg3_state_rx, RX_SREG_SPI_3);

	utils_sendAnswerDebug(DEBUG_CH, _3_3P, 0, 0);
}
void _3_2100(){
	COMMUTATOR.sreg2_state_tx &= ~0b00001011;
	COMMUTATOR.sreg2_state_tx |=  0b00000100;

	if (!checkInChannelState()) {
		COMMUTATOR.sreg3_state_tx &= ~0b00000011;
	}
	COMMUTATOR.sreg3_state_tx |=  0b00001100;

	spi_setReg(&SPID, &PORTF, COMMUTATOR.sreg2_state_tx, TX_SREG_SPI_2);
	spi_setReg(&SPID, &PORTF, COMMUTATOR.sreg3_state_tx, TX_SREG_SPI_3);
	//******************************************************************
	COMMUTATOR.sreg1_state_rx = 0b00000000;

	COMMUTATOR.sreg2_state_rx &= ~0b00001011;
	COMMUTATOR.sreg2_state_rx |=  0b00000100;

	if (!checkInChannelState()){
		COMMUTATOR.sreg3_state_rx &= ~0b00001100;
	}
	COMMUTATOR.sreg3_state_rx |= 0b00000011;

	spi_setReg(&SPID, &PORTJ, COMMUTATOR.sreg1_state_rx, RX_SREG_SPI_1);
	spi_setReg(&SPID, &PORTJ, COMMUTATOR.sreg2_state_rx, RX_SREG_SPI_2);
	spi_setReg(&SPID, &PORTJ, COMMUTATOR.sreg3_state_rx, RX_SREG_SPI_3);
	utils_sendAnswerDebug(DEBUG_CH, _3_2100P, 0, 0);
}
void _3_off(){
	COMMUTATOR.sreg1_state_tx &= ~0b00011111;
	if (!checkInChannelState()) {
		COMMUTATOR.sreg1_state_tx &= ~0x11100000;
	}

	COMMUTATOR.sreg2_state_tx &= ~0b00001011;

	if (!checkInChannelState()) {
		COMMUTATOR.sreg3_state_tx &= ~0b00001111;
	}
	spi_setReg(&SPID, &PORTF, COMMUTATOR.sreg1_state_tx, TX_SREG_SPI_1);
	spi_setReg(&SPID, &PORTF, COMMUTATOR.sreg2_state_tx, TX_SREG_SPI_2);
	spi_setReg(&SPID, &PORTF, COMMUTATOR.sreg3_state_tx, TX_SREG_SPI_3);
	//******************************************************************
	COMMUTATOR.sreg1_state_rx  =  0b00000000;
	COMMUTATOR.sreg2_state_rx &= ~0b00001011;
	if (!checkInChannelState()){
		COMMUTATOR.sreg3_state_rx &= ~0b00001111;
	}

	spi_setReg(&SPID, &PORTJ, COMMUTATOR.sreg1_state_rx, RX_SREG_SPI_1);
	spi_setReg(&SPID, &PORTJ, COMMUTATOR.sreg2_state_rx, RX_SREG_SPI_2);
	spi_setReg(&SPID, &PORTJ, COMMUTATOR.sreg3_state_rx, RX_SREG_SPI_3);

	utils_sendAnswerDebug(DEBUG_CH, _3_OFF, 0, 0);
}

void _4_1(){
	utils_sendAnswerDebug(DEBUG_CH, _COMM_ERR, 0, 0);
}
void _4_2(){
	utils_sendAnswerDebug(DEBUG_CH, _COMM_ERR, 0, 0);
}
void _4_3(){
	COMMUTATOR.sreg1_state_tx &= ~0b00011111;
	COMMUTATOR.sreg1_state_tx |=  0b10000000;

	COMMUTATOR.sreg2_state_tx &= ~0b00000111;

	COMMUTATOR.sreg3_state_tx &= ~0b00000100;
	if (!checkInChannelState()) {
		COMMUTATOR.sreg3_state_tx &= ~0b00000011;
	}
	COMMUTATOR.sreg3_state_tx |=  0b00001000;

	spi_setReg(&SPID, &PORTF, COMMUTATOR.sreg1_state_tx, TX_SREG_SPI_1);
	spi_setReg(&SPID, &PORTF, COMMUTATOR.sreg2_state_tx, TX_SREG_SPI_2);
	spi_setReg(&SPID, &PORTF, COMMUTATOR.sreg3_state_tx, TX_SREG_SPI_3);
	//******************************************************************
	COMMUTATOR.sreg1_state_rx = 0b00000000;

	COMMUTATOR.sreg2_state_rx &= ~0b00000111;

	COMMUTATOR.sreg3_state_rx &= ~0b00000001;
	if (!checkInChannelState()){
		COMMUTATOR.sreg3_state_rx &= ~0b00001100;
	}
	COMMUTATOR.sreg3_state_rx |= 0b00000010;

	spi_setReg(&SPID, &PORTJ, COMMUTATOR.sreg1_state_rx, RX_SREG_SPI_1);
	spi_setReg(&SPID, &PORTJ, COMMUTATOR.sreg2_state_rx, RX_SREG_SPI_2);
	spi_setReg(&SPID, &PORTJ, COMMUTATOR.sreg3_state_rx, RX_SREG_SPI_3);

	utils_sendAnswerDebug(DEBUG_CH, _4_3P, 0, 0);
}
void _4_2100(){
	COMMUTATOR.sreg2_state_tx &= ~0b00001011;
	COMMUTATOR.sreg2_state_tx |=  0b00000100;

	if (!checkInChannelState()) {
		COMMUTATOR.sreg3_state_tx &= ~0b00000011;
	}
	COMMUTATOR.sreg3_state_tx |=  0b00001100;

	spi_setReg(&SPID, &PORTF, COMMUTATOR.sreg2_state_tx, TX_SREG_SPI_2);
	spi_setReg(&SPID, &PORTF, COMMUTATOR.sreg3_state_tx, TX_SREG_SPI_3);
	//******************************************************************
	COMMUTATOR.sreg1_state_rx = 0b00000000;

	COMMUTATOR.sreg2_state_rx &= ~0b00001011;
	COMMUTATOR.sreg2_state_rx |=  0b00000100;

	if (!checkInChannelState()){
		COMMUTATOR.sreg3_state_rx &= ~0b00001100;
	}
	COMMUTATOR.sreg3_state_rx |= 0b00000011;

	spi_setReg(&SPID, &PORTJ, COMMUTATOR.sreg1_state_rx, RX_SREG_SPI_1);
	spi_setReg(&SPID, &PORTJ, COMMUTATOR.sreg2_state_rx, RX_SREG_SPI_2);
	spi_setReg(&SPID, &PORTJ, COMMUTATOR.sreg3_state_rx, RX_SREG_SPI_3);
	utils_sendAnswerDebug(DEBUG_CH, _4_2100P, 0, 0);
}
void _4_off(){
	COMMUTATOR.sreg1_state_tx &= ~0b00011111;
	if (!checkInChannelState()) {
		COMMUTATOR.sreg1_state_tx &= ~0x11100000;
	}

	COMMUTATOR.sreg2_state_tx &= ~0b00000011;
	COMMUTATOR.sreg2_state_tx |=  0b00000100;

	if (!checkInChannelState()) {
		COMMUTATOR.sreg3_state_tx &= ~0b00001111;
	}
	spi_setReg(&SPID, &PORTF, COMMUTATOR.sreg1_state_tx, TX_SREG_SPI_1);
	spi_setReg(&SPID, &PORTF, COMMUTATOR.sreg2_state_tx, TX_SREG_SPI_2);
	spi_setReg(&SPID, &PORTF, COMMUTATOR.sreg3_state_tx, TX_SREG_SPI_3);
	//******************************************************************
	COMMUTATOR.sreg1_state_rx  =  0b00000000;
	COMMUTATOR.sreg2_state_rx &= ~0b00000011;
	COMMUTATOR.sreg2_state_rx |=  0b00000100;
	if (!checkInChannelState()){
		COMMUTATOR.sreg3_state_rx &= ~0b00001111;
	}

	spi_setReg(&SPID, &PORTJ, COMMUTATOR.sreg1_state_rx, RX_SREG_SPI_1);
	spi_setReg(&SPID, &PORTJ, COMMUTATOR.sreg2_state_rx, RX_SREG_SPI_2);
	spi_setReg(&SPID, &PORTJ, COMMUTATOR.sreg3_state_rx, RX_SREG_SPI_3);

	utils_sendAnswerDebug(DEBUG_CH, _4_OFF, 0, 0);
}
void setAttCommutator(uint16_t value4, uint16_t value5){										//value4 = 0xTTee - TT-ch3, ee-ch1; value5 = 0xYYuu   YY-ch4, uu-ch2
	spi_setRegDouble(&SPID, &PORTF, COMMUTATOR.sreg4_state_att + value4, ST_SREG_SPI_4);
	spi_setRegDouble(&SPID, &PORTK, COMMUTATOR.sreg5_state_att + value5, ST_SREG_SPI_5);
	utils_sendAnswer(DEBUG_CH, (uint8_t*)"\ns4= ", utils_hex16ToAscii32((COMMUTATOR.sreg4_state_att + value4) >> 1), 4);
	utils_sendAnswer(DEBUG_CH, (uint8_t*)"\ns5= ", utils_hex16ToAscii32((COMMUTATOR.sreg5_state_att + value5) >> 1), 4);
}
uint8_t checkInChannelState(){
	return COMMUTATOR.ch_1 | COMMUTATOR.ch_2 | COMMUTATOR.ch_3 | COMMUTATOR.ch_4;
}