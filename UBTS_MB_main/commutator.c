#include "commutator.h"



bool commutator_decoder(uint8_t address){
	bool validCommand = true;
	switch(address){
		case 0x00:{
			_1_off();
			_2_off();
			_3_off();
			_4_off();
			setAttCommutator(0, 0);
			setPaState(0);
			break;
		}
		case 0x01:{
			_1_1();
			_2_off();
			_3_off();
			_4_off();
			setAttCommutator(0, 0);
			setPaState(PA1.channel);
			POWER_LEDS1.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_1, 1);
			break;
		}
		case 0x02:{
			_1_2();
			_2_off();
			_3_off();
			_4_off();
			setAttCommutator(0, 0);
			setPaState(PA2.channel);
			POWER_LEDS2.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_1, 1);
			break;
		}
		case 0x03:{
			_2_off();
			_3_off();
			_4_off();
			_1_3();
			setAttCommutator(0, 0);
			setPaState(PA3.channel);
			POWER_LEDS3.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_1, 1);
			break;
		}
		case 0x04:{
			_1_off();
			//_2_off();
			_2_1();
			_3_off();
			_4_off();
			setAttCommutator(0, 0);
			setPaState(PA1.channel);
			POWER_LEDS1.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_2, 1);
			break;
		}
		case 0x05:{
			_1_off();
			_2_2();
			_3_off();
			_4_off();
			setAttCommutator(0, 0);
			setPaState(PA2.channel);
			POWER_LEDS2.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_2, 1);
			break;
		}
		case 0x06:{
			_1_off();
			_2_3();
			_3_off();
			_4_off();
			setAttCommutator(0, 0);
			setPaState(PA3.channel);
			POWER_LEDS3.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_2, 1);
			break;
		}
		case 0x07:{
			_1_off();
			_2_off();
			_3_3();
			_4_off();
			setAttCommutator(0, 0);
			setPaState(PA3.channel);
			POWER_LEDS3.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_3, 1);
			break;
		}
		case 0x08:{
			_1_off();
			_2_off();
			_3_off();
			_4_3();
			setAttCommutator(0, 0);
			setPaState(PA3.channel);
			POWER_LEDS3.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_4, 1);
			break;
		}
		case 0x09:{
			_1_1();
			_2_1();
			_3_3();
			_4_off();
			setAttCommutator(0x0018, 0x0018);
			setPaState(PA1.channel | PA3.channel);
			POWER_LEDS1.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_1, 2);
			POWER_LEDS3.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_3, 1);
			break;
		}
		case 0x0a:{
			_1_1();
			_2_1();
			_3_off();
			_4_off();
			setAttCommutator(0x0018, 0x0018);
			setPaState(PA1.channel);
			POWER_LEDS1.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_1, 2);
			break;
		}
		case 0x0b:{
			_1_1();
			_2_off();
			_3_3();
			_4_off();
			setAttCommutator(0x0000, 0x0000);
			setPaState(PA1.channel | PA3.channel);
			POWER_LEDS1.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_1, 1);
			POWER_LEDS3.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_3, 1);
			break;
		}
		case 0x0c:{
			_1_1();
			_2_off();
			_3_off();
			_4_3();
			setAttCommutator(0x0000, 0x0000);
			setPaState(PA1.channel | PA3.channel);
			POWER_LEDS1.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_1, 1);
			POWER_LEDS3.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_4, 1);
			break;
		}
		case 0x0d:{
			_1_1();
			_2_2();
			_3_off();
			_4_off();
			setAttCommutator(0x0000, 0x0000);
			setPaState(PA1.channel | PA2.channel);
			POWER_LEDS1.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_1, 1);
			POWER_LEDS2.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_2, 1);
			break;
		}
		case 0x0e:{
			_1_2();
			_2_1();
			_3_off();
			_4_off();
			setAttCommutator(0x0000, 0x0000);
			setPaState(PA1.channel | PA2.channel);
			POWER_LEDS1.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_2, 1);
			POWER_LEDS2.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_1, 1);
			break;
		}
		case 0x0f:{
			_1_2();
			_2_3();
			_3_off();
			_4_off();
			setAttCommutator(0x0000, 0x0000);
			setPaState(PA2.channel | PA3.channel);
			POWER_LEDS2.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_1, 1);
			POWER_LEDS3.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_2, 1);
			break;
		}
		case 0x10:{
			_1_2();
			_2_off();
			_3_3();
			_4_off();
			setAttCommutator(0x0000, 0x0000);
			setPaState(PA2.channel | PA3.channel);
			POWER_LEDS2.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_1, 1);
			POWER_LEDS3.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_3, 1);
			break;
		}
		case 0x11:{
			_1_2();
			_2_off();
			_3_off();
			_4_3();
			setAttCommutator(0x0000, 0x0000);
			setPaState(PA2.channel | PA3.channel);
			POWER_LEDS2.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_1, 1);
			POWER_LEDS3.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_4, 1);
			break;
		}
		case 0x12:{
			if(PA3.band == 0x01 && (COMMUTATOR.standart_ch_1 != 'C' &&
			COMMUTATOR.standart_ch_3 != 'C' && COMMUTATOR.standart_ch_4 != 'C')){
				_1_3();
				_2_off();
				_3_2100();
				_4_2100();
				setAttCommutator(0x1818, 0x1800);
				setPaState(PA3.channel);
				POWER_LEDS3.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_1, 3);
			}
			else {
				commutator_decoder(NOCOMBINATION);
				validCommand = false;
			}
			break;
		}
		case 0x13:{
			_1_2();
			_2_2();
			_3_off();
			_4_off();
			setAttCommutator(0x0018, 0x0018);
			setPaState(PA2.channel);
			POWER_LEDS2.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_1, 2);
			break;
		}
		case 0x14:{
			_1_off();
			_2_1();
			_3_3();
			_4_off();
			setAttCommutator(0x0000, 0x0000);
			setPaState(PA1.channel | PA3.channel);
			POWER_LEDS1.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_2, 1);
			POWER_LEDS3.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_3, 1);
			break;
		}
		case 0x15:{
			_1_off();
			_2_1();
			_3_off();
			_4_3();
			setAttCommutator(0x0000, 0x0000);
			setPaState(PA1.channel | PA3.channel);
			POWER_LEDS1.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_2, 1);
			POWER_LEDS3.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_4, 1);
			break;
		}
		case 0x16:{
			_1_off();
			_2_2();
			_3_3();
			_4_off();
			setAttCommutator(0x0000, 0x0000);
			setPaState(PA2.channel | PA3.channel);
			POWER_LEDS2.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_2, 1);
			POWER_LEDS3.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_3, 1);
			break;
		}
		case 0x17:{
			_1_off();
			_2_2();
			_3_off();
			_4_3();
			setAttCommutator(0x0000, 0x0000);
			setPaState(PA2.channel | PA3.channel);
			POWER_LEDS2.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_2, 1);
			POWER_LEDS3.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_4, 1);
			break;
		}
		case 0x18:{
			_1_off();
			_2_2();
			if (PA3.band == 0x01 && (COMMUTATOR.standart_ch_3 != 'C' && COMMUTATOR.standart_ch_4 != 'C')){
				_3_2100();
				_4_2100();
				setAttCommutator(0x0000, 0x0000);
			}
			else{
				_3_3();
				_4_3();
				setAttCommutator(0x1800, 0x1800);
			}
			setPaState(PA2.channel | PA3.channel);
			POWER_LEDS2.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_2, 1);
			POWER_LEDS3.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_3, 2);
			break;
		}
		case 0x19:{
			_1_off();
			_2_1();
			if (PA3.band == 0x01 && (COMMUTATOR.standart_ch_3 != 'C' && COMMUTATOR.standart_ch_4 != 'C')){
				_3_2100();
				_4_2100();
				setAttCommutator(0x0000, 0x0000);
			}
			else{
				_3_3();
				_4_3();
				setAttCommutator(0x1800, 0x1800);
			}
			setPaState(PA1.channel | PA3.channel);
			POWER_LEDS1.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_2, 1);
			POWER_LEDS3.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_3, 2);
			break;
		}
		case 0x1a:{
			_1_1();
			_2_off();
			if (PA3.band == 0x01 && (COMMUTATOR.standart_ch_3 != 'C' && COMMUTATOR.standart_ch_4 != 'C')){
				_3_2100();
				_4_2100();
				setAttCommutator(0x0000, 0x0000);
			}
			else{
				_3_3();
				_4_3();
				setAttCommutator(0x1800, 0x1800);
			}
			setPaState(PA1.channel | PA3.channel);
			POWER_LEDS1.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_1, 1);
			POWER_LEDS3.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_3, 2);
			break;
		}
		case 0x1b:{
			_1_2();
			_2_off();
			if (PA3.band == 0x01 && (COMMUTATOR.standart_ch_3 != 'C' && COMMUTATOR.standart_ch_4 != 'C')){
				_3_2100();
				_4_2100();
				setAttCommutator(0x0000, 0x0000);
			}
			else{
				_3_3();
				_4_3();
				setAttCommutator(0x1800, 0x1800);
			}
			setPaState(PA2.channel | PA3.channel);
			POWER_LEDS2.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_1, 1);
			POWER_LEDS3.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_3, 2);
			break;
		}
		case 0x1c:{
			_1_off();
			_2_off();
			if (PA3.band == 0x01 && (COMMUTATOR.standart_ch_3 != 'C' && COMMUTATOR.standart_ch_4 != 'C')){
				_3_2100();
				_4_2100();
				setAttCommutator(0x0000, 0x0000);
			}
			else{
				_3_3();
				_4_3();
				setAttCommutator(0x1800, 0x1800);
			}
			setPaState(PA3.channel);
			POWER_LEDS3.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_3, 2);
			break;
		}
		case 0x1d:{
			_1_3();
			_2_1();
			_3_off();
			_4_off();
			setAttCommutator(0x0000, 0x0000);
			setPaState(PA1.channel | PA3.channel);
			POWER_LEDS3.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_1, 1);
			POWER_LEDS1.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_2, 1);
			break;
		}
		case 0x1e:{
			_1_3();
			_2_2();
			_3_off();
			_4_off();
			setAttCommutator(0x0000, 0x0000);
			setPaState(PA2.channel | PA3.channel);
			POWER_LEDS3.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_1, 1);
			POWER_LEDS2.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_2, 1);
			break;
		}
		case 0x1f:{
			_1_3();
			_2_3();
			_3_off();
			_4_off();
			setAttCommutator(0x0018, 0x0018);
			setPaState(PA3.channel);
			POWER_LEDS3.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_1, 2);
			break;
		}
		case 0x20:{
			_1_3();
			_2_off();
			_3_off();
			_4_3();
			setAttCommutator(0x0018, 0x1800);
			setPaState(PA3.channel);
			POWER_LEDS3.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_1, 2);
			break;
		}
		case 0x21:{
			_1_off();
			_2_3();
			_3_3();
			_4_off();
			setAttCommutator(0x1800, 0x0018);
			setPaState(PA3.channel);
			POWER_LEDS3.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_2, 2);
			break;
		}
		case 0x22:{
			_1_1();
			_2_1();
			if (PA3.band == 0x01 && (COMMUTATOR.standart_ch_3 != 'C' && COMMUTATOR.standart_ch_4 != 'C')){
				_3_2100();
				_4_2100();
				setAttCommutator(0x0018, 0x0018);
			}
			else{
				_3_3();
				_4_3();
				setAttCommutator(0x1818, 0x1818);
			}
			setPaState(PA1.channel | PA3.channel);
			POWER_LEDS1.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_1, 2);
			POWER_LEDS3.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_3, 2);
			break;
		}
		case 0x23:{
			_1_2();
			_2_2();
			if (PA3.band == 0x01 && (COMMUTATOR.standart_ch_3 != 'C' && COMMUTATOR.standart_ch_4 != 'C')){
				_3_2100();
				_4_2100();
				setAttCommutator(0x0018, 0x0018);
			}
			else{
				_3_3();
				_4_3();
				setAttCommutator(0x1818, 0x1818);
			}
			setPaState(PA2.channel | PA3.channel);
			POWER_LEDS2.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_1, 2);
			POWER_LEDS3.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_3, 2);
			break;
		}
		case 0x24:{
			_1_1();
			_2_2();
			if (PA3.band == 0x01 && (COMMUTATOR.standart_ch_3 != 'C' && COMMUTATOR.standart_ch_4 != 'C')){
				_3_2100();
				_4_2100();
				setAttCommutator(0x0000, 0x0000);
			}
			else{
				_3_3();
				_4_3();
				setAttCommutator(0x1800, 0x1800);
			}
			setPaState(PA1.channel | PA2.channel | PA3.channel);
			POWER_LEDS1.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_1, 1);
			POWER_LEDS2.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_2, 1);
			POWER_LEDS3.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_3, 2);
			break;
		}
		case 0x25:{
			_1_2();
			_2_1();
			if (PA3.band == 0x01 && (COMMUTATOR.standart_ch_3 != 'C' && COMMUTATOR.standart_ch_4 != 'C')){
				_3_2100();
				_4_2100();
				setAttCommutator(0x0000, 0x0000);
			}
			else{
				_3_3();
				_4_3();
				setAttCommutator(0x1800, 0x1800);
			}
			setPaState(PA1.channel | PA2.channel | PA3.channel);
			POWER_LEDS2.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_1, 1);
			POWER_LEDS1.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_2, 1);
			POWER_LEDS3.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_3, 2);
			break;
		}
		case 0x26:{
			_1_1();
			_2_3();
			_3_3();
			_4_off();
			setAttCommutator(0x1800, 0x0018);
			setPaState(PA1.channel | PA3.channel);
			POWER_LEDS1.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_1, 1);
			POWER_LEDS3.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_2, 2);
			break;
		}
		case 0x27:{
			_1_1();
			_2_3();
			_3_off();
			_4_off();
			setAttCommutator(0x0000, 0x0000);
			setPaState(PA1.channel | PA3.channel);
			POWER_LEDS1.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_1, 1);
			POWER_LEDS3.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_2, 1);
			break;
		}
		case 0x28:{
			_1_1();
			_2_off();
			_3_off();
			_4_off();
			setAttCommutator(0x0000, 0x0000);
			setPaState(PA1.channel);
			POWER_LEDS1.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_1, 1);
			break;
		}
		case 0x29:{
			if (COMMUTATOR.standart_ch_1 == COMMUTATOR.standart_ch_2){
				_1_1();
				_2_1();
				_3_3();
				setAttCommutator(0x0018, 0x0018);
				POWER_LEDS1.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_1, 2);
				POWER_LEDS3.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_3, 1);
			}
			else if (COMMUTATOR.standart_ch_2 == COMMUTATOR.standart_ch_3){
				_1_1();
				_2_3();
				_3_3();
				setAttCommutator(0x1800, 0x0018);
				POWER_LEDS1.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_1, 1);
				POWER_LEDS3.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_3, 2);
			}
			_4_off();
			setPaState(PA1.channel | PA3.channel);
			break;
		}
		case 0x2a:{
			//if (PA1.band == 0x01 && PA3.band == 0x01 && PA1.isValid && PA3.isValid){
			_1_1();
			_2_off();
			_3_3();
			_4_off();
			setAttCommutator(0x0000, 0x0000);
			//}
			//else commutator_decoder(0xff);
			setPaState(PA1.channel | PA3.channel);
			POWER_LEDS1.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_1, 1);
			POWER_LEDS3.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_3, 1);
			break;
		}
		case 0x2b:{
			_1_1();
			_2_3();
			_3_off();
			_4_off();
			setAttCommutator(0x0000, 0x0000);
			setPaState(PA1.channel | PA3.channel);
			POWER_LEDS1.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_1, 1);
			POWER_LEDS3.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_2, 1);
			break;
		}
		case 0x2c:{
			_1_off();
			_2_1();
			_3_off();
			_4_off();
			setAttCommutator(0x0000, 0x0000);
			setPaState(PA1.channel);
			POWER_LEDS1.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_2, 1);
			break;
		}
		case 0x2d:{
			_1_off();
			_2_1();
			_3_3();
			_4_off();
			setAttCommutator(0x0000, 0x0000);
			setPaState(PA1.channel | PA3.channel);
			POWER_LEDS1.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_2, 1);
			POWER_LEDS3.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_3, 1);
			break;
		}
		case 0x2e:{
			_1_off();
			_2_off();
			_3_3();
			_4_off();
			setAttCommutator(0x0000, 0x0000);
			setPaState(PA3.channel);
			POWER_LEDS3.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_3, 1);
			break;
		}
		case 0x2f:{
			_1_off();
			_2_off();
			_3_off();
			_4_3();
			setAttCommutator(0x0000, 0x0000);
			setPaState(PA3.channel);
			POWER_LEDS3.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_4, 1);
			break;
		}
		case 0x30:{
			_2_off();
			_3_off();
			_1_1();
			_4_3();
			setAttCommutator(0x0000, 0x0000);
			setPaState(PA3.channel | PA1.channel);
			POWER_LEDS1.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_1, 1);
			POWER_LEDS3.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_4, 1);
			break;
		}
		case 0x31:{
			_1_1();
			_2_1();
			_3_off();
			_4_3();
			setAttCommutator(0x0018, 0x0018);
			setPaState(PA3.channel | PA1.channel);
			POWER_LEDS1.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_1, 2);
			POWER_LEDS3.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_4, 1);
			break;
		}
		case 0x32:{
			_1_1();
			_2_off();
			if (PA3.band == 0x01 && (COMMUTATOR.standart_ch_3 != 'C' && COMMUTATOR.standart_ch_4 != 'C')){
				_3_2100();
				_4_2100();
				setAttCommutator(0x0000, 0x0000);
			}
			else{
				_3_3();
				_4_3();
				setAttCommutator(0x1800, 0x1800);
			}
			setPaState(PA3.channel | PA1.channel);
			POWER_LEDS1.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_1, 1);
			POWER_LEDS3.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_3, 2);
			break;
		}
		case 0x33:{
			_1_off();
			_2_off();
			if (PA3.band == 0x01 && (COMMUTATOR.standart_ch_3 != 'C' && COMMUTATOR.standart_ch_4 != 'C')){
				_3_2100();
				_4_2100();
				setAttCommutator(0x0000, 0x0000);
			}
			else{
				_3_3();
				_4_3();
				setAttCommutator(0x1800, 0x1800);
			}
			setPaState(PA3.channel);
			POWER_LEDS3.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_3, 2);
			break;
		}
		case 0x34:{
			_1_off();
			_2_1();
			_3_off();
			_4_3();
			setAttCommutator(0x0000, 0x0000);
			setPaState(PA3.channel | PA1.channel);
			POWER_LEDS1.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_2, 1);
			POWER_LEDS3.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_4, 1);
			break;
		}
		case 0x35:{
			_1_1();
			_2_1();
			if (PA3.band == 0x01 && (COMMUTATOR.standart_ch_3 != 'C' && COMMUTATOR.standart_ch_4 != 'C')){
				_3_2100();
				_4_2100();
				setAttCommutator(0x0018, 0x0018);
			}
			else{
				_3_3();
				_4_3();
				setAttCommutator(0x1818, 0x1818);
			}
			setPaState(PA3.channel | PA1.channel);
			POWER_LEDS1.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_1, 2);
			POWER_LEDS3.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_3, 2);
			break;
		}
		case 0x36:{
			_1_off();
			_2_1();
			if (PA3.band == 0x01 && (COMMUTATOR.standart_ch_3 != 'C' && COMMUTATOR.standart_ch_4 != 'C')){
				_3_2100();
				_4_2100();
				setAttCommutator(0x0000, 0x0000);
			}
			else{
				_3_3();
				_4_3();
				setAttCommutator(0x1800, 0x1800);
			}
			setPaState(PA3.channel | PA1.channel);
			POWER_LEDS1.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_2, 1);
			POWER_LEDS3.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_3, 2);
			break;
		}
		case 0x37:{
			_1_1();
			_2_1();
			_3_off();
			_4_3();
			setAttCommutator(0x0018, 0x0018);
			setPaState(PA1.channel | PA3.channel);
			POWER_LEDS1.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_1, 2);
			POWER_LEDS3.pArrLedSt = getArrayOfLeds(COMMUTATOR.standart_ch_3, 1);
			break;
		}
		
		case NOCOMBINATION:{
			utils_sendDebugPGM(DEBUG_CH, _ABSENT, 0, 0);
			utils_sendDebugPGM(MAIN_CH, _ABSENT, 0, 0);
			validCommand = false;
			break;
		}
		default:{
			utils_sendDebugPGM(DEBUG_CH, 0, 0, 0);
			validCommand = false;
			break;
		}
	}
	return validCommand;
}

