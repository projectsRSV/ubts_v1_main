#include <avr/io.h>
//#include <avr/eeprom.h>
#include "initDevice.h"
#include "PROGM_.h"
#include "commands.h"

#include "ISR.h"
#include "reads.h"

uint8_t buff[BUFFER_SIZE];
uint8_t buffer_gate[4];								//192, 168, 6, 1
uint8_t buffer_mask[4];								//255, 255, 255, 0
uint8_t buffer_ip[4];								//192, 168, 6, 10
uint8_t buffer_SOCKET_main[2];
uint8_t buffer_serialNum[4];
//uint8_t buffer_mac[6] = {0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa};;								//ff-ff-ff-ff-ff-ff
uint8_t buffer_mac[6];								//ff-ff-ff-ff-ff-ff
uint16_t animePause;

uint8_t *pGate, *pMask, *pIp;

uint8_t configBuff[2] = {0x47, 0xff};
uint8_t calibBuff[2] = {0x02, 0x00};		//scale = 10A (max = 9.999A); 1mA/bit


uint16_t arrLTE7_1[] = {1448, 1755, 1838, 1900, 1952, 1975, 2050, 1238};			//6, 11, 16, 21, 27, __,  40, 5W - BW
uint16_t arrLTE7_2[] = {1618, 1855, 1933, 1992, 2047, 2095, 2147, 1438};			//6, 11, 16, 21, 27, __,  40, 5W - BW
uint16_t arrLTE7_3[] = {1218, 1955, 2033, 2092, 2147, 2195, 2247, 1538};			//6, 11, 16, 21, 27, __,  40, 5W - BW

uint16_t arrLTE3_1[] = {1448, 1755, 1838, 1900, 1952, 1975, 2050, 1238};			//6, 11, 16, 21, 27, __,  40, 5W - BW
uint16_t arrLTE3_2[] = {1618, 1855, 1933, 1992, 2047, 2095, 2147, 1438};			//6, 11, 16, 21, 27, __,  40, 5W - BW
uint16_t arrLTE3_3[] = {1218, 1955, 2033, 2092, 2147, 2195, 2247, 1538};			//6, 11, 16, 21, 27, __,  40, 5W - BW

uint16_t arrUMTS3_1[] = {1448, 1755, 1838, 1900, 1952, 1975, 2050, 1238};			//6, 11, 16, 21, 27, __,  40, 5W - BW
uint16_t arrUMTS3_2[] = {1618, 1855, 1933, 1992, 2047, 2095, 2147, 1438};			//6, 11, 16, 21, 27, __,  40, 5W - BW
uint16_t arrUMTS3_3[] = {1218, 1955, 2033, 2092, 2147, 2195, 2247, 1538};			//6, 11, 16, 21, 27, __,  40, 5W - BW

uint16_t arrUMTS7_1[] = {1448, 1755, 1838, 1900, 1952, 1975, 2050, 1238};			//6, 11, 16, 21, 27, __,  40, 5W - BW
uint16_t arrUMTS7_2[] = {1618, 1855, 1933, 1992, 2047, 2095, 2147, 1438};			//6, 11, 16, 21, 27, __,  40, 5W - BW
uint16_t arrUMTS7_3[] = {1218, 1955, 2033, 2092, 2147, 2195, 2247, 1538};			//6, 11, 16, 21, 27, __,  40, 5W - BW

uint16_t *bandU1[] = {};
uint16_t *bandU2[] = {};
uint16_t *bandU3[] = {arrUMTS3_1, arrUMTS3_2, arrUMTS3_3};
uint16_t *bandU5[] = {};
uint16_t *bandU7[] = {arrUMTS7_1, arrUMTS7_2, arrUMTS7_3};
uint16_t *bandU8[] = {};
uint16_t *bandU20[] = {};
uint16_t **arrLedUMTS[] = {0x00, bandU1, bandU2, bandU3, 0x00, bandU5, 0x00, bandU7, bandU8, 0x00, 0x00
, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, bandU20};

