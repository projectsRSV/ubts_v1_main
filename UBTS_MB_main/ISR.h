#ifndef ISR_H_
#define ISR_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include "w5200.h"
#include "PROGM_.h"
#include "commands.h"
#include "structures.h"
#include "initDevice.h"


void ISR_init(void);


extern uint8_t commands_decoder(fifo_t* buff);
void twim_interrupt_handler(void);
extern twi_device_t INA_BTS, INA_PERIPHERY, PA1, PA2, PA3, PA4, BOARD;
extern fpProgMode fpProgModeTable[];

#endif /* ISR_H_ */