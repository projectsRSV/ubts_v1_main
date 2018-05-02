#ifndef READS_H_
#define READS_H_


#include "w5200.h"
#include "defines.h"
#include "structures.h"
#include "eeprom/eeprom_driver.h"
#include "eeprom_defines.h"
#include "adc.h"
#include "initDevice.h"
#include "twi.h"


void read_twiSensors();
void read_sendGps();
void read_sendNMAnswer();
void read_nmCommand();
void read_mainCommand();
void read_sendMainAnswer();
void read_sendDebugAnswer();
void read_debugCommand();
void read_readUDP();
void read_udpCommand();
void read_adc();

extern uint8_t commands_decoder(fifo_t*);

uint8_t read_eeprByte(uint16_t addr);
void read_eeprBuff(uint8_t addr,uint8_t* buff,uint8_t);
void read_eeprom();
void read_writeEEPROMBuff(uint16_t addr, uint8_t* buff, uint8_t length);
void read_writeEEPROMByte(uint16_t addr, uint8_t byte);
void read_commandUART();
//void read_isrW5200();


#endif /* READS_H_ */