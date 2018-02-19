#ifndef UTILS_H_
#define UTILS_H_

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdbool.h>
#include "defines.h"
#include "structures.h"
#include "w5200.h"
#include "commands.h"

extern uint16_t *pArrOfLedsvalGlobal;
extern uint16_t umtsArrLeds[];
extern uint16_t lteArrLeds[];


void utils_sendAnswerDebug(uint8_t ch,const uint8_t *wordPGM,uint8_t *buff, uint8_t length);
void utils_sendAnswer(uint8_t ch,uint8_t *word,uint8_t *buff, uint8_t length);
uint8_t* utils_hex8ToDecAscii16(uint8_t hex);
uint8_t* utils_hex8ToAscii16(uint8_t hex);
uint8_t* utils_hex16ToAscii32(uint16_t hex);
uint8_t* utils_hexArrayToAsciiArray(uint8_t* hex, uint8_t length);
uint8_t utils_ascii16ToHex8(uint16_t ascii);
uint8_t utils_returnOrderedNum(uint8_t* interReg);
uint8_t* utils_hex2ArrayToDecAscii4Array(uint8_t* hex);


typedef void (*fpStatusLed)(void);
fpStatusLed blinkFuncPtr;
void utils_fastBlink();
void utils_middleBlink();
void utils_slowBlink();
//extern const fpBlinkLed blinkPtrTable[] PROGMEM;
extern fpStatusLed blinkPtrTable[];
	
typedef void (*fpFanLed)(void);
fpFanLed fanLedFuncPtr;
void utils_greenLight();
void utils_yellowLight();
void utils_redLight();
void utils_redBLink();
void utils_allBLink();
extern fpFanLed lightPtrTable[];	
	
typedef void (*fpPowerLed)(POWER_LEDS_t*);
void utils_powerLedNormal(POWER_LEDS_t*);
void utils_powerLedEmergencyBW(POWER_LEDS_t*);
void utils_powerLedEmergencyOverPower(POWER_LEDS_t*);
//extern const fpPowerLed powerLedPtrTable[] PROGMEM;
extern fpPowerLed powerLedPtrTable[];


void utils_switchFan(twi_device_t* sensor);
void utils_controlTempPA(twi_device_t* pa);


void utils_avgValue(ANALOG_INPUT_t* filter, uint16_t newValue);
uint8_t* utils_hex16ToDecAscii32(uint16_t hex);
 
extern POWER_LEDS_t POWER_LEDS1;
extern POWER_LEDS_t POWER_LEDS2;
extern POWER_LEDS_t POWER_LEDS3;

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