#include "commutator.h"



void commutator_decoder(uint16_t address){
	//uint16_t *pArrValue = arrLedAll[9][3][1];;
	uint8_t tempCh01 = (address & 0x000f) ? 0 : 1;
	uint8_t tempCh23 = (address & 0x0f00) ? 2 : 3;

	//uint8_t tempBand;
	commutator_t *commutator = &COMMUTATOR;
	switch(address){
		case 0x0000:{
			_1_off();
			_2_off();
			_3_off();
			_4_off();
			setAttCommutator(0);
			setPaState(0);
			break;
		}
		case 0x0001:{
			_1_1();
			_2_off();
			_3_off();
			_4_off();
			setAttCommutator(CH1);
			setPaState(paBin1);
			POWER_LEDS1.pArrLedSt = arrLedAll[(uint8_t)commutator->channel[tempCh01].standart - 0x43][commutator->channel[tempCh01].band][ONE_CH];
			break;
		}
		case 0x0010:{
			_1_off();
			_2_1();
			_3_off();
			_4_off();
			setAttCommutator(CH2);
			setPaState(paBin1);
			POWER_LEDS1.pArrLedSt = arrLedAll[(uint8_t)commutator->channel[tempCh01].standart - 0x43][commutator->channel[tempCh01].band][ONE_CH];
			break;
		}
		case 0x0011:{
			_1_1();
			_2_1();
			_3_off();
			_4_off();
			setAttCommutator(CH1 | CH2);
			setPaState(paBin1);
			POWER_LEDS1.pArrLedSt = arrLedAll[(uint8_t)commutator->channel[tempCh01].standart - 0x43][commutator->channel[tempCh01].band][TWO_CH];
			break;
		}
		case 0x0300:{
			_1_off();
			_2_off();
			_3_3();
			_4_off();
			setAttCommutator(CH3);
			setPaState(paBin3);
			POWER_LEDS2.pArrLedSt = arrLedAll[(uint8_t)commutator->channel[tempCh23].standart - 0x43][commutator->channel[tempCh23].band][ONE_CH];
			break;
		}
		case 0x0301:{
			_1_1();
			_2_off();
			_3_3();
			_4_off();
			setAttCommutator(CH1 | CH3);
			setPaState(paBin1 | paBin3);
			POWER_LEDS1.pArrLedSt = arrLedAll[(uint8_t)commutator->channel[tempCh01].standart - 0x43][commutator->channel[tempCh01].band][ONE_CH];
			POWER_LEDS2.pArrLedSt = arrLedAll[(uint8_t)commutator->channel[tempCh23].standart - 0x43][commutator->channel[tempCh23].band][ONE_CH];
			break;
		}
		case 0x0310:{
			_1_off();
			_2_1();
			_3_3();
			_4_off();
			setAttCommutator(CH2 | CH3);
			setPaState(paBin1 | paBin3);
			POWER_LEDS1.pArrLedSt = arrLedAll[(uint8_t)commutator->channel[tempCh01].standart - 0x43][commutator->channel[tempCh01].band][ONE_CH];
			POWER_LEDS2.pArrLedSt = arrLedAll[(uint8_t)commutator->channel[tempCh23].standart - 0x43][commutator->channel[tempCh23].band][ONE_CH];
			break;
		}
		case 0x0311:{
			_1_1();
			_2_1();
			_3_3();
			_4_off();
			setAttCommutator(CH1 | CH2 | CH3);
			setPaState(paBin1 | paBin3);
			POWER_LEDS1.pArrLedSt = arrLedAll[(uint8_t)commutator->channel[tempCh01].standart - 0x43][commutator->channel[tempCh01].band][TWO_CH];
			POWER_LEDS2.pArrLedSt = arrLedAll[(uint8_t)commutator->channel[tempCh23].standart - 0x43][commutator->channel[tempCh23].band][ONE_CH];
			break;
		}
		case 0x3000:{
			_1_off();
			_2_off();
			_3_off();
			_4_3();
			setAttCommutator(CH4);
			setPaState(paBin3);
			POWER_LEDS2.pArrLedSt = arrLedAll[(uint8_t)commutator->channel[tempCh23].standart - 0x43][commutator->channel[tempCh23].band][ONE_CH];
			break;
		}
		case 0x3001:{
			_1_1();
			_2_off();
			_3_off();
			_4_3();
			setAttCommutator(CH1 | CH4);
			setPaState(paBin1 | paBin3);
			POWER_LEDS1.pArrLedSt = arrLedAll[(uint8_t)commutator->channel[tempCh01].standart - 0x43][commutator->channel[tempCh01].band][ONE_CH];
			POWER_LEDS2.pArrLedSt = arrLedAll[(uint8_t)commutator->channel[tempCh23].standart - 0x43][commutator->channel[tempCh23].band][ONE_CH];
			break;
		}
		case 0x3010:{
			_1_off();
			_2_1();
			_3_off();
			_4_3();
			setAttCommutator(CH2 | CH4);
			setPaState(paBin1 | paBin3);
			POWER_LEDS1.pArrLedSt = arrLedAll[(uint8_t)commutator->channel[tempCh01].standart - 0x43][commutator->channel[tempCh01].band][ONE_CH];
			POWER_LEDS2.pArrLedSt = arrLedAll[(uint8_t)commutator->channel[tempCh23].standart - 0x43][commutator->channel[tempCh23].band][ONE_CH];
			break;
		}
		case 0x3011:{
			_1_1();
			_2_1();
			_3_off();
			_4_3();
			setAttCommutator(CH1 | CH2 | CH4);
			setPaState(paBin1 | paBin3);
			POWER_LEDS1.pArrLedSt = arrLedAll[(uint8_t)commutator->channel[tempCh01].standart - 0x43][commutator->channel[tempCh01].band][TWO_CH];
			POWER_LEDS2.pArrLedSt = arrLedAll[(uint8_t)commutator->channel[tempCh23].standart - 0x43][commutator->channel[tempCh23].band][ONE_CH];
			break;
		}
		case 0x3300:{
			_1_off();
			_2_off();
			_3_3();
			_4_3();
			setAttCommutator(CH3 | CH4);
			setPaState(paBin3);
			POWER_LEDS2.pArrLedSt = arrLedAll[(uint8_t)commutator->channel[tempCh23].standart - 0x43][commutator->channel[tempCh23].band][TWO_CH];
			break;
		}
		case 0x3301:{
			_1_1();
			_2_off();
			_3_3();
			_4_3();
			setAttCommutator(CH1 | CH3 | CH4);
			setPaState(paBin1 | paBin3);
			POWER_LEDS1.pArrLedSt = arrLedAll[(uint8_t)commutator->channel[tempCh01].standart - 0x43][commutator->channel[tempCh01].band][ONE_CH];
			POWER_LEDS2.pArrLedSt = arrLedAll[(uint8_t)commutator->channel[tempCh23].standart - 0x43][commutator->channel[tempCh23].band][TWO_CH];
			break;
		}
		case 0x3310:{
			_1_off();
			_2_1();
			_3_3();
			_4_3();
			setAttCommutator(CH2 | CH3 | CH4);
			setPaState(paBin1 | paBin3);
			POWER_LEDS1.pArrLedSt = arrLedAll[(uint8_t)commutator->channel[tempCh01].standart - 0x43][commutator->channel[tempCh01].band][ONE_CH];
			POWER_LEDS2.pArrLedSt = arrLedAll[(uint8_t)commutator->channel[tempCh23].standart - 0x43][commutator->channel[tempCh23].band][TWO_CH];
			break;
		}
		case 0x3311:{
			_1_1();
			_2_1();
			_3_3();
			_4_3();
			setAttCommutator(CH1 | CH2 | CH3 | CH4);
			setPaState(paBin1 | paBin3);
			POWER_LEDS1.pArrLedSt = arrLedAll[(uint8_t)commutator->channel[tempCh01].standart - 0x43][commutator->channel[tempCh01].band][TWO_CH];
			POWER_LEDS2.pArrLedSt = arrLedAll[(uint8_t)commutator->channel[tempCh23].standart - 0x43][commutator->channel[tempCh23].band][TWO_CH];
			break;
		}
		default:{
			utils_sendDebugPGM(DEBUG_CH, _PAUSE, 0, 0);
			break;
		}
	}
}

