#ifndef UTILS_H_
#define UTILS_H_

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdbool.h>
#include <string.h>
#include "defines.h"
#include "structures.h"
#include "w5200.h"
#include "commands.h"



void utils_sendDebugPGM(uint8_t ch, const uint8_t *wordPGM, uint8_t *buff, uint8_t length);
void utils_sendAnswerMain(uint8_t ch, char *word, uint8_t *buff, uint8_t length);
uint8_t* utils_hex8ToDecAscii16(uint8_t hex);
uint8_t* utils_hex8ToAscii16(uint8_t hex);
uint8_t* utils_hex16ToAscii32(uint16_t hex);
uint8_t* utils_hexArrayToAsciiArray(uint8_t* hex, uint8_t length);
uint8_t utils_ascii16ToHex8(uint16_t ascii);
uint8_t utils_returnOrderedNum(uint8_t* interReg);
uint8_t* utils_hex2ArrayToDecAscii4Array(uint8_t* hex);
void utils_sendStDebug(char *word);
void utils_delayMs(uint16_t delay);

typedef void (*fpStatusLed)(void);
fpStatusLed blinkFuncPtr;
void utils_fastBlink();
void utils_middleBlink();
void utils_slowBlink();
extern fpStatusLed blinkLedTable[];

typedef void (*fpFanLed)(void);
fpFanLed fanLedFuncPtr;
void utils_greenLight();
void utils_yellowLight();
void utils_redLight();
void utils_redBLink();
void utils_allBLink();
extern fpFanLed ledFanTable[];

typedef void (*fpPowerLed)(power_leds_t*);
void utils_powerLedNormal(power_leds_t*);
void utils_powerLedEmergencyBW(power_leds_t*);
void utils_powerLedEmergencyOutP(power_leds_t*);
extern fpPowerLed ledsTable[];


void utils_switchFan(twi_device_t* sensor);
void utils_controlTempPA(twi_device_t* pa);
void paOffByNum(uint8_t paNum);

void utils_avgValue(ANALOG_INPUT_t* filter, uint16_t newValue);
uint8_t* utils_hex16ToDecAscii32(uint16_t hex);

extern power_leds_t POWER_LEDS1;
extern power_leds_t POWER_LEDS2;
extern power_leds_t POWER_LEDS3;

static inline bool utils_isFifoEmpty(fifo_t* buff){
	if (buff->head == buff->tail) return true;
	else return false;
}
static inline uint8_t utils_irqSave(void){
	volatile uint8_t flags = SREG;
	cli();
	return flags;
}
static inline void utils_irqRestore(uint8_t flags){
	SREG = flags;
	//sei();
}


#endif /* UTILS_H_ */