const uint8_t table_1[] = {nul, pa1, pa2, pa3, nul, nul, nul, nul, nul,/*09*/ pa1, pa1, pa1, pa1, pa1,/*0e*/ pa2, pa2, pa2, pa2, pa3,/*13*/ pa2, nul, nul, nul, nul, nul, nul,/*1a*/ pa1, pa2, nul, pa3, pa3, pa3,/*20*/ pa3, nul, pa1, pa2, pa1, pa2,/*26*/ pa1, pa1, p13, p13, p13,/*2b*/ p13, nul, nul, nul, nul,/*30*/ p13, p13, p13, nul, nul, p13, nul, pa1};
const uint8_t table_2[] = {nul, nul, nul, nul, pa1, pa2, pa3, nul, nul,/*09*/ pa1, pa1, nul, nul, pa2,/*0e*/ pa1, pa3, nul, nul, nul,/*13*/ pa2, pa1, pa1, pa2, pa2, pa2, pa1,/*1a*/ nul, nul, nul, pa1, pa2, pa3,/*20*/ nul, pa3, pa1, pa2, pa2, pa1,/*26*/ pa3, pa3, nul, p13, nul,/*2b*/ p13, p13, p13, nul, nul,/*30*/ nul, p13, nul, nul, p13, p13, p13, pa1};
const uint8_t table_3[] = {nul, nul, nul, nul, nul, nul, nul, pa3, nul,/*09*/ pa3, nul, pa3, nul, nul,/*0e*/ nul, nul, pa3, nul, pa3,/*13*/ nul, pa3, nul, pa3, nul, pa3, pa3,/*1a*/ pa3, pa3, pa3, nul, nul, nul,/*20*/ nul, pa3, pa3, pa3, pa3, pa3,/*26*/ pa3, nul, nul, p13, p13,/*2b*/ nul, nul, p13, p13, nul,/*30*/ nul, nul, p13, p13, nul, p13, p13, nul};
const uint8_t table_4[] = {nul, nul, nul, nul, nul, nul, nul, nul, pa3,/*09*/ nul, nul, nul, pa3, nul,/*0e*/ nul, nul, nul, pa3, pa3,/*13*/ nul, nul, pa3, nul, pa3, pa3, pa3,/*1a*/ pa3, pa3, pa3, nul, nul, nul,/*20*/ pa3, nul, pa3, pa3, pa3, pa3,/*26*/ nul, nul, nul, nul, nul,/*2b*/ nul, nul, nul, nul, p13,/*30*/ p13, p13, p13, p13, p13, p13, p13, pa3};