const uint8_t table_1[] = {nul, pa1, nul, nul, nul, pa1, pa1, pa1, pa1, pa1, pa1, pa1, nul, nul, nul, nul};
const uint8_t table_2[] = {nul, nul, pa1, nul, nul, pa1, nul, nul, nul, pa1, pa1, pa1, pa1, pa1, pa1, nul};
const uint8_t table_3[] = {nul, nul, nul, pa3, nul, nul, pa3, nul, pa3, pa3, nul, pa3, pa3, nul, pa3, pa3};
const uint8_t table_4[] = {nul, nul, nul, nul, pa3, nul, nul, pa3, pa3, nul, pa3, pa3, nul, pa3, pa3, pa3};

uint16_t searchCombination(commutator_t *commutator){
	uint8_t size = sizeof(table_1);
	for (uint8_t i=0; i < size; i++){
		if (table_1[i] == commutator->channel[0].paNum && table_2[i] == commutator->channel[1].paNum &&
		table_3[i] == commutator->channel[2].paNum && table_4[i] == commutator->channel[3].paNum)
		return table_4[i] << 12 | table_3[i] << 8 | table_2[i] << 4 | table_1[i];
	}
	return NOCOMBINATION;
}
uint8_t findDuplicate(){
	uint8_t size = sizeof(table_1);
	for (uint8_t i=0; i < size; i++){
		for (uint8_t k= i+1; k < size; k++){
			if ((table_1[i] == table_1[k]) && (table_2[i] == table_2[k]) && (table_3[i] == table_3[k]) && (table_4[i] == table_4[k])) return i;
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

	spi_setReg(&SPID, &PORTH, REGISTERS.ledChState |= CH1, LED_CH_REG);		//set led 1 ch

	utils_sendDebugPGM(DEBUG_CH, _1_1P, 0, 0);
	utils_sendStDebug(&COMMUTATOR.channel[0].standart);
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

	spi_setReg(&SPID, &PORTH, REGISTERS.ledChState |= CH1, LED_CH_REG);		//set led 1 ch

	utils_sendDebugPGM(DEBUG_CH, _1_2P, 0, 0);
	utils_sendAnswerMain(DEBUG_CH, &COMMUTATOR.channel[0].standart, 0, 0);
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

	spi_setReg(&SPID, &PORTH, REGISTERS.ledChState |= CH1, LED_CH_REG);		//set led 1 ch

	utils_sendDebugPGM(DEBUG_CH, _1_3P, 0, 0);
	utils_sendStDebug(&COMMUTATOR.channel[0].standart);
}
void _1_off(){
	COMMUTATOR.sreg1_state_tx &= ~0b00011111;
	COMMUTATOR.sreg2_state_tx &= ~0b11000011;
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

	spi_setReg(&SPID, &PORTH, REGISTERS.ledChState &= ~CH1, LED_CH_REG);

	utils_sendDebugPGM(DEBUG_CH, _1_OFF, 0, 0);
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

	spi_setReg(&SPID, &PORTH, REGISTERS.ledChState |= CH2, LED_CH_REG);		//set led 2 ch

	utils_sendDebugPGM(DEBUG_CH, _2_1P, 0, 0);
	utils_sendStDebug(&COMMUTATOR.channel[1].standart);
}
void _2_2(){
	//COMMUTATOR.sreg1_state_tx &= ~0b00011111;
	COMMUTATOR.sreg1_state_tx =  0b01000000;

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

	spi_setReg(&SPID, &PORTH, REGISTERS.ledChState |= CH2, LED_CH_REG);		//set led 2 ch

	utils_sendDebugPGM(DEBUG_CH, _2_2P, 0, 0);
	utils_sendStDebug(&COMMUTATOR.channel[1].standart);
}
void _2_3(){
	//COMMUTATOR.sreg1_state_tx &= ~0b00011111;
	COMMUTATOR.sreg1_state_tx =  0b10000000;

	COMMUTATOR.sreg2_state_tx &= ~0b00110011;
	//COMMUTATOR.sreg2_state_tx |=  0b00000100;

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

	spi_setReg(&SPID, &PORTH, REGISTERS.ledChState |= CH2, LED_CH_REG);		//set led 2 ch

	utils_sendDebugPGM(DEBUG_CH, _2_3P, 0, 0);
	utils_sendStDebug(&COMMUTATOR.channel[1].standart);
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

	spi_setReg(&SPID, &PORTH, REGISTERS.ledChState &= ~CH2, LED_CH_REG);

	utils_sendDebugPGM(DEBUG_CH, _2_OFF, 0, 0);
}

void _3_1(){
	utils_sendDebugPGM(DEBUG_CH, _ABSENT, 0, 0);
}
void _3_2(){
	utils_sendDebugPGM(DEBUG_CH, _ABSENT, 0, 0);
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

	spi_setReg(&SPID, &PORTH, REGISTERS.ledChState |= CH3, LED_CH_REG);		//set led 3 ch

	utils_sendDebugPGM(DEBUG_CH, _3_3P, 0, 0);
	utils_sendStDebug(&COMMUTATOR.channel[2].standart);
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

	spi_setReg(&SPID, &PORTH, REGISTERS.ledChState |= CH3, LED_CH_REG);		//set led 3 ch

	utils_sendDebugPGM(DEBUG_CH, _3_2100P, 0, 0);
	utils_sendStDebug(&COMMUTATOR.channel[2].standart);
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

	spi_setReg(&SPID, &PORTH, REGISTERS.ledChState &= ~CH3, LED_CH_REG);

	utils_sendDebugPGM(DEBUG_CH, _3_OFF, 0, 0);
}

void _4_1(){
	utils_sendDebugPGM(DEBUG_CH, _ABSENT, 0, 0);
}
void _4_2(){
	utils_sendDebugPGM(DEBUG_CH, _ABSENT, 0, 0);
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

	spi_setReg(&SPID, &PORTH, REGISTERS.ledChState |= CH4, LED_CH_REG);		//set led 4 ch

	utils_sendDebugPGM(DEBUG_CH, _4_3P, 0, 0);
	utils_sendStDebug(&COMMUTATOR.channel[3].standart);
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

	spi_setReg(&SPID, &PORTH, REGISTERS.ledChState |= CH4, LED_CH_REG);		//set led 4 ch

	utils_sendDebugPGM(DEBUG_CH, _4_2100P, 0, 0);
	utils_sendStDebug(&COMMUTATOR.channel[3].standart);
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

	spi_setReg(&SPID, &PORTH, REGISTERS.ledChState &= ~CH4, LED_CH_REG);

	utils_sendDebugPGM(DEBUG_CH, _4_OFF, 0, 0);
}
void setAttCommutator(uint8_t channels){					//value4 = 0x3311 - 33-ch3, 11-ch1; value5 = 0x4422   44-ch4, 22-ch2
	uint16_t value4 = 0, value5 = 0;
	if ((channels & CH1) && (channels & CH2)){
		 value4 |= 0x0018;
		 value5 |= 0x0018;
	}
	if ((channels & CH3) && (channels & CH4)){
		value4 |= 0x1800;
		value5 |= 0x1800;
	}
	spi_setRegDouble(&SPID, &PORTF, COMMUTATOR.sreg4_state_att + value4, ST_SREG_SPI_4);
	spi_setRegDouble(&SPID, &PORTK, COMMUTATOR.sreg5_state_att + value5, ST_SREG_SPI_5);
	utils_sendDebugPGM(DEBUG_CH, _ATT_1, utils_hex8ToAscii16((COMMUTATOR.sreg4_state_att + value4) >> 1), 2);
	utils_sendDebugPGM(DEBUG_CH, _ATT_2, utils_hex8ToAscii16((COMMUTATOR.sreg5_state_att + value5) >> 1), 2);
	utils_sendDebugPGM(DEBUG_CH, _ATT_3, utils_hex8ToAscii16((COMMUTATOR.sreg4_state_att + value4) >> 9), 2);
	utils_sendDebugPGM(DEBUG_CH, _ATT_4, utils_hex8ToAscii16((COMMUTATOR.sreg5_state_att + value5) >> 9), 2);
	
	//utils_sendAnswerMain(DEBUG_CH, "\ns4=", utils_hex16ToAscii32((COMMUTATOR.sreg4_state_att + value4) >> 1), 4);
	//utils_sendAnswerMain(DEBUG_CH, "  s5=", utils_hex16ToAscii32((COMMUTATOR.sreg5_state_att + value5) >> 1), 4);
}
uint8_t checkInChannelState(){
	return COMMUTATOR.channel[0].paNum | COMMUTATOR.channel[1].paNum | COMMUTATOR.channel[2].paNum | COMMUTATOR.channel[3].paNum;
}