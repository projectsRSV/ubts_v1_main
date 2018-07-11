#ifndef TWI_H_
#define TWI_H_

#include <avr/io.h>
#include <stdbool.h>
#include "structures.h"
#include "initDevice.h"



#define TWI_BAUD(F_CPU, F_TWI)			(F_CPU / (2 * F_TWI)) - 5



void twi_init(TWI_t *twi);
void twi_start(TWI_t *twi, twi_device_t* twiSensor, bool wr_r, uint8_t buffLength);


#endif /* TWI_H_ */