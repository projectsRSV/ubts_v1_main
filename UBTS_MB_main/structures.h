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
} BUFF_t;

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
	
	uint16_t i_fan;
	uint16_t i_temp;
	bool fanState;
	uint8_t fanPin;
	uint8_t paPin;
	uint8_t channel;
	
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
	fpGeneric fp;
	uint16_t *pArrLedSt;
	
} power_leds_t;

typedef struct{
	uint8_t sreg1_state_tx;
	uint8_t sreg2_state_tx;
	uint8_t sreg3_state_tx;
	
	uint8_t sreg1_state_rx;
	uint8_t sreg2_state_rx;
	uint8_t sreg3_state_rx;
	
	uint16_t sreg4_state_att;
	uint16_t sreg5_state_att;
	
	uint8_t ch_1;
	uint8_t ch_2;
	uint8_t ch_3;
	uint8_t ch_4;
	
	uint8_t standart_ch_1;
	uint8_t standart_ch_2;
	uint8_t standart_ch_3;
	uint8_t standart_ch_4;
}commut_regs_t;
typedef struct{
	uint8_t nm;
	uint8_t main;
	uint8_t debug;
	uint8_t udp;
}isr_w5200;

//ANALOG_INPUT_t ADC_DET_0, ADC_DET_1, ADC_DET_2, ADC_DET_3, ADC_DET_4, ADC_DET_5, ADC_DET_6, ADC_DET_7;
ANALOG_INPUT_t ADC_PA_BW_1, ADC_PA_BW_2, ADC_PA_BW_3, ADC_PA_BW_4, ADC_PA_OUT_1, ADC_PA_OUT_2, ADC_PA_OUT_3, ADC_PA_OUT_4;
//regs_t REGISTERS;
BUFF_t COMMAND, COMMAND_3d, COMMAND_21, COMMAND_e8;
fifo_t FIFO_gpsCh, FIFO_recUART, FIFO_nmChRx, FIFO_nmChTx, FIFO_mainChTx, FIFO_mainChRx;
transfer_t TRANSFER;
commut_regs_t COMMUTATOR;
isr_w5200 ISR_W5200;
typedef void (*fpProgMode)(void);
fpProgMode fpProgModeVar;
void mainMode();
void sendMode();
void offMode();


#endif /* STRUCTURES_H_ */