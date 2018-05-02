
#ifndef COMMUTATOR_H_
#define COMMUTATOR_H_


//#include <stdio>
#include "usart.h"
#include "PROGM_.h"
#include "w5200.h"
#include "twi.h"
#include "adc.h"
#include "eeprom_defines.h"
#include "initDevice.h"
#include "reads.h"


void _1_1(void);
void _1_2(void);
void _1_3(void);
void _1_off(void);

void _2_1(void);
void _2_2(void);
void _2_3(void);
void _2_off(void);

void _3_1(void);
void _3_2(void);
void _3_3(void);
void _3_2100(void);
void _3_off(void);

void _4_1(void);
void _4_2(void);
void _4_3(void);
void _4_2100(void);
void _4_off(void);

void setAttCommutator(uint16_t value4, uint16_t value5);
uint8_t searchCombination(commut_regs_t * commutator);
uint8_t checkInChannelState(void);
uint8_t findDuplicate();	
uint16_t* getArrayOfLeds(char standart, uint8_t isDouble);
bool commutator_decoder(uint8_t address);


extern const uint8_t table_1[];
extern const uint8_t table_2[];
extern const uint8_t table_3[];
extern const uint8_t table_4[];

extern power_leds_t POWER_LEDS1, POWER_LEDS2, POWER_LEDS3;


#endif /* COMMUTATOR_H_ */