uint16_t *bandL1[] = {};
uint16_t *bandL2[] = {};
uint16_t *bandL3[] = {arrLTE3_1, arrLTE3_2, arrLTE3_3};
uint16_t *bandL5[] = {};
uint16_t *bandL7[] = {arrLTE7_1, arrLTE7_2, arrLTE7_3};
uint16_t *bandL8[] = {};
uint16_t *bandL20[] = {};

uint16_t **arrLedLTE[] = {0x00, bandL1, bandL2, bandL3, 0x00, bandL5, 0x00, bandL7, bandL8, 0x00, 0x00
, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, bandL20};

uint16_t **arrLedGSM[] = {};
uint16_t **arrLedCDMA[] = {};

uint16_t ***arrLedAll[] ={arrLedCDMA, 0x00, 0x00, 0x00, arrLedGSM, 0x00, 0x00, 0x00, 0x00, arrLedLTE, 0x00
	, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, arrLedUMTS};
	

twi_device_t PA1 = {.fanPin = FAN_PA1, .paPin = PA_ENABLE_1, .name = (uint8_t*)_PA1};								//
twi_device_t PA2 = {.fanPin = FAN_PA2, .paPin = PA_ENABLE_2, .name = (uint8_t*)_PA2};								//
twi_device_t PA3 = {.fanPin = FAN_PA3, .paPin = PA_ENABLE_3, .name = (uint8_t*)_PA3};								//
//twi_device_t PA4 = {.fanPin = FAN_PA4, .paPin = PA_ENABLE_4, .name = (uint8_t*)_PA4};								//none

twi_device_t BOARD = {.addrTWI = TEMP_BOARD, .fanPin = FAN_BACK};
twi_device_t INA_BTS = {.addrTWI = I2C_BTS};
twi_device_t INA_PERIPHERY = {.addrTWI = I2C_PERIPHERY};

channel_t CHANNEL1 = {.channelNum = 1};
channel_t CHANNEL2 = {.channelNum = 2};
channel_t CHANNEL3 = {.channelNum = 4};
channel_t CHANNEL4 = {.channelNum = 8};
commutator_t COMMUTATOR;// = {.channel[] = {CHANNEL1, CHANNEL2, CHANNEL3, CHANNEL4}};

regs_t REGISTERS = {.nmGpsWifiPpsState = 0x00, .paState = 0, .dcDcState = 0xf810, .resetWifiGpsNmState = 0x06, .ledChState = 0, .ledFanState = 0};				//all bts,back fan,on wifi, freset and reset wifi on
power_leds_t POWER_LEDS1, POWER_LEDS2, POWER_LEDS3;

void main_onOffLedPaTemp();
void main_onOffPaTemp();

