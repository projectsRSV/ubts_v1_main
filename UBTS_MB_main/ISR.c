#include "ISR.h"


fpProgMode fpProgModeTable[] = {mainMode, sendMode, offMode};


void ISR_init(void){
	CCP = CCP_IOREG_gc;
	PMIC.CTRL = PMIC_LOLVLEN_bm;
}
/***************interrupt vectors******************/
ISR(PORTJ_INT0_vect){
	uint8_t flags = utils_irqSave();
	fpProgModeVar = (fpProgMode)fpProgModeTable[1];							//go to sendMode function
	utils_irqRestore(flags);
}
ISR(TWIC_TWIM_vect){
	uint8_t flags = utils_irqSave();
	twim_interrupt_handler();
	utils_irqRestore(flags);
}
ISR(TWID_TWIM_vect){
	uint8_t flags = utils_irqSave();
	twim_interrupt_handler();
	utils_irqRestore(flags);
}
ISR(TWIE_TWIM_vect){
	uint8_t flags = utils_irqSave();
	twim_interrupt_handler();
	utils_irqRestore(flags);
}
ISR(TWIF_TWIM_vect){
	uint8_t flags = utils_irqSave();
	twim_interrupt_handler();
	utils_irqRestore(flags);
}
ISR(USARTC0_RXC_vect){
	uint8_t flags = utils_irqSave();
	FIFO_gpsCh.data[FIFO_gpsCh.head++] = USARTC0.DATA;
	//FIFO_gpsCh.head &= (BUFFER_SIZE-1);
	utils_irqRestore(flags);
}
ISR(USARTD0_DRE_vect){
	uint8_t flags = utils_irqSave();
	if (FIFO_nmChRx.head != FIFO_nmChRx.tail){
		USARTD0.DATA = FIFO_nmChRx.data[FIFO_nmChRx.tail++];
		//FIFO_nmChRx.tail &= (BUFFER_SIZE-1);
		blinkFuncPtr = (fpStatusLed)(blinkLedTable[0]);				//speed of led blinking
	}
	else USARTD0.CTRLA &= ~USART_DREINTLVL0_bm;
	utils_irqRestore(flags);
}
ISR(USARTD0_RXC_vect){
	uint8_t flags = utils_irqSave();
	FIFO_nmChTx.data[FIFO_nmChTx.head++] = USARTD0.DATA;
	//FIFO_nmChTx.head &= (BUFFER_SIZE-1);
	utils_irqRestore(flags);
}
ISR(USARTE0_RXC_vect){
	uint8_t flags = utils_irqSave();
	FIFO_recUART.data[FIFO_recUART.head++] = USARTE0.DATA;
	//FIFO_recUART.head &= (BUFFER_SIZE-1);
	utils_irqRestore(flags);
}

static inline void twim_write_handler(){
	TWI_t * const bus = TRANSFER.bus;
	if (TRANSFER.pointerCounter < 1){
		bus->MASTER.DATA = TRANSFER.pointer;
		TRANSFER.pointerCounter++;
	}
	else if ((TRANSFER.dataCounter < TRANSFER.buffLength) && (TRANSFER.buffLength != 0)) {
		TRANSFER.bus->MASTER.DATA = TRANSFER.buffer[TRANSFER.dataCounter++];
	}
	else {
		bus->MASTER.CTRLC = TWI_MASTER_CMD_STOP_gc;
	}
}
static inline void twim_read_handler(){
	TWI_t * bus = TRANSFER.bus;
	if (TRANSFER.dataCounter < TRANSFER.buffLength){
		if (TRANSFER.pointer == INA_CONFIG_REG){
			TRANSFER.twiSensor->configBuff[TRANSFER.dataCounter++] = bus->MASTER.DATA;
		}
		else if (TRANSFER.pointer == INA_SHUNT_REG){
			TRANSFER.twiSensor->shuntBuff[TRANSFER.dataCounter++] = bus->MASTER.DATA;
		}
		else if (TRANSFER.pointer == INA_VOLT_REG){
			TRANSFER.twiSensor->voltageBuff[TRANSFER.dataCounter++] = bus->MASTER.DATA;
		}
		else if (TRANSFER.pointer == INA_POWER_REG){
			TRANSFER.twiSensor->powerBuff[TRANSFER.dataCounter++] = bus->MASTER.DATA;
		}
		else if (TRANSFER.pointer == INA_CURRENT_REG){
			TRANSFER.twiSensor->currentBuff[TRANSFER.dataCounter++] = bus->MASTER.DATA;
		}
		else if (TRANSFER.pointer == INA_CALIB_REG){
			TRANSFER.twiSensor->calibBuff[TRANSFER.dataCounter++] = bus->MASTER.DATA;
		}
		else if (TRANSFER.pointer == INA_ID_REG){
			TRANSFER.twiSensor->idBuff[TRANSFER.dataCounter++] = bus->MASTER.DATA;
		}
		else {
			TRANSFER.twiSensor->temperBuff[TRANSFER.dataCounter++] = bus->MASTER.DATA;
		}
	}
	else{
		if (TRANSFER.pointer == INA_VOLT_REG){
			uint16_t temp = (uint32_t)((TRANSFER.twiSensor->voltageBuff[0] << 8) | TRANSFER.twiSensor->voltageBuff[1]) * 125 / 1000;
			TRANSFER.twiSensor->voltageBuff[0] = temp >> 8;
			TRANSFER.twiSensor->voltageBuff[1] = temp;
		}
		else if (TRANSFER.pointer == INA_POWER_REG){
			uint16_t temp = (uint32_t)((TRANSFER.twiSensor->powerBuff[0] << 8) | TRANSFER.twiSensor->powerBuff[1]) * 25 / 10;
			TRANSFER.twiSensor->powerBuff[0] = temp >> 8;
			TRANSFER.twiSensor->powerBuff[1] = temp;
		}
		else if (TRANSFER.pointer == INA_CURRENT_REG){
			uint16_t temp = ((TRANSFER.twiSensor->currentBuff[0] << 8) | TRANSFER.twiSensor->currentBuff[1]);// / 5000;
			TRANSFER.twiSensor->currentBuff[0] = temp >> 8;
			TRANSFER.twiSensor->currentBuff[1] = temp;
		}
		bus->MASTER.CTRLC = TWI_MASTER_CMD_STOP_gc;
	}
}
void twim_interrupt_handler(){
	uint8_t const master_status = TRANSFER.bus->MASTER.STATUS;
	
	if (master_status & TWI_MASTER_ARBLOST_bm) {
		TRANSFER.bus->MASTER.STATUS = master_status | TWI_MASTER_ARBLOST_bm;
		TRANSFER.bus->MASTER.CTRLC  = TWI_MASTER_CMD_STOP_gc;
	}
	else if ((master_status & TWI_MASTER_BUSERR_bm) || (master_status & TWI_MASTER_RXACK_bm)){		//NACK
		TRANSFER.bus->MASTER.CTRLC = TWI_MASTER_CMD_STOP_gc;
		TRANSFER.twiSensor->temperBuff[0] = 0;
	}
	else if (master_status & TWI_MASTER_WIF_bm){
		twim_write_handler();
	}
	else if (master_status & TWI_MASTER_RIF_bm) {
		twim_read_handler();
	}
	TGL_RED_LED_right;
}

