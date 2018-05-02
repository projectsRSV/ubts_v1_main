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
uint8_t *pGate, *pMask, *pIp;

uint8_t configBuff[2] = {0x47, 0xff};
uint8_t calibBuff[2] = {0x02, 0x00};		//scale = 10A (max = 9.999A); 1mA/bit

uint16_t arrLed1U[] = {1448, 1755, 1838, 1900, 1952, 1975, 2050, 1238};			//6, 11, 16, 21, 27, __,  40, 2.3W - BW
uint16_t arrLed2U[] = {1618, 1855, 1933, 1992, 2047, 2095, 2147, 1438};			//6, 11, 16, 21, 27, __,  40, 2.3W - BW
uint16_t arrLed3U[] = {1218, 1955, 2033, 2092, 2147, 2195, 2247, 1538};			//6, 11, 16, 21, 27, __,  40, 2.3W - BW

uint16_t arrLed1L[] = {1168, 1234, 1282, 1319, 1412, 1440, 1600, 1000};			//6, 11, 16, 21, 27, __,  40, 2.1W - BW
uint16_t arrLed2L[] = {1350, 1442, 1490, 1534, 1790, 1835, 1870, 1080};			//6, 11, 16, 21, 27, __,  40, 2.1W - BW
uint16_t arrLed3L[] = {1830, 1925, 1991, 2030, 2090, 2135, 2170, 1180};			//6, 11, 16, 21, 27, __,  40, 2.1W - BW

twi_device_t PA1 = {.fanPin = FAN_PA1, .paPin = PA_ENABLE_1, .channel = 1, .name = (uint8_t*)_PA1};								//
twi_device_t PA2 = {.fanPin = FAN_PA2, .paPin = PA_ENABLE_2, .channel = 2, .name = (uint8_t*)_PA2};								//
twi_device_t PA3 = {.fanPin = FAN_PA3, .paPin = PA_ENABLE_3, .channel = 4, .name = (uint8_t*)_PA3};								//
twi_device_t PA4 = {.fanPin = FAN_PA4, .paPin = PA_ENABLE_4, .channel = 8, .name = (uint8_t*)_PA4};								//none

twi_device_t BOARD = {.addrTWI = TEMP_BOARD, .fanPin = FAN_BACK};																//
twi_device_t INA_BTS = {.addrTWI = I2C_BTS};
twi_device_t INA_PERIPHERY = {.addrTWI = I2C_PERIPHERY};

regs_t REGISTERS = {.nmGpsWifiPpsState = 0x00, .paState = 0, .dcDcState = 0xf810, .resetWifiGpsNmState = 0x06, .ledChState = 0, .ledFanState = 0};				//all bts,back fan,on wifi, freset and reset wifi on
power_leds_t POWER_LEDS1, POWER_LEDS2, POWER_LEDS3;

void main_ledFanFunc(void);
void setIp(uint8_t* buff, uint8_t value);

int main(void) {
	pGate = buffer_gate;
	pMask = buffer_mask;
	pIp = buffer_ip;
	
	POWER_LEDS1 = (power_leds_t){.ledBit = 1, .fp = (fpGeneric)ledsTable[0], .adcValueO = &ADC_PA_OUT_1.value, .adcValueBW = &ADC_PA_BW_1.value, .pin = LED_POWER_3, .pArrLedSt = arrLed1U};
	POWER_LEDS2 = (power_leds_t){.ledBit = 1, .fp = (fpGeneric)ledsTable[0], .adcValueO = &ADC_PA_OUT_2.value, .adcValueBW = &ADC_PA_BW_2.value, .pin = LED_POWER_2, .pArrLedSt = arrLed1U};
	POWER_LEDS3 = (power_leds_t){.ledBit = 1, .fp = (fpGeneric)ledsTable[0], .adcValueO = &ADC_PA_OUT_3.value, .adcValueBW = &ADC_PA_BW_3.value, .pin = LED_POWER_1, .pArrLedSt = arrLed1U};
	
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
		
		main_ledFanFunc();
	}
}

void main_ledFanFunc(void){
	static uint8_t latch;
	static uint16_t i;
	
	if (i++ == 0x3fff){
		if (latch == 0) {
			if ((PA1.temperBuff[0] == 0 && PA1.isValid == 1) || (PA2.temperBuff[0] == 0 && PA2.isValid == 1) ||
			(PA3.temperBuff[0] == 0 && PA3.isValid == 1) || (PA4.temperBuff[0] == 0 && PA4.isValid == 1)){
				fanLedFuncPtr = (fpFanLed)(ledFanTable[4]);				//fan led blink all
			}
			else if (PA1.temperBuff[0] >= TEMP_SHUTDOWN || PA2.temperBuff[0] >= TEMP_SHUTDOWN || PA3.temperBuff[0] >= TEMP_SHUTDOWN || PA4.temperBuff[0] >= TEMP_SHUTDOWN) {
				fanLedFuncPtr = (fpFanLed)(ledFanTable[3]);				//fan led blink red
				latch = 1;
				utils_sendDebugPGM(DEBUG_CH, _OVER_TEMP, 0, 0);
				command_exec(0x1a);
				paOffAll();
			}
			else if (PA1.temperBuff[0] >= TEMP_RED || PA2.temperBuff[0] >= TEMP_RED || PA3.temperBuff[0] >= TEMP_RED || PA4.temperBuff[0] >= TEMP_RED) {
				fanLedFuncPtr = (fpFanLed)(ledFanTable[2]);				//fan led light red
			}
			else if (!PA1.fanState && !PA2.fanState && !PA3.fanState && !PA4.fanState){
				fanLedFuncPtr = (fpFanLed)(ledFanTable[0]);				//fan led light green
			}
			else if (PA1.temperBuff[0] >= TEMP_YELLOW || PA2.temperBuff[0] >= TEMP_YELLOW || PA3.temperBuff[0] >= TEMP_YELLOW || PA4.temperBuff[0] >= TEMP_YELLOW) {
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

	if (k <= 5) {
		if (i++ >= 0x5fff) {
			for (uint8_t i=0; i<strlen(charact); i++){
				FIFO_udpChTx.data[FIFO_udpChTx.head++] = charact[i];
			}
			for (uint8_t i=0; i<strlen(charact); i++){
				FIFO_udpChTx.data[FIFO_udpChTx.head++] = charact[i];
			}
			utils_sendDebugPGM(DEBUG_CH, _SHUT_DOWN, 0, 0);
			i = 0;
			k++;
		}
	}
	else {
		command_exec(DC_DC_OFF);
		fpProgModeVar = (fpProgMode)fpProgModeTable[0];					//go to main mode
		k = 0;
	}
}
void offMode(){
	static uint16_t i;
	static uint8_t k;
	if (k != 10) {
		if (i++ == 0x0fff) {
			utils_sendDebugPGM(DEBUG_CH, _INA_CURRENT, utils_hex2ArrayToDecAscii4Array(INA_BTS.currentBuff), 4);
			if (((INA_BTS.currentBuff[0] << 8) | (INA_BTS.currentBuff[1])) <= SHUTDOWN_LEVEL){
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
	}
}