int main() {	
	pGate = buffer_gate;
	pMask = buffer_mask;
	pIp = buffer_ip;
	
	POWER_LEDS1 = (power_leds_t){.ledBit = 1, .fp = (fpGeneric)ledsTable[0], .adcValueO = &ADC_PA_OUT_1.value, .adcValueBW = &ADC_PA_BW_1.value, .pin = LED_POWER_3, .pArrLedSt = arrLTE7_1, .paNum = pa1};
	POWER_LEDS2 = (power_leds_t){.ledBit = 1, .fp = (fpGeneric)ledsTable[0], .adcValueO = &ADC_PA_OUT_2.value, .adcValueBW = &ADC_PA_BW_2.value, .pin = LED_POWER_2, .pArrLedSt = arrLTE7_1, .paNum = pa2};
	POWER_LEDS3 = (power_leds_t){.ledBit = 1, .fp = (fpGeneric)ledsTable[0], .adcValueO = &ADC_PA_OUT_3.value, .adcValueBW = &ADC_PA_BW_3.value, .pin = LED_POWER_1, .pArrLedSt = arrLTE7_1, .paNum = pa3};
	
	COMMUTATOR.channel[0] = CHANNEL1;
	COMMUTATOR.channel[1] = CHANNEL2;
	COMMUTATOR.channel[2] = CHANNEL3;
	COMMUTATOR.channel[3] = CHANNEL4;
	
	read_eeprom();
	init_all();
	
	fpProgModeVar = (fpProgMode)(fpProgModeTable[0]);			//main mode
	blinkFuncPtr = (fpStatusLed)(blinkLedTable[2]);				//speed of led blinking
	fanLedFuncPtr = (fpFanLed)(ledFanTable[0]);					//fan led light green
	
	spi_startAnime();
	startDCs();
	
	while (1) {
		blinkFuncPtr();
		fpProgModeVar();
		fanLedFuncPtr();
		
		read_udpCommand();
		read_mainCommand();
		read_debugCommand();
		//read_commandUART();
		read_nmCommand();
		read_sendGps();
		read_twiSensors();
		read_adc();
		
		((fpPowerLed)POWER_LEDS1.fp)(&POWER_LEDS1);
		((fpPowerLed)POWER_LEDS2.fp)(&POWER_LEDS2);
		((fpPowerLed)POWER_LEDS3.fp)(&POWER_LEDS3);
		
		utils_controlTempPA(&PA1);
		utils_switchFan(&PA1);
		utils_controlTempPA(&PA2);
		utils_switchFan(&PA2);
		utils_controlTempPA(&PA3);
		utils_switchFan(&PA3);
		//utils_controlTempPA(&PA4);
		//utils_switchFan(&PA4);
		//utils_controlTempPA(&BOARD);
		//utils_switchFan(&BOARD);
		
		main_onOffLedPaTemp();
		main_onOffPaTemp();
	}
}
void main_onOffPaTemp(){
	static uint16_t i;
	
	if (i++ == 0x6fff){
		if (PA1.temperBuff[0] >= TEMP_SHUTDOWN) {
			paOffByNum(POWER_LEDS1.paNum);
		}
		else if (PA2.temperBuff[0] >= TEMP_SHUTDOWN){
			paOffByNum(POWER_LEDS2.paNum);
		}
		else if (PA3.temperBuff[0] >= TEMP_SHUTDOWN){
			paOffByNum(POWER_LEDS3.paNum);
		}
		i = 0;
	}
}
void main_onOffLedPaTemp(){
	static uint8_t latch, latch1;
	static uint16_t i;
	
	if (i++ == 0x3fff){
		if (latch == 0) {
			if ((PA1.temperBuff[0] == 0 && PA1.isValid == 1) || (PA2.temperBuff[0] == 0 && PA2.isValid == 1) ||	(PA3.temperBuff[0] == 0 && PA3.isValid == 1)){
				fanLedFuncPtr = (fpFanLed)(ledFanTable[4]);				//fan led blink all
				if (!latch1){
					utils_sendDebugPGM(DEBUG_CH, _ERROR_I2C, 0, 0);
					utils_sendDebugPGM(MAIN_CH, _ERROR_I2C, 0, 0);
					latch1 = 1;
				}
			}
			else if (PA1.temperBuff[0] >= TEMP_SHUTDOWN) {
				latch = 1;
				fanLedFuncPtr = (fpFanLed)(ledFanTable[3]);				//fan led blink red
				command_exec(0x16);
				utils_sendDebugPGM(DEBUG_CH, _OVER_TEMP, utils_hex8ToDecAscii16(PA1.temperBuff[0]), 2);
				utils_sendDebugPGM(MAIN_CH, _OVER_TEMP, 0, 0);
			}
			else if (PA2.temperBuff[0] >= TEMP_SHUTDOWN){
				latch = 1;
				fanLedFuncPtr = (fpFanLed)(ledFanTable[3]);				//fan led blink red
				command_exec(0x17);
				utils_sendDebugPGM(DEBUG_CH, _OVER_TEMP, utils_hex8ToDecAscii16(PA2.temperBuff[0]), 2);
				utils_sendDebugPGM(MAIN_CH, _OVER_TEMP, 0, 0);
			}
			else if (PA3.temperBuff[0] >= TEMP_SHUTDOWN){
				latch = 1;
				fanLedFuncPtr = (fpFanLed)(ledFanTable[3]);				//fan led blink red
				command_exec(0x18);
				utils_sendDebugPGM(DEBUG_CH, _OVER_TEMP, utils_hex8ToDecAscii16(PA3.temperBuff[0]), 2);
				utils_sendDebugPGM(MAIN_CH, _OVER_TEMP, 0, 0);
			}
			else if (PA1.temperBuff[0] >= TEMP_RED || PA2.temperBuff[0] >= TEMP_RED || PA3.temperBuff[0] >= TEMP_RED) {
				latch1 = 0;
				fanLedFuncPtr = (fpFanLed)(ledFanTable[2]);				//fan led light red
			}
			else if (!PA1.fanState && !PA2.fanState && !PA3.fanState){
				latch1 = 0;
				fanLedFuncPtr = (fpFanLed)(ledFanTable[0]);				//fan led light green
			}
			else if (PA1.temperBuff[0] >= TEMP_YELLOW || PA2.temperBuff[0] >= TEMP_YELLOW || PA3.temperBuff[0] >= TEMP_YELLOW) {
				latch1 = 0;
				fanLedFuncPtr = (fpFanLed)(ledFanTable[1]);				//fan led light yellow
			}
		}
		i = 0;
	}
}
void mainMode(){}														//main mode, doing nothing
void sendMode(){
	static uint16_t i;
	static uint8_t k;
	//char charact[] = "\n%72*";
	char *charact = "\n%72*";

	if (k <= 7) {
		if (i++ >= 0x2fff) {
			for (uint8_t i=0; i<strlen(charact); i++){
				FIFO_udpChTx.data[FIFO_udpChTx.head++] = charact[i];
			}
			for (uint8_t i=0; i<3; i++){
				FIFO_udpIp.data[FIFO_udpIp.head++] = *(pIp + i);
			}
			FIFO_udpIp.data[FIFO_udpIp.head++] = *(pIp + 3) + 1;
			w5200_sendDataFifoUDP(UDP_CH, &FIFO_udpChTx, &FIFO_udpIp);
			
			FIFO_udpChTx.tail -= 5;
			FIFO_udpIp.tail -= 4;
			FIFO_udpIp.data[FIFO_udpIp.head - 1] += 2;
			w5200_sendDataFifoUDP(UDP_CH, &FIFO_udpChTx, &FIFO_udpIp);
			
			utils_sendDebugPGM(DEBUG_CH, _SHUT_DOWN, 0, 0);
			i = 0;
			k++;
		}
	}
	else {
		command_exec(DC_DC_OFF);
		fpProgModeVar = (fpProgMode)fpProgModeTable[0];					//go to main mode
		k = 0;
		i = 0;
	}
}
void offMode(){
	static uint16_t i;
	static uint8_t k;
	if (k != 40) {
		if (i++ == 0x2fff) {
			utils_sendDebugPGM(DEBUG_CH, _INA_CURRENT, utils_hex2ArrayToDecAscii4Array(INA_BTS.currentBuff), 4);
			if ((((INA_BTS.currentBuff[0] << 8) | (INA_BTS.currentBuff[1])) <= SHUTDOWN_LEVEL) && ((INA_BTS.currentBuff[0] << 8) | (INA_BTS.currentBuff[1])) != 0){
				_delay_ms(1000);
				command_exec(DC_DC_OFF);
			}
			i = 0;
			k++;
		}
	}
	else {
		command_exec(DC_DC_OFF);
		fpProgModeVar = (fpProgMode)fpProgModeTable[0];			//go to main mode
		k = 0;
		i = 0;
	}
}
