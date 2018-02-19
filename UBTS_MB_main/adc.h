#ifndef ADC_H
#define ADC_H

#include <avr/io.h>
#include "utils.h"
#include "structures.h"
#include "nvm/nvm.h"


//void adc_initAsm(void);
//uint8_t adc_readAdc(void);



void adc_enable(ADC_t *adc);
void adc_disable(ADC_t *adc);
void adc_init(ADC_t *adc);
void adc_readData(ADC_t* adc, uint8_t pin);
ANALOG_INPUT_t* adc_selectADC(ADC_t *adc,uint8_t pin);

static inline uint16_t adc_get_calibration_data(ADC_t* adc){
	uint16_t data;
	
	if (adc == &ADCA){
		data = nvm_read_production_signature_row(0x0021);
		data <<= 8;
		data |= nvm_read_production_signature_row(0x0020);
	}
	else {
		data = nvm_read_production_signature_row(0x0025);
		data <<= 8;
		data |= nvm_read_production_signature_row(0x0024);
	}
	return data;
}



#endif /* ADC_H */
