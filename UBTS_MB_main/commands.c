#include "COMMANDS.h"

uint8_t commands_decoder(fifo_t* fifo, buff_t *buffOut) {
	uint8_t command=0;
	if (((fifo->head - fifo->tail) & 0xff) > 0){
		while (1) {
			if (fifo->data[fifo->tail]=='%') {
				command=1;
				fifo->tail++;
				if(utils_isFifoEmpty(fifo)) return EMPTY_CMD;
			}
			if (command) {
				buffOut->command = (uint16_t)fifo->data[fifo->tail++]<<8;
				if(utils_isFifoEmpty(fifo)) return EMPTY_CMD;
				buffOut->command |= (uint16_t)fifo->data[fifo->tail++];
				if(utils_isFifoEmpty(fifo)) return EMPTY_CMD;
				if (fifo->data[fifo->tail] == '*') {
					fifo->tail++;
					return utils_ascii16ToHex8(buffOut->command);
				}
				else {
					uint8_t i = 0;
					do{
						if(utils_isFifoEmpty(fifo)) return EMPTY_CMD;
						buffOut->buffer[i++] = fifo->data[fifo->tail++];
						buffOut->length = i;
						if (i >= BUFF_SIZE_COMM_DATA) break;
					} while (fifo->data[fifo->tail] != '*');
					return utils_ascii16ToHex8(buffOut->command);
				}
			}
			else {
				fifo->tail++;
				return EMPTY_CMD;
			}
		}
	} else return EMPTY_CMD;
}
static bool commandValidation(uint8_t command, buff_t *commandBuff){
	bool valid = true;
	switch(command){
		case 0x75:{																				//%75aabbaabbaabb*	-	set mac
			buffer_mac[0] = utils_ascii16ToHex8(commandBuff->buffer[0] << 8 | commandBuff->buffer[1]);
			buffer_mac[1] = utils_ascii16ToHex8(commandBuff->buffer[2] << 8 | commandBuff->buffer[3]);
			buffer_mac[2] = utils_ascii16ToHex8(commandBuff->buffer[4] << 8 | commandBuff->buffer[5]);
			buffer_mac[3] = utils_ascii16ToHex8(commandBuff->buffer[6] << 8 | commandBuff->buffer[7]);
			buffer_mac[4] = utils_ascii16ToHex8(commandBuff->buffer[8] << 8 | commandBuff->buffer[9]);
			buffer_mac[5] = utils_ascii16ToHex8(commandBuff->buffer[10] << 8 | commandBuff->buffer[11]);
			
			if (commandBuff->length != 12) return false;
			//if (commandBuff->buffer[0] != ',') return false;
			break;
		}
		case 0x76:{								//%76,x,yy,z*		-  x-pa number[1-3], yy-band number[0-99], z-isActive[0-1] (1-true,0-false)
			uint8_t bandNumber = utils_ascii16ToHex8(commandBuff->buffer[3] << 8 | commandBuff->buffer[4]);
			uint8_t paNumber = commandBuff->buffer[1];
			uint8_t activeNumber = commandBuff->buffer[6];

			if (COMMUTATOR.nmIsOn) return false;
			if (commandBuff->length != 7) return false;
			if (bandNumber < 0 || bandNumber > 99) return false;
			if (paNumber < 1 || paNumber > 3) return false;
			if (activeNumber != 0 && activeNumber != 1) return false;
			break;
		}
		case 0xaa:{								//%aa,x,Yyy,z*	- x-input channel[1-4], Y-standart[C,G,U,L], yy-band[0-99], z-on or off[0-1]
			uint8_t band = utils_ascii16ToHex8((commandBuff->buffer[4] << 8) | commandBuff->buffer[5]);
			uint8_t standart = commandBuff->buffer[3];
			uint8_t inChannel = commandBuff->buffer[1] - 0x30;
			uint8_t isPaOn = commandBuff->buffer[7] - 0x30;
			uint8_t paNum;
			
			if (commandBuff->length != 8) return false;
			if (commandBuff->buffer[0] != ',') return false;
			if (commandBuff->buffer[2] != ',') return false;
			if (commandBuff->buffer[6] != ',') return false;
			if (band < 0 || band > 99) return false;
			paNum = getPaNum(band);
			if(paNum == 0) return false;
			if (standart != 'U' && standart != 'C' && standart != 'L' && standart != 'G') return false;
			if (inChannel < 1 || inChannel > 4) return false;
			if (isPaOn != 0 && isPaOn != 1) return false;
			break;
		}
	}
	return valid;
}
void command_exec(uint8_t command){
	switch (command){
		case 0x00:{																													//read software version
			utils_sendDebugPGM(MAIN_CH,_VERSION,0,0);
			utils_sendDebugPGM(DEBUG_CH,_VERSION,0,0);
			break;
		}
		/*case 0x02:{																													//set anime speed
		break;
		}*/
		case 0x01:{																													//GPS on
			gpsOn(true);
			break;
		}
		case 0x03:{																													//GPS off
			gpsOn(false);
			break;
		}
		case 0x04:{																													//temp board
			utils_sendAnswerMain(MAIN_CH, "\n%04*", utils_hexArrayToAsciiArray(BOARD.temperBuff, 2), 2);
			utils_sendDebugPGM(DEBUG_CH, _Tboard, utils_hex8ToDecAscii16(BOARD.temperBuff[0]), 2);
			break;
		}
		case 0x05:{																													//NM on
			nmOn(true);
			break;
		}
		case 0x06:{																													//NM off
			nmOn(false);
			break;
		}
		case 0x07:{																													//ina data bts
			utils_sendAnswerMain(MAIN_CH, "\n%07*", utils_hexArrayToAsciiArray(INA_BTS.voltageBuff, 2), 4);
			utils_sendDebugPGM(DEBUG_CH, _INA_VOLT, utils_hex2ArrayToDecAscii4Array(INA_BTS.voltageBuff), 4);
			break;
		}
		case 0x08:{																													//
			utils_sendAnswerMain(MAIN_CH, "\n%08*", utils_hexArrayToAsciiArray(INA_BTS.currentBuff, 2), 4);
			utils_sendDebugPGM(DEBUG_CH, _INA_CURRENT, utils_hex2ArrayToDecAscii4Array(INA_BTS.currentBuff), 4);
			break;
		}
		case 0x09:{																													//
			utils_sendAnswerMain(MAIN_CH, "\n%09*", utils_hexArrayToAsciiArray(INA_BTS.powerBuff, 2), 4);
			utils_sendDebugPGM(DEBUG_CH, _INA_POWER, utils_hex2ArrayToDecAscii4Array(INA_BTS.powerBuff), 4);
			break;
		}
		case 0x0a:{																													//ina data periphery
			utils_sendAnswerMain(MAIN_CH, "\n%0a*", utils_hexArrayToAsciiArray(INA_PERIPHERY.voltageBuff, 2), 4);
			utils_sendDebugPGM(DEBUG_CH, _INA_VOLT, utils_hex2ArrayToDecAscii4Array(INA_PERIPHERY.voltageBuff), 4);
			break;
		}
		case 0x0b:{																													//
			utils_sendAnswerMain(MAIN_CH, "\n%0b*", utils_hexArrayToAsciiArray(INA_PERIPHERY.currentBuff, 2), 4);
			utils_sendDebugPGM(DEBUG_CH, _INA_CURRENT, utils_hex2ArrayToDecAscii4Array(INA_PERIPHERY.currentBuff), 4);
			break;
		}
		case 0x0c:{																													//
			utils_sendAnswerMain(MAIN_CH, "\n%0c*", utils_hexArrayToAsciiArray(INA_PERIPHERY.powerBuff, 2), 4);
			utils_sendDebugPGM(DEBUG_CH, _INA_POWER, utils_hex2ArrayToDecAscii4Array(INA_PERIPHERY.powerBuff), 4);
			break;
		}
		case 0x0d:{
			utils_sendAnswerMain(MAIN_CH, "\n%07*", utils_hexArrayToAsciiArray(INA_BTS.voltageBuff, 2), 4);
			utils_sendDebugPGM(DEBUG_CH, _INA_VOLT, utils_hex2ArrayToDecAscii4Array(INA_BTS.voltageBuff), 4);
			utils_sendAnswerMain(MAIN_CH, "\n%08*", utils_hexArrayToAsciiArray(INA_BTS.currentBuff, 2), 4);
			utils_sendDebugPGM(DEBUG_CH, _INA_CURRENT, utils_hex2ArrayToDecAscii4Array(INA_BTS.currentBuff), 4);
			utils_sendAnswerMain(MAIN_CH, "\n%09*", utils_hexArrayToAsciiArray(INA_BTS.powerBuff, 2), 4);
			utils_sendDebugPGM(DEBUG_CH, _INA_POWER, utils_hex2ArrayToDecAscii4Array(INA_BTS.powerBuff), 4);
			utils_sendAnswerMain(MAIN_CH, "\n%0a*", utils_hexArrayToAsciiArray(INA_PERIPHERY.voltageBuff, 2), 4);
			utils_sendDebugPGM(DEBUG_CH, _INA_VOLT, utils_hex2ArrayToDecAscii4Array(INA_PERIPHERY.voltageBuff), 4);
			utils_sendAnswerMain(MAIN_CH, "\n%0b*", utils_hexArrayToAsciiArray(INA_PERIPHERY.currentBuff, 2), 4);
			utils_sendDebugPGM(DEBUG_CH, _INA_CURRENT, utils_hex2ArrayToDecAscii4Array(INA_PERIPHERY.currentBuff), 4);
			utils_sendAnswerMain(MAIN_CH, "\n%0c*", utils_hexArrayToAsciiArray(INA_PERIPHERY.powerBuff, 2), 4);
			utils_sendDebugPGM(DEBUG_CH, _INA_POWER, utils_hex2ArrayToDecAscii4Array(INA_PERIPHERY.powerBuff), 4);
			break;
		}
		case 0x0f:{																													//set start wifi
			uint8_t temp;
			utils_sendAnswerMain(DEBUG_CH, 0x00, COMMAND.buffer, COMMAND.length);
			temp = utils_ascii16ToHex8(COMMAND.buffer[1] << 8 | COMMAND.buffer[2]);				//0 or 1
			if (temp) utils_sendDebugPGM(DEBUG_CH, _WIFI_ON, 0, 0);
			else utils_sendDebugPGM(DEBUG_CH, _WIFI_OFF, 0, 0);
			read_writeEEPROMBuff(WIFI_ALWAYS_ON, &temp, 1);
			break;
		}
		case 0x10:{																													//pa1 out power adc
			utils_sendDebugPGM(DEBUG_CH, _ADC_OUT_PA_1, utils_hex16ToDecAscii32(ADC_PA_OUT_1.value), 4);
			utils_sendAnswerMain(MAIN_CH, "\n%10*", utils_hex16ToAscii32(ADC_PA_OUT_1.value), 4);
			break;
		}
		case 0x11:{																													//pa2 out power adc
			utils_sendDebugPGM(DEBUG_CH, _ADC_OUT_PA_2, utils_hex16ToDecAscii32(ADC_PA_OUT_2.value), 4);
			utils_sendAnswerMain(MAIN_CH, "\n%11*", utils_hex16ToAscii32(ADC_PA_OUT_2.value), 4);
			break;
		}
		case 0x12:{																													//pa3 out power adc
			utils_sendDebugPGM(DEBUG_CH, _ADC_OUT_PA_3, utils_hex16ToDecAscii32(ADC_PA_OUT_3.value), 4);
			utils_sendAnswerMain(MAIN_CH, "\n%12*", utils_hex16ToAscii32(ADC_PA_OUT_3.value), 4);
			break;
		}
		/*case 0x13:{																													//pa4 out power adc
		utils_sendDebugPGM(DEBUG_CH, _ADC_OUT_PA_4, utils_hex16ToDecAscii32(ADC_PA_OUT_4.value), 4);
		utils_sendAnswerMain(MAIN_CH, "\n%13*", utils_hex16ToAscii32(ADC_PA_OUT_4.value), 4);
		break;
		}*/
		case 0x14:{																													//all pa out power adc
			utils_sendDebugPGM(DEBUG_CH, _ADC_OUT_PA_1, utils_hex16ToDecAscii32(ADC_PA_OUT_1.value), 4);
			utils_sendAnswerMain(MAIN_CH, "\n%10*", utils_hex16ToAscii32(ADC_PA_OUT_1.value), 4);
			utils_sendDebugPGM(DEBUG_CH, _ADC_OUT_PA_2, utils_hex16ToDecAscii32(ADC_PA_OUT_2.value), 4);
			utils_sendAnswerMain(MAIN_CH, "\n%11*", utils_hex16ToAscii32(ADC_PA_OUT_2.value), 4);
			utils_sendDebugPGM(DEBUG_CH, _ADC_OUT_PA_3, utils_hex16ToDecAscii32(ADC_PA_OUT_3.value), 4);
			utils_sendAnswerMain(MAIN_CH, "\n%12*", utils_hex16ToAscii32(ADC_PA_OUT_3.value), 4);
			break;
		}
		case 0x15:{																													//read serial number of the device
			utils_sendAnswerMain(MAIN_CH, "\n%15*", utils_hexArrayToAsciiArray(buffer_serialNum,4), 8);
			utils_sendAnswerMain(DEBUG_CH, "\nserial= ", utils_hexArrayToAsciiArray(buffer_serialNum,4), 8);
			//utils_sendDebug(DEBUG_CH, (uint8_t*)"\nserial= ", 9, utils_hexArrayToAsciiArray(buffer_serialNum,4), 8);
			break;
		}
		case 0x16:{																													//temp pa0
			utils_sendAnswerMain(MAIN_CH, "\n%16*", utils_hexArrayToAsciiArray(PA1.temperBuff, 2), 2);
			utils_sendDebugPGM(DEBUG_CH, _Tpa1, utils_hex8ToDecAscii16(PA1.temperBuff[0]), 2);
			break;
		}
		case 0x17:{																													//temp pa1
			utils_sendAnswerMain(MAIN_CH, "\n%17*", utils_hexArrayToAsciiArray(PA2.temperBuff, 2), 2);
			utils_sendDebugPGM(DEBUG_CH, _Tpa2, utils_hex8ToDecAscii16(PA2.temperBuff[0]), 2);
			break;
		}
		case 0x18:{																													//temp pa2
			utils_sendAnswerMain(MAIN_CH, "\n%18*", utils_hexArrayToAsciiArray(PA3.temperBuff, 2), 2);
			utils_sendDebugPGM(DEBUG_CH, _Tpa3, utils_hex8ToDecAscii16(PA3.temperBuff[0]), 2);
			break;
		}
		/*case 0x19:{																													//temp pa3
		utils_sendAnswerMain(MAIN_CH, "\n%19*", utils_hexArrayToAsciiArray(PA4.temperBuff, 2), 2);
		utils_sendDebugPGM(DEBUG_CH, _Tpa4, utils_hex8ToDecAscii16(PA4.temperBuff[0]), 2);
		break;
		}*/
		case 0x1a:{																													//temp all
			utils_sendAnswerMain(MAIN_CH, "\n%04*", utils_hexArrayToAsciiArray(BOARD.temperBuff, 2), 2);
			utils_sendDebugPGM(DEBUG_CH, _Tboard, utils_hex8ToDecAscii16(BOARD.temperBuff[0]), 2);
			utils_sendAnswerMain(MAIN_CH, "\n%16*", utils_hexArrayToAsciiArray(PA1.temperBuff, 2), 2);
			utils_sendDebugPGM(DEBUG_CH, _Tpa1, utils_hex8ToDecAscii16(PA1.temperBuff[0]), 2);
			utils_sendAnswerMain(MAIN_CH, "\n%17*", utils_hexArrayToAsciiArray(PA2.temperBuff, 2), 2);
			utils_sendDebugPGM(DEBUG_CH, _Tpa2, utils_hex8ToDecAscii16(PA2.temperBuff[0]), 2);
			utils_sendAnswerMain(MAIN_CH, "\n%18*", utils_hexArrayToAsciiArray(PA3.temperBuff, 2), 2);
			utils_sendDebugPGM(DEBUG_CH, _Tpa3, utils_hex8ToDecAscii16(PA3.temperBuff[0]), 2);
			break;
		}
		case 0x1b:{																													//pa1 bw power adc
			utils_sendDebugPGM(DEBUG_CH, _ADC_BW_PA_1, utils_hex16ToDecAscii32(ADC_PA_BW_1.value), 4);
			utils_sendAnswerMain(MAIN_CH, "\n%1b*", utils_hex16ToAscii32(ADC_PA_BW_1.value), 4);
			break;
		}
		case 0x1c:{																													//pa2 bw power adc
			utils_sendDebugPGM(DEBUG_CH, _ADC_BW_PA_2, utils_hex16ToDecAscii32(ADC_PA_BW_2.value), 4);
			utils_sendAnswerMain(MAIN_CH, "\n%1c*", utils_hex16ToAscii32(ADC_PA_BW_2.value), 4);
			break;
		}
		case 0x1d:{																													//pa3 bw power adc
			utils_sendDebugPGM(DEBUG_CH, _ADC_BW_PA_3, utils_hex16ToDecAscii32(ADC_PA_BW_3.value), 4);
			utils_sendAnswerMain(MAIN_CH, "\n%1d*", utils_hex16ToAscii32(ADC_PA_BW_3.value), 4);
			break;
		}
		/*case 0x1e:{																													//pa4 bw power adc
		utils_sendDebugPGM(DEBUG_CH, _ADC_BW_PA_4, utils_hex16ToDecAscii32(ADC_PA_BW_4.value), 4);
		utils_sendAnswerMain(MAIN_CH, "\n%1e*", utils_hex16ToAscii32(ADC_PA_BW_4.value), 4);
		break;
		}*/
		case 0x1f:{																													//all pa bw power adc
			utils_sendDebugPGM(DEBUG_CH, _ADC_BW_PA_1, utils_hex16ToDecAscii32(ADC_PA_BW_1.value), 4);
			utils_sendAnswerMain(MAIN_CH, "\n%1b*", utils_hex16ToAscii32(ADC_PA_BW_1.value), 4);
			utils_sendDebugPGM(DEBUG_CH, _ADC_BW_PA_2, utils_hex16ToDecAscii32(ADC_PA_BW_2.value), 4);
			utils_sendAnswerMain(MAIN_CH, "\n%1c*", utils_hex16ToAscii32(ADC_PA_BW_2.value), 4);
			utils_sendDebugPGM(DEBUG_CH, _ADC_BW_PA_3, utils_hex16ToDecAscii32(ADC_PA_BW_3.value), 4);
			utils_sendAnswerMain(MAIN_CH, "\n%1d*", utils_hex16ToAscii32(ADC_PA_BW_3.value), 4);
			//command_exec(0x1e);
			break;
		}
		/*case 0x20:{																												//write command %20*
		read_writeEEPROMBuff(LENGTH_21,&COMMAND.length,1);
		read_writeEEPROMBuff(STRING_21,COMMAND.buffer,COMMAND.length);
		utils_sendAnswer(MAIN_CH,(uint8_t*)"\n%20*", COMMAND.buffer,COMMAND.length);
		utils_sendAnswer(DEBUG_CH,(uint8_t*)"\n%20*", COMMAND.buffer,COMMAND.length);
		break;
		}
		case 0x21:{																													//read command %21*
		utils_sendAnswer(MAIN_CH,(uint8_t*)"\n%21*", COMMAND_21.buffer, COMMAND_21.length);
		utils_sendAnswer(DEBUG_CH,(uint8_t*)"\n%21*", COMMAND_21.buffer, COMMAND_21.length);
		break;
		}
		case 0x3a:{																													//write command %3a*
		read_writeEEPROMBuff(LENGTH_3d,&COMMAND.length,1);
		read_writeEEPROMBuff(STRING_3d,COMMAND.buffer,COMMAND.length);
		utils_sendAnswer(MAIN_CH,(uint8_t*)"\n%3a*", COMMAND.buffer,COMMAND.length);
		utils_sendAnswer(DEBUG_CH,(uint8_t*)"\n%3a*", COMMAND.buffer,COMMAND.length);
		break;
		}
		case 0x3d:{																													//read command %3d*
		utils_sendAnswer(MAIN_CH,(uint8_t*)"\n%3d*", COMMAND_3d.buffer, COMMAND_3d.length);
		utils_sendAnswer(DEBUG_CH,(uint8_t*)"\n%3d*", COMMAND_3d.buffer, COMMAND_3d.length);
		break;
		}*/
		//******************************************NM*******************************************
		case 0x5f:{																											//send nm command
			utils_sendAnswerMain(DEBUG_CH, "\n%5f*", 0, 0);
			for (uint8_t i=0; i<COMMAND.length; i++){
				FIFO_nmChRx.data[FIFO_nmChRx.head++] = COMMAND.buffer[i];
			}
			FIFO_nmChRx.data[FIFO_nmChRx.head++] = 0x0d;
			FIFO_nmChRx.data[FIFO_nmChRx.head++] = 0x0a;
			break;
		}
		//***************************************tuning att****************************************
		case 0x60:{																											//set ch1 att
			uint8_t temp;
			utils_sendAnswerMain(DEBUG_CH, "\natt= ", COMMAND.buffer, COMMAND.length);
			temp = utils_ascii16ToHex8(COMMAND.buffer[1] << 8 | COMMAND.buffer[2]) << 1;
			COMMUTATOR.sreg4_state_att &= ~0x00ff;
			COMMUTATOR.sreg4_state_att |= temp;
			spi_setRegDouble(&SPID, &PORTF, COMMUTATOR.sreg4_state_att, ST_SREG_SPI_4);
			read_writeEEPROMBuff(ATT_1_EEPR, &temp, 1);
			break;
		}
		case 0x61:{																											//set ch2 att
			uint8_t temp;
			utils_sendAnswerMain(DEBUG_CH, "\natt= ", COMMAND.buffer, COMMAND.length);
			temp = utils_ascii16ToHex8(COMMAND.buffer[1] << 8 | COMMAND.buffer[2]) << 1;
			COMMUTATOR.sreg5_state_att &= ~0x00ff;
			COMMUTATOR.sreg5_state_att |= temp;
			spi_setRegDouble(&SPID, &PORTK, COMMUTATOR.sreg5_state_att, ST_SREG_SPI_5);
			read_writeEEPROMBuff(ATT_2_EEPR, &temp, 1);
			break;
		}
		case 0x62:{																											//set ch3 att
			uint8_t temp;
			utils_sendAnswerMain(DEBUG_CH, "\natt= ", COMMAND.buffer, COMMAND.length);
			temp = utils_ascii16ToHex8(COMMAND.buffer[1] << 8 | COMMAND.buffer[2]) << 1;
			COMMUTATOR.sreg4_state_att &= ~0xff00;
			COMMUTATOR.sreg4_state_att |= temp << 8;
			spi_setRegDouble(&SPID, &PORTF, COMMUTATOR.sreg4_state_att, ST_SREG_SPI_4);
			read_writeEEPROMBuff(ATT_3_EEPR, &temp , 1);
			break;
		}
		case 0x63:{																											//set ch4 att
			uint8_t temp;
			utils_sendAnswerMain(DEBUG_CH, "\natt= ", COMMAND.buffer, COMMAND.length);
			temp = utils_ascii16ToHex8(COMMAND.buffer[1] << 8 | COMMAND.buffer[2]) << 1;
			COMMUTATOR.sreg5_state_att &= ~0xff00;
			COMMUTATOR.sreg5_state_att |= temp << 8;
			spi_setRegDouble(&SPID, &PORTK, COMMUTATOR.sreg5_state_att, ST_SREG_SPI_5);
			read_writeEEPROMBuff(ATT_4_EEPR, &temp, 1);
			break;
		}
		case 0x64:{																											//read all att
			utils_sendDebugPGM(DEBUG_CH, _ATT_1, utils_hex8ToAscii16(COMMUTATOR.sreg4_state_att >> 1), 2);
			utils_sendDebugPGM(DEBUG_CH, _ATT_2, utils_hex8ToAscii16(COMMUTATOR.sreg5_state_att >> 1), 2);
			utils_sendDebugPGM(DEBUG_CH, _ATT_3, utils_hex8ToAscii16(COMMUTATOR.sreg4_state_att >> 9), 2);
			utils_sendDebugPGM(DEBUG_CH, _ATT_4, utils_hex8ToAscii16(COMMUTATOR.sreg5_state_att >> 9), 2);
			break;
		}
		///////////////////////holding on power/////////////////////////////
		case DC_DC_ON:{																										//hold power dc-dc
			MCU_ON_DCDC_RELAYS_VDC_IN;		//PORTK.OUTSET = PIN4_bm;
			break;
		}
		case DC_DC_OFF:{
			utils_sendDebugPGM(DEBUG_CH, _OFF, 0, 0);
			MCU_OFF_DCDC_RELAYS_VDC_IN;		//PORTK.OUTCLR = PIN4_bm;
			break;
		}
		case 0x72:{																											//go to offMode function
			fpProgModeVar = (fpProgMode)fpProgModeTable[2];
			break;
		}
		case 0x73:{																											//go to sendMode function instead dc-dc off
			fpProgModeVar = (fpProgMode)fpProgModeTable[1];
			break;
		}
		//********************************************************************************************************
		case 0x74:{																				//read mac
			utils_sendAnswerMain(MAIN_CH, "\n%74*", utils_hexArrayToAsciiArray(buffer_mac, 6), 12);
			utils_sendAnswerMain(DEBUG_CH, "\nmac= ", utils_hexArrayToAsciiArray(buffer_mac, 6), 12);
			break;
		}
		case 0x75:{																				//%75aabbaabbaabb*	-	set mac
			buffer_mac[0] = utils_ascii16ToHex8(COMMAND.buffer[0] << 8 | COMMAND.buffer[1]);
			buffer_mac[1] = utils_ascii16ToHex8(COMMAND.buffer[2] << 8 | COMMAND.buffer[3]);
			buffer_mac[2] = utils_ascii16ToHex8(COMMAND.buffer[4] << 8 | COMMAND.buffer[5]);
			buffer_mac[3] = utils_ascii16ToHex8(COMMAND.buffer[6] << 8 | COMMAND.buffer[7]);
			buffer_mac[4] = utils_ascii16ToHex8(COMMAND.buffer[8] << 8 | COMMAND.buffer[9]);
			buffer_mac[5] = utils_ascii16ToHex8(COMMAND.buffer[10] << 8 | COMMAND.buffer[11]);
			
			if (commandValidation(0x75, &COMMAND)){
				read_writeEEPROMBuff(MAC_EEP, buffer_mac, 6);
				utils_sendAnswerMain(MAIN_CH, "\n%75*", utils_hexArrayToAsciiArray(buffer_mac, 6), 12);
				utils_sendAnswerMain(DEBUG_CH, "\nmac= ", utils_hexArrayToAsciiArray(buffer_mac, 6), 12);
			}
			break;
		}
		case 0x76:{									//%76,x,yy,z*		-  x-pa number, yy-band number, z-isActive (1-true,0-false)
			tunePa(&COMMAND);
			break;
		}
		case 0x77:{																									//read all PA info
			utils_sendDebugPGM(DEBUG_CH, _PA1_ADDR, utils_hex8ToAscii16(PA1.addrTWI), 2);
			utils_sendDebugPGM(DEBUG_CH, _PA1_BAND, utils_hex8ToAscii16(PA1.band), 2);
			utils_sendDebugPGM(DEBUG_CH, _PA1_FANPIN, utils_hex8ToAscii16(PA1.fanPin), 2);
			utils_sendDebugPGM(DEBUG_CH, _PA1_ISACTIVE, utils_hex8ToAscii16(PA1.isValid), 2);
			break;
		}
		case 0x78:{																									//read all PA info
			utils_sendDebugPGM(DEBUG_CH, _PA2_ADDR, utils_hex8ToAscii16(PA2.addrTWI), 2);
			utils_sendDebugPGM(DEBUG_CH, _PA2_BAND, utils_hex8ToAscii16(PA2.band), 2);
			utils_sendDebugPGM(DEBUG_CH, _PA2_FANPIN, utils_hex8ToAscii16(PA2.fanPin), 2);
			utils_sendDebugPGM(DEBUG_CH, _PA2_ISACTIVE, utils_hex8ToAscii16(PA2.isValid), 2);
			break;
		}
		case 0x79:{																									//read all PA info
			utils_sendDebugPGM(DEBUG_CH, _PA3_ADDR, utils_hex8ToAscii16(PA3.addrTWI), 2);
			utils_sendDebugPGM(DEBUG_CH, _PA3_BAND, utils_hex8ToAscii16(PA3.band), 2);
			utils_sendDebugPGM(DEBUG_CH, _PA3_FANPIN, utils_hex8ToAscii16(PA3.fanPin), 2);
			utils_sendDebugPGM(DEBUG_CH, _PA3_ISACTIVE, utils_hex8ToAscii16(PA3.isValid), 2);
			break;
		}
		/*case 0x7a:{																									//read all PA info
		utils_sendDebugPGM(DEBUG_CH, _PA4_ADDR, utils_hex8ToAscii16(PA4.addrTWI), 2);
		utils_sendDebugPGM(DEBUG_CH, _PA4_BAND, utils_hex8ToAscii16(PA4.band), 2);
		utils_sendDebugPGM(DEBUG_CH, _PA4_FANPIN, utils_hex8ToAscii16(PA4.fanPin), 2);
		utils_sendDebugPGM(DEBUG_CH, _PA4_ISACTIVE, utils_hex8ToAscii16(PA4.isValid), 2);
		break;
		}*/
		//********************************************************************************************************
		case 0xaa:{																//%aa,x,Yyy,z*	- x-input channel, Y-standart, yy-band, z-on or off
			uint8_t band = utils_ascii16ToHex8(COMMAND.buffer[4] << 8 | COMMAND.buffer[5]);
			uint8_t standart = COMMAND.buffer[3];
			uint8_t inChannel = COMMAND.buffer[1] & 0x0f;
			uint8_t isPaOn = COMMAND.buffer[7] & 0x0f;
			uint8_t combination;
			uint8_t paNum;
			
			if (!commandValidation(0xaa, &COMMAND)){
				utils_sendDebugPGM(MAIN_CH, _ABSENT, 0, 0);
				utils_sendDebugPGM(DEBUG_CH, _ABSENT, 0, 0);
			}
			else if (COMMUTATOR.nmIsOn && isPaOn == 1) {
				utils_sendDebugPGM(MAIN_CH, _NOTALLOW, 0, 0);
				utils_sendDebugPGM(DEBUG_CH, _NOTALLOW, 0, 0);
			}
			else{
				paNum = getPaNum(band);
				setChInCommutator(inChannel, paNum, standart, isPaOn);
				combination = searchCombination(&COMMUTATOR);
				if (commutator_decoder(combination)){
					utils_sendDebugPGM(DEBUG_CH, _COMBINATION, utils_hex8ToAscii16(combination), 2);
					utils_sendAnswerMain(MAIN_CH, "\n%aa*", COMMAND.buffer, COMMAND.length);
				}else setChInCommutator(inChannel, paNum, standart, 0);
			}
			break;
		}
		//**************************************************************************************************
		case 0xe7:{																													//write command %e7*
			read_writeEEPROMBuff(LENGTH_e8, &COMMAND.length,1);
			read_writeEEPROMBuff(STRING_e8, COMMAND.buffer, COMMAND.length);
			read_eeprBuff(LENGTH_e8, &COMMAND_e8.length, 1);
			read_eeprBuff(STRING_e8, COMMAND_e8.buffer, COMMAND_e8.length);
			utils_sendAnswerMain(MAIN_CH, "\n%e7*", COMMAND.buffer, COMMAND.length);
			utils_sendAnswerMain(DEBUG_CH + 10, "\n%e7*", COMMAND.buffer, COMMAND.length);
			break;
		}
		case 0xe8:{																													//read command %e8*
			utils_sendAnswerMain(MAIN_CH, "\n%e8*", COMMAND_e8.buffer, COMMAND_e8.length);
			utils_sendAnswerMain(DEBUG_CH + 10, "\n%e8*", COMMAND_e8.buffer, COMMAND_e8.length);
			break;
		}
		/****** nothing to do, don't use ******/
		case 0xfd:{
			break;
		}
		/**************************************/
		case 0xfe:{																								//jump to bootloader
			utils_sendAnswerMain(MAIN_CH, "\n%fe*", 0, 0);
			//utils_sendDebugPGM(DEBUG_CH, _JMP_BOOTLOADER, 0, 0);
			_delay_ms(500);
			pBootloader=(void(*)())BOOT_SECTION;
			EIND = 1;
			pBootloader();
			break;
		}
		case 0xff:{																								//mcu reboot
			utils_sendAnswerMain(MAIN_CH, "\n%ff*", 0, 0);
			//utils_sendDebugPGM(DEBUG_CH, _MCU_REBOOT, 0, 0);
			_delay_ms(500);
			pBootloader=(void(*)())RESET_SECTION;
			EIND = 0;
			pBootloader();
			break;
		}
	}
}
void setChInCommutator(uint8_t inChannel, uint8_t paNum, uint8_t standart, uint8_t isPaOn){
	paNum = (isPaOn == 1) ? paNum : 0;
	standart = (isPaOn == 1) ? standart : 0;
	if (inChannel == 1) {
		COMMUTATOR.ch_1 = paNum;
		COMMUTATOR.standart_ch_1 = standart;
	}
	else if (inChannel == 2) {
		COMMUTATOR.ch_2 = paNum;
		COMMUTATOR.standart_ch_2 = standart;
	}
	else if (inChannel == 3) {
		COMMUTATOR.ch_3 = paNum;
		COMMUTATOR.standart_ch_3 = standart;
	}
	else if (inChannel == 4) {
		COMMUTATOR.ch_4 = paNum;
		COMMUTATOR.standart_ch_4 = standart;
	}
}
uint8_t getPaNum(uint8_t band){
	uint8_t temp = 0;
	if (PA1.band == band && PA1.isValid){
		temp |= PA1.channel;
	}
	if (PA2.band == band && PA2.isValid) {
		temp |= PA2.channel;
	}
	if (PA3.band == band && PA3.isValid) {
		temp |= PA3.channel;
	}
	/*if (PA4.band == band) {
	temp |= PA4.channel;
	}*/
	return temp;
}
void setPaState(uint8_t temp){
	paOn(&PA1, temp & 0x01);
	paOn(&PA2, temp & 0x02);
	paOn(&PA3, temp & 0x04);
	//paOn(&PA4, temp & 0x08);
}
void paOn(twi_device_t* pPa, bool isOn){
	if (isOn && pPa->isValid == 1)	{
		spi_setReg(&SPIC, &PORTK, REGISTERS.paState |= (1 << pPa->paPin), MCU_SREG_PA);
		//spi_setReg(&SPID, &PORTH, REGISTERS.ledChState |= (1 << pPa->paPin), LED_CH_REG);
		pPa->isOnState = 1;
	}
	else {
		spi_setReg(&SPIC, &PORTK, REGISTERS.paState &= ~(1 << pPa->paPin), MCU_SREG_PA);
		//spi_setReg(&SPID, &PORTH, REGISTERS.ledChState &= ~(1 << pPa->paPin), LED_CH_REG);
		pPa->isOnState = 0;
	}
	utils_sendDebugPGM(DEBUG_CH, pPa->name, utils_hex8ToAscii16(pPa->isOnState), 2);
}
void nmOn(bool isOn){
	if (isOn) {
		if (PA1.isOnState || PA2.isOnState || PA3.isOnState) {
			utils_sendDebugPGM(MAIN_CH, _NOTALLOW, 0, 0);
			utils_sendDebugPGM(DEBUG_CH, _NOTALLOW, 0, 0);
		}
		else{
			COMMUTATOR.nmIsOn = true;
			spi_setReg(&SPIC, &PORTK, REGISTERS.nmGpsWifiPpsState |= NM_ON, MCU_SREG_NM_GPS);		//on power for telit
			COMMUTATOR.sreg1_state_rx = 0b00010000;
			COMMUTATOR.sreg2_state_rx &= ~0b01110011;
			COMMUTATOR.sreg2_state_rx |=  0b10000000;
			COMMUTATOR.sreg3_state_rx &= ~0b11110000;
			if (!checkInChannelState()){
				COMMUTATOR.sreg3_state_rx &= ~0b00001111;
			}
			spi_setReg(&SPID, &PORTJ, COMMUTATOR.sreg1_state_rx, RX_SREG_SPI_1);
			spi_setReg(&SPID, &PORTJ, COMMUTATOR.sreg2_state_rx, RX_SREG_SPI_2);
			spi_setReg(&SPID, &PORTJ, COMMUTATOR.sreg3_state_rx, RX_SREG_SPI_3);
			
			utils_sendAnswerMain(MAIN_CH, "\n%05*", 0, 0);
			utils_sendDebugPGM(DEBUG_CH, _NM_ON, 0, 0);
		}
	}
	else {
		COMMUTATOR.nmIsOn = false;
		spi_setReg(&SPIC, &PORTK, REGISTERS.nmGpsWifiPpsState &= ~NM_ON, MCU_SREG_NM_GPS);		//off power for telit
		
		COMMUTATOR.sreg1_state_rx = 0b00000000;
		COMMUTATOR.sreg2_state_rx &= ~0b00110011;
		COMMUTATOR.sreg3_state_rx &= ~0b10010000;
		if (!checkInChannelState()){
			COMMUTATOR.sreg3_state_rx &= ~0b00001111;
		}
		spi_setReg(&SPID, &PORTJ, COMMUTATOR.sreg1_state_rx, RX_SREG_SPI_1);
		spi_setReg(&SPID, &PORTJ, COMMUTATOR.sreg2_state_rx, RX_SREG_SPI_2);
		spi_setReg(&SPID, &PORTJ, COMMUTATOR.sreg3_state_rx, RX_SREG_SPI_3);
		
		utils_sendAnswerMain(MAIN_CH, "\n%06*", 0, 0);
		utils_sendDebugPGM(DEBUG_CH, _NM_OFF, 0, 0);
	}
}
void gpsOn(bool isOn){
	if (isOn) {
		spi_setReg(&SPIC, &PORTK, REGISTERS.nmGpsWifiPpsState |= GPS_ON, MCU_SREG_NM_GPS);
		utils_sendAnswerMain(MAIN_CH, "\n%01*", 0, 0);
		utils_sendDebugPGM(DEBUG_CH, _GPS_ON, 0, 0);
	}
	else {
		spi_setReg(&SPIC, &PORTK, REGISTERS.nmGpsWifiPpsState &= ~GPS_ON, MCU_SREG_NM_GPS);
		utils_sendAnswerMain(MAIN_CH, "\n%03*", 0, 0);
		utils_sendDebugPGM(DEBUG_CH, _GPS_OFF, 0, 0);
	}
}
static inline uint8_t command_scanTwi(twi_device_t* pPA){
	TWI_t *twi;
	if (pPA == &PA1 || pPA == &PA2) twi = &TWID;
	else twi = &TWIF;
	TRANSFER.pointer = TEMP_base;
	pPA->addrTWI = TEMP_base;
	pPA->temperBuff[0] = 0;
	pPA->isValid = 0;
	
	for (uint8_t i=0; i<8; i++){
		twi_start(twi, pPA, false, 2);
		if (pPA->temperBuff[0] > 0) {
			pPA->isValid = 1;
			break;
		}
		pPA->addrTWI++;
	}
	
	if (pPA->isValid != 1) pPA->addrTWI = 0;
	return pPA->addrTWI;
}
void tunePa(buff_t *commandBuff){
	uint8_t bandNumber = utils_ascii16ToHex8(COMMAND.buffer[3] << 8 | COMMAND.buffer[4]);
	uint8_t paNumber = COMMAND.buffer[1] & 0x0f;
	uint8_t activeNumber = COMMAND.buffer[6] & 0x0f;
	
	twi_device_t *pPA;
	uint16_t eeprI2c = 0;
	uint16_t eeprBand = 0, eeprValid = 0;
	
	uint8_t *pADDR, *pBAND, *pFANPIN, *pISACTIVE;
	
	switch(paNumber){
		case 1:{
			pPA = &PA1;
			eeprI2c = I2C_PA1_EEPR;
			eeprBand = BAND_PA1_EEPR;
			eeprValid = VALID_PA1_EEPR;
			pADDR = (uint8_t *)_PA1_ADDR;
			pBAND = (uint8_t *)_PA1_BAND;
			pFANPIN = (uint8_t *)_PA1_FANPIN;
			pISACTIVE = (uint8_t *)_PA1_ISACTIVE;
			break;
		}
		case 2:{
			pPA = &PA2;
			eeprI2c = I2C_PA2_EEPR;
			eeprBand = BAND_PA2_EEPR;
			eeprValid = VALID_PA2_EEPR;
			pADDR = (uint8_t *)_PA2_ADDR;
			pBAND = (uint8_t *)_PA2_BAND;
			pFANPIN = (uint8_t *)_PA2_FANPIN;
			pISACTIVE = (uint8_t *)_PA2_ISACTIVE;
			break;
		}
		case 3:{
			pPA = &PA3;
			eeprI2c = I2C_PA3_EEPR;
			eeprBand = BAND_PA3_EEPR;
			eeprValid = VALID_PA3_EEPR;
			pADDR = (uint8_t *)_PA3_ADDR;
			pBAND = (uint8_t *)_PA3_BAND;
			pFANPIN = (uint8_t *)_PA3_FANPIN;
			pISACTIVE = (uint8_t *)_PA3_ISACTIVE;
			break;
		}
		/*case 4:{
		pPA = &PA4;
		eeprI2c = I2C_PA3_EEPR;
		eeprBand = BAND_PA3_EEPR;
		eeprValid = VALID_PA3_EEPR;
		pADDR = (uint8_t *)_PA4_ADDR;
		pBAND = (uint8_t *)_PA4_BAND;
		pFANPIN = (uint8_t *)_PA4_FANPIN;
		pISACTIVE = (uint8_t *)_PA4_ISACTIVE;
		break;
		}*/
		default: {
			utils_sendDebugPGM(DEBUG_CH, _ERROR, 0, 0);
			return;
		}
	}
	command_scanTwi(pPA);
	if ((PA1.addrTWI > 0 || PA2.addrTWI > 0) && (PA1.addrTWI == PA2.addrTWI)) {
		utils_sendDebugPGM(DEBUG_CH, _ERROR, 0, 0);
		pPA->isValid = 0;
		pPA->addrTWI = 0;
		pPA->temperBuff[0] = 0;
		return;
	}
	/*else if ((PA3.addrTWI > 0 || PA4.addrTWI > 0) && (PA3.addrTWI == PA4.addrTWI)) {
	utils_sendDebugPGM(DEBUG_CH, _ERROR, 0, 0);
	pPA->isValid = 0;
	pPA->addrTWI = 0;
	pPA->temperBuff[0] = 0;
	return;
	}*/
	if (pPA->addrTWI == 0) activeNumber = 0;
	pPA->isValid = activeNumber;
	pPA->band = bandNumber;
	read_writeEEPROMByte(eeprI2c, pPA->addrTWI);
	read_writeEEPROMByte(eeprBand, pPA->band);
	read_writeEEPROMByte(eeprValid, pPA->isValid);
	
	utils_sendDebugPGM(DEBUG_CH, pADDR, utils_hex8ToAscii16(pPA->addrTWI), 2);
	utils_sendDebugPGM(DEBUG_CH, pBAND, utils_hex8ToAscii16(pPA->band), 2);
	utils_sendDebugPGM(DEBUG_CH, pFANPIN, utils_hex8ToAscii16(pPA->fanPin), 2);
	utils_sendDebugPGM(DEBUG_CH, pISACTIVE, utils_hex8ToAscii16(pPA->isValid), 2);
}
