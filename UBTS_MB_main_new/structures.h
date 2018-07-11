#ifndef STRUCTURES_H_
#define STRUCTURES_H_

#include <avr/io.h>
#include "defines.h"
#include <stdbool.h>



typedef struct {
	uint8_t head;
	uint8_t tail;
	uint8_t data[BUFFER_SIZE];
} fifo_t;

typedef struct{
	uint16_t command;
	uint8_t buffer[BUFF_SIZE_COMM_DATA];
	uint8_t length;
} buff_t;

typedef struct{
	uint8_t configBuff[2];
	uint8_t shuntBuff[2];
	uint8_t voltageBuff[2];
	uint8_t powerBuff[2];
	uint8_t currentBuff[2];
	uint8_t calibBuff[2];
	uint8_t idBuff[2];
	uint8_t *name;
	
	uint8_t addrTWI;
	uint8_t isValid;
	uint8_t isOnState;
	uint8_t band;
	uint8_t temperBuff[2];
	
	uint16_t i_tempFan;
	uint16_t i_tempPA;
	bool fanState;
	uint8_t fanPin;
	uint8_t paPin;
	//uint8_t channelPa;
	
} twi_device_t;

typedef struct{
	TWI_t *bus;				 // Bus register interface
	twi_device_t * twiSensor;
	uint8_t pointer;
	uint8_t pointerCounter;
	uint8_t dataCounter;
	uint8_t *buffer;
	uint8_t buffLength;
	bool isWrite;				 // Bus transfer direction
	
	uint8_t writeCollision;
} transfer_t;

typedef struct{
	uint8_t nmGpsWifiPpsState;
	uint8_t paState;
	uint16_t dcDcState;
	uint8_t resetWifiGpsNmState;
	uint8_t ledChState;
	uint8_t ledFanState;
} regs_t;

typedef struct{
	uint16_t value;
	uint8_t pos;
	uint32_t sum;
	uint16_t buff[FILTER_SAMPLES];
} ANALOG_INPUT_t;

typedef void (*fpGeneric)(void);
typedef struct{
	uint8_t arrayIndex;
	uint8_t ledBit;
	//uint16_t value;
	uint16_t i_main;
	uint8_t i_out;
	uint8_t i_bw;
	uint16_t *adcValueO;
	uint16_t *adcValueBW;
	uint8_t pin;
	uint8_t paNum;
	uint8_t latch;
	fpGeneric fp;
	uint16_t *pArrLedSt;	
} power_leds_t;

typedef struct{
	uint8_t channelNum;
	uint8_t paNum;
	uint8_t band;
	char standart;
	uint8_t isOn;
}channel_t;

typedef struct{
	uint8_t sreg1_state_tx;
	uint8_t sreg2_state_tx;
	uint8_t sreg3_state_tx;
	
	uint8_t sreg1_state_rx;
	uint8_t sreg2_state_rx;
	uint8_t sreg3_state_rx;
	
	uint16_t sreg4_state_att;
	uint16_t sreg5_state_att;
	channel_t channel[4];
	bool nmIsOn;
}commutator_t;

typedef struct{
	uint8_t conNm;
	uint8_t conMain;
	uint8_t conDebug;
	uint8_t conGps;
	uint8_t discNm;
	uint8_t discMain;
	uint8_t discDebug;
	uint8_t discGps;
}isr_w5200;

ANALOG_INPUT_t ADC_PA_BW_1, ADC_PA_BW_2, ADC_PA_BW_3, ADC_PA_BW_4, ADC_PA_OUT_1, ADC_PA_OUT_2, ADC_PA_OUT_3, ADC_PA_OUT_4;
buff_t COMMAND, COMMAND_e8;//, COMMAND_3d, COMMAND_21;
fifo_t FIFO_gpsCh, FIFO_recUART, FIFO_nmChRx, FIFO_nmChTx, FIFO_mainChTx, FIFO_mainChRx, FIFO_debugChRx, FIFO_debugChTx, FIFO_udpChTx, FIFO_udpChRx, FIFO_udpIp;
transfer_t TRANSFER;
isr_w5200 ISR_W5200;
typedef void (*fpProgMode)(void);
fpProgMode fpProgModeVar;
void mainMode();
void sendMode();
void offMode();


#endif /* STRUCTURES_H_ */