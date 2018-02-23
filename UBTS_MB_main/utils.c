#include "utils.h"



fpStatusLed blinkPtrTable[] = {utils_fastBlink, utils_middleBlink, utils_slowBlink};
fpFanLed lightPtrTable[] = {utils_greenLight, utils_yellowLight, utils_redLight, utils_redBLink, utils_allBLink};

fpPowerLed powerLedPtrTable[] = {utils_powerLedNormal, utils_powerLedEmergencyOverPower, utils_powerLedEmergencyBW};

void utils_sendAnswerDebug(uint8_t ch, const uint8_t *wordPGM, uint8_t *buff, uint8_t length){
	w5200_sendDataPGM(ch,wordPGM);
	for (uint8_t i=0; i<length; i++){
		FIFO_mainChTx.data[FIFO_mainChTx.head++] = buff[i];
	}
	if(length) w5200_sendDataFifo(ch,&FIFO_mainChTx);
}
void utils_sendAnswer(uint8_t ch,uint8_t *word, uint8_t *buff, uint8_t length){
	for (uint8_t i=0; i<4; i++){
		FIFO_mainChTx.data[FIFO_mainChTx.head++] = word[i];
	}
	for (uint8_t i=0; i<length; i++){
		FIFO_mainChTx.data[FIFO_mainChTx.head++] = buff[i];
	}
	FIFO_mainChTx.data[FIFO_mainChTx.head++] = word[4];
	w5200_sendDataFifo(ch,&FIFO_mainChTx);
}
uint8_t* utils_hex8ToDecAscii16(uint8_t hex){
	uint8_t a=0,b=0,c=0;
	static uint8_t pdec[2];
	while (hex>=100) {hex -= 100;a++;}
	while (hex>=10) {hex -= 10;b++;}
	pdec[0]=b+0x30;
	while (hex>=1) {hex -= 1;c++;}
	pdec[1]=c+0x30;
	return pdec;
}

uint8_t* utils_hex2ArrayToDecAscii4Array(uint8_t* hex){
	uint8_t a=0,b=0,c=0,d=0;
	static uint8_t pdec[4];
	uint16_t temp;
	
	temp = hex[0] << 8 | hex[1];
	
	while (temp >= 10000) {temp -= 10000;}
	while (temp >= 1000) {temp -= 1000; a++;}
	pdec[0] = a + 0x30;
	while (temp >= 100) {temp -= 100 ; b++;}
	pdec[1] = b + 0x30;
	while (temp >= 10) {temp -= 10; c++;}
	pdec[2] = c + 0x30;
	while (temp >= 1) {temp -= 1; d++;}
	pdec[3] = d + 0x30;
	return pdec;
}