uint16_t* getArrayOfLeds(char standart, uint8_t isDouble){
	if (standart == 'L' && isDouble == 1) return arrLed1L;
	else if (standart == 'L' && isDouble == 2) return arrLed2L;
	else if (standart == 'L' && isDouble == 3) return arrLed3L;
	else if (standart == 'U' && isDouble == 1) return arrLed1U;
	else if (standart == 'U' && isDouble == 2) return arrLed2U;
	else if (standart == 'C' && isDouble == 1) return arrLed1C;
	else if (standart == 'C' && isDouble == 2) return arrLed1C;
	else if (standart == 'C' && isDouble == 3) return arrLed1C;
	else return arrLed3U;
}
uint8_t searchCombination(commut_regs_t *commutator){
	uint8_t size = sizeof(table_1);
	for (uint8_t i=0; i < size; i++){
		if (table_1[i] == commutator->ch_1 && table_2[i] == commutator->ch_2 && table_3[i] == commutator->ch_3 && table_4[i] == commutator->ch_4){
			return i;
		}
	}
	return NOCOMBINATION;
}
uint8_t findDuplicate(){
	uint8_t size = sizeof(table_1);
	for (uint8_t i=0; i < size; i++){
		for (uint8_t k= i+1; k < size; k++){
			//if (i == k) continue;
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

	spi_setReg(&SPID, &PORTH, REGISTERS.ledChState |= LED_CH1, LED_CH_REG);		//set led 1 ch

	utils_sendDebugPGM(DEBUG_CH, _1_1P, 0, 0);
	utils_sendStDebug(&COMMUTATOR.standart_ch_1);
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

	spi_setReg(&SPID, &PORTH, REGISTERS.ledChState |= LED_CH1, LED_CH_REG);		//set led 1 ch

	utils_sendDebugPGM(DEBUG_CH, _1_2P, 0, 0);
	utils_sendAnswerMain(DEBUG_CH, &COMMUTATOR.standart_ch_1, 0, 0);
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

	spi_setReg(&SPID, &PORTH, REGISTERS.ledChState |= LED_CH1, LED_CH_REG);		//set led 1 ch

	utils_sendDebugPGM(DEBUG_CH, _1_3P, 0, 0);
	utils_sendStDebug(&COMMUTATOR.standart_ch_1);
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

	spi_setReg(&SPID, &PORTH, REGISTERS.ledChState &= ~LED_CH1, LED_CH_REG);

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

	spi_setReg(&SPID, &PORTH, REGISTERS.ledChState |= LED_CH2, LED_CH_REG);		//set led 2 ch

	utils_sendDebugPGM(DEBUG_CH, _2_1P, 0, 0);
	utils_sendStDebug(&COMMUTATOR.standart_ch_2);
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

	spi_setReg(&SPID, &PORTH, REGISTERS.ledChState |= LED_CH2, LED_CH_REG);		//set led 2 ch

	utils_sendDebugPGM(DEBUG_CH, _2_2P, 0, 0);
	utils_sendStDebug(&COMMUTATOR.standart_ch_2);
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

	spi_setReg(&SPID, &PORTH, REGISTERS.ledChState |= LED_CH2, LED_CH_REG);		//set led 2 ch

	utils_sendDebugPGM(DEBUG_CH, _2_3P, 0, 0);
	utils_sendStDebug(&COMMUTATOR.standart_ch_2);
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

	spi_setReg(&SPID, &PORTH, REGISTERS.ledChState &= ~LED_CH2, LED_CH_REG);

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

	spi_setReg(&SPID, &PORTH, REGISTERS.ledChState |= LED_CH3, LED_CH_REG);		//set led 3 ch

	utils_sendDebugPGM(DEBUG_CH, _3_3P, 0, 0);
	utils_sendStDebug(&COMMUTATOR.standart_ch_3);
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

	spi_setReg(&SPID, &PORTH, REGISTERS.ledChState |= LED_CH3, LED_CH_REG);		//set led 3 ch

	utils_sendDebugPGM(DEBUG_CH, _3_2100P, 0, 0);
	utils_sendStDebug(&COMMUTATOR.standart_ch_3);
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

	spi_setReg(&SPID, &PORTH, REGISTERS.ledChState &= ~LED_CH3, LED_CH_REG);

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

	spi_setReg(&SPID, &PORTH, REGISTERS.ledChState |= LED_CH4, LED_CH_REG);		//set led 4 ch

	utils_sendDebugPGM(DEBUG_CH, _4_3P, 0, 0);
	utils_sendStDebug(&COMMUTATOR.standart_ch_4);
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

	spi_setReg(&SPID, &PORTH, REGISTERS.ledChState |= LED_CH4, LED_CH_REG);		//set led 4 ch

	utils_sendDebugPGM(DEBUG_CH, _4_2100P, 0, 0);
	utils_sendStDebug(&COMMUTATOR.standart_ch_4);
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

	spi_setReg(&SPID, &PORTH, REGISTERS.ledChState &= ~LED_CH4, LED_CH_REG);

	utils_sendDebugPGM(DEBUG_CH, _4_OFF, 0, 0);
}
void setAttCommutator(uint16_t value4, uint16_t value5){										//value4 = 0xTTee - TT-ch3, ee-ch1; value5 = 0xYYuu   YY-ch4, uu-ch2

	spi_setRegDouble(&SPID, &PORTF, COMMUTATOR.sreg4_state_att + value4, ST_SREG_SPI_4);
	spi_setRegDouble(&SPID, &PORTK, COMMUTATOR.sreg5_state_att + value5, ST_SREG_SPI_5);
	utils_sendAnswerMain(DEBUG_CH, "\ns4= ", utils_hex16ToAscii32((COMMUTATOR.sreg4_state_att + value4) >> 1), 4);
	utils_sendAnswerMain(DEBUG_CH, "\ns5= ", utils_hex16ToAscii32((COMMUTATOR.sreg5_state_att + value5) >> 1), 4);
}
uint8_t checkInChannelState(){
	return COMMUTATOR.ch_1 | COMMUTATOR.ch_2 | COMMUTATOR.ch_3 | COMMUTATOR.ch_4;
}