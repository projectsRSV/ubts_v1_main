#include "twi.h"


void twi_init(TWI_t *twi){
	twi->CTRL=0;
	twi->MASTER.BAUD = TWI_BAUD(F_CPU, 250000);
	twi->MASTER.CTRLA = TWI_MASTER_INTLVL0_bm|TWI_MASTER_RIEN_bm|TWI_MASTER_WIEN_bm|TWI_MASTER_ENABLE_bm;
	twi->MASTER.CTRLB = TWI_MASTER_SMEN_bm;// | TWI_MASTER_TIMEOUT_200US_gc;
	twi->MASTER.STATUS = TWI_MASTER_BUSSTATE_IDLE_gc;
}
void twi_start(TWI_t *twi, twi_device_t* sensor, bool isWrite, uint8_t buffLength){
	TRANSFER.bus = twi;
	TRANSFER.isWrite = isWrite;
	TRANSFER.buffLength = buffLength;
	TRANSFER.pointerCounter = 0;
	TRANSFER.dataCounter = 0;
	TRANSFER.twiSensor = sensor;
	//TRANSFER.pointer = sensor->addrTWI;

	if (isWrite){
		twi->MASTER.ADDR = sensor->addrTWI << 1;
	}
	else {
		twi->MASTER.ADDR = (sensor->addrTWI << 1) | 0x01;
	}
	_delay_us(200);
}
