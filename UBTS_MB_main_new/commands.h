#ifndef COMMANDS_H_
#define COMMANDS_H_


//#include <avr/pgmspace.h>
#include "usart.h"
#include "PROGM_.h"
#include "w5200.h"
#include "twi.h"
#include "adc.h"
#include "eeprom_defines.h"
#include "initDevice.h"
#include "reads.h"
#include "commutator.h"


extern commutator_t COMMUTATOR;
//extern channel_t CHANNEL[];
extern uint8_t buffer_serialNum[];
extern regs_t REGISTERS;

uint8_t commands_decoder(fifo_t*, buff_t *);
void command_exec(uint8_t);
void(*pBootloader)(void);
void tunePa(buff_t *);
void paOn(twi_device_t* pPa, bool isOn);
void nmOn(bool isOn);
void gpsOn(bool isOn);
void wifiOn(bool isOn);
void setRegisters(uint8_t channel);
void setPaState(uint8_t paNumOn);
bool setPaNumInCh(channel_t *channel);
void setChInCommutator(channel_t * inChannel);
uint8_t checkPermission(uint8_t command, uint8_t type);


#endif /* COMMANDS_H_ */