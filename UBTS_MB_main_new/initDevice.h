#ifndef INITDEVICE_H_
#define INITDEVICE_H_

#include "defines.h"
#include <util/delay.h>
#include "usart.h"
#include "w5200.h"
#include "ISR.h"
#include "twi.h"
//#include "structures.h"
#include "commands.h"



extern uint8_t configBuff[];
extern  uint8_t calibBuff[];

void init_all(void);
void init_clock(void);
void init_port(void);
void reset_w5200(void);
void init_ina(void);
void startDCs();


#endif /* INITDEVICE_H_ */