uint8_t* utils_hex16ToDecAscii32(uint16_t hex){
	uint8_t a=0,b=0,c=0,d=0,e=0;
	static uint8_t pdec[4];
	while (hex>=10000) {hex -= 10000;a++;}
	while (hex>=1000) {hex -= 1000;b++;}
	pdec[0]=b+0x30;
	while (hex>=100) {hex -= 100;c++;}
	pdec[1]=c+0x30;
	while (hex>=10) {hex -= 10;d++;}
	pdec[2]=d+0x30;
	while (hex>=1) {hex -= 1;e++;}
	pdec[3]=e+0x30;
	return pdec;
}
uint8_t* utils_hex8ToAscii16(uint8_t hex){
	uint8_t i,temp;
	static uint8_t array[2];
	temp=hex>>4;
	if (temp>9) i=0x57;
	else i=0x30;
	array[0]=i+temp;
	temp=hex&0x0f;
	if (temp>9) i=0x57;
	else i=0x30;
	array[1]=i+temp;
	return array;
}
uint8_t* utils_hex16ToAscii32(uint16_t hex){
	uint8_t i,temp;
	static uint8_t array[4];
	
	temp=(uint8_t)(hex>>12)&0x0f;;
	if (temp>9) i=0x57;
	else i=0x30;
	array[0]=i+temp;
	temp=(uint8_t)(hex>>8)&0x0f;
	if (temp>9) i=0x57;
	else i=0x30;
	array[1]=i+temp;
	temp=(uint8_t)(hex>>4)&0x0f;
	if (temp>9) i=0x57;
	else i=0x30;
	array[2]=i+temp;
	temp=(uint8_t)(hex)&0x0f;
	if (temp>9) i=0x57;
	else i=0x30;
	array[3]=i+temp;
	return array;
}
uint8_t* utils_hexArrayToAsciiArray(uint8_t* hex, uint8_t length){
	uint8_t n,temp;
	static uint8_t array[8];
	
	for (uint8_t i=0,k=0; i<length; i++,k+=2){
		temp=hex[i]>>4;
		if (temp>9) n=0x57;
		else n=0x30;
		array[k]=n+temp;
		temp=hex[i]&0x0f;
		if (temp>9) n=0x57;
		else n=0x30;
		array[k+1]=n+temp;
	}
	return array;
}
uint8_t utils_ascii16ToHex8(uint16_t ascii){
	uint8_t temp;
	uint8_t byte;
	temp=(uint8_t)(ascii>>8);
	if (temp>=0x61 && temp<=0x66) temp -=0x57;
	else if (temp>=0x41 && temp<=0x46) temp -=0x37;
	else if (temp>=0x30 && temp<=0x39) temp -=0x30;
	else return 0xfb;
	byte=(uint8_t)(temp<<4);
	
	temp=(uint8_t)(ascii & 0x00ff);
	if (temp>=0x61 && temp<=0x66) temp -=0x57;
	else if (temp>=0x41 && temp<=0x46) temp -=0x37;
	else if (temp>=0x30 && temp<=0x39) temp -=0x30;
	else return 0xfb;
	
	byte |=(uint8_t)(temp&0x0f);
	return byte;
}
void utils_fastBlink(){
	static uint16_t i=0;
	if (i++ == 0x03ff){
		TGL_RED_LED_left;
		i=0;
	}
}
void utils_middleBlink(){
	static uint16_t i=0;
	if (i++ == 0x07ff){
		TGL_RED_LED_left;
		i=0;
	}
}
void utils_slowBlink(){
	static uint16_t i=0;
	if (i++ == 0x0fff){
		TGL_RED_LED_left;
		i=0;
	}
}
void utils_powerLedNormal(POWER_LEDS_t* ledStruct){
	if (ledStruct->i++ == 0x1fff) {
		if (pArrOfLedsvalGlobal[ledStruct->arrayIndex] < *ledStruct->adcValue){
			if (ledStruct->arrayIndex < 6){
				ledStruct->arrayIndex++;
				ledStruct->ledValueRender |= (ledStruct->ledValueRender << 1);
				spi_setReg(&SPID, &PORTH, ledStruct->ledValueRender >> 1, ledStruct->pin);
			}
			else {
				ledStruct->fp = (fpGeneric)powerLedPtrTable[2];
			}
		}
		else if ((pArrOfLedsvalGlobal[ledStruct->arrayIndex - 1] - 5) >= *ledStruct->adcValue){
			if (ledStruct->arrayIndex > 0){
				ledStruct->arrayIndex--;
				ledStruct->ledValueRender = (ledStruct->ledValueRender >> 1);
				spi_setReg(&SPID, &PORTH, ledStruct->ledValueRender >> 1, ledStruct->pin);
			}
		}
		ledStruct->i=0;
	}
}
void paOffAll(){
	setPaState(0x00);
	PA1.isValid = 0; PA2.isValid = 0; PA3.isValid = 0; PA4.isValid = 0;
}
void utils_powerLedEmergencyBW(POWER_LEDS_t* ledStruct){
	static uint8_t latch;
	if (!latch){
		latch = 1;
		paOffAll();
	}
	if (ledStruct->i++ == 0x09ff){
		spi_setReg(&SPID,&PORTH, ledStruct->ledValueRender ^= 0xff, ledStruct->pin);
		ledStruct->i=0;
	}
}
void utils_powerLedEmergencyOverPower(POWER_LEDS_t* ledStruct){
	static uint8_t latch;
	if (!latch){
		latch = 1;
		paOffAll();
	}
	if (ledStruct->i++ == 0x09ff){
		spi_setReg(&SPID,&PORTH, ledStruct->ledValueRender ^= 0x20, ledStruct->pin);
		ledStruct->i = 0;
	}
}
uint8_t utils_returnOrderedNum(uint8_t* interReg){
	uint8_t count=0,k=1;
	for (uint8_t i=0; i<8; i++){
		if ((*interReg & (k<<i))){
			*interReg &= ~(k<<i);
			break;
		}else count++;
	}
	return count;
}
void utils_avgValue(ANALOG_INPUT_t* filter, uint16_t newValue){
	filter->sum = filter->sum - filter->buff[filter->pos] + newValue;
	filter->value = filter->sum / FILTER_SAMPLES;
	filter->buff[filter->pos] = newValue;
	filter->pos++;
	filter->pos &= (FILTER_SAMPLES - 1);
}
void utils_greenLight(){
	spi_setReg(&SPIC, &PORTQ, REGISTERS.ledFanState = LED_FAN_GREEN, MCU_SREG_LED_FAN);
}
void utils_yellowLight(){
	spi_setReg(&SPIC, &PORTQ, REGISTERS.ledFanState = LED_FAN_YELL, MCU_SREG_LED_FAN);
}
void utils_redLight(){
	spi_setReg(&SPIC, &PORTQ, REGISTERS.ledFanState = LED_FAN_RED, MCU_SREG_LED_FAN);
}
void utils_redBLink(){
	static uint16_t i;
	if (i++ == 0x09ff){
		spi_setReg(&SPIC, &PORTQ, REGISTERS.ledFanState ^= LED_FAN_RED, MCU_SREG_LED_FAN);
		i=0;
	}
}
void utils_allBLink(){
	static uint16_t i;
	
	if (i++ == 0x09ff){
		spi_setReg(&SPIC, &PORTQ, REGISTERS.ledFanState = LED_FAN_RED | LED_FAN_GREEN | LED_FAN_YELL, MCU_SREG_LED_FAN);
	}
	else if (i == 0x9ff * 2){
		spi_setReg(&SPIC, &PORTQ, REGISTERS.ledFanState = 0, MCU_SREG_LED_FAN);
		i=0;
	}
}
void utils_switchFan(twi_device_t* pa){
	const uint16_t COUNT = 0x3fff;
	
	if (pa->i_fan++ == COUNT){
		pa->i_fan=0;
		if (pa->fanState) REGISTERS.dcDcState |= (1 << pa->fanPin);
		else REGISTERS.dcDcState &= ~ (1 << pa->fanPin);
		spi_setRegDouble(&SPID, &PORTJ, REGISTERS.dcDcState, MCU_C4_CS0_SREG);
	}
}
void utils_controlTempPA(twi_device_t* pa){
	const uint16_t COUNT = 0x3fff;
	
	if (pa->i_temp++ == COUNT){
		pa->i_temp=0;
		uint8_t temperature = pa->temperBuff[0];
		if (temperature == 0 && pa->isValid) pa->fanState = true;
		else if (temperature >= TEMP_YELLOW) {
			pa->fanState = true;
		}
		else if (temperature <= TEMP_GREEN){
			pa->fanState = false;
		}
	}
}