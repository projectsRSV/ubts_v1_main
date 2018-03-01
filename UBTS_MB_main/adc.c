#include "adc.h"


//#define adc_getResult(adc,ch)    (adc_getChannel(adc, ch)->RES)

static inline void adc_startConversion(ADC_t *adc){
	uint8_t flags = utils_irqSave();
	
	adc->CTRLA |= ADC_CH0START_bm;
	utils_irqRestore(flags);
}
inline static  ADC_CH_t *adc_getChannel(ADC_t *adc){
	return (ADC_CH_t *)(&adc->CH0);
}
static inline uint16_t adc_getUnsignedResult(ADC_t *adc){
	uint16_t val;
	uint8_t flags;
	ADC_CH_t *adc_ch;

	adc_ch = &adc->CH0;
	flags = utils_irqSave();
	val = adc_ch->RES;
	utils_irqRestore(flags);
	return val;
}

void adc_init(ADC_t *adc){
	if(adc == &ADCB) adc->REFCTRL = ADC_REFSEL_AREFB_gc;
	else adc->REFCTRL = ADC_REFSEL_AREFA_gc;
	//adc->REFCTRL = ADC_REFSEL_INT1V_gc;
	adc->CAL = adc_get_calibration_data(adc);
	//adc->CTRLB = ADC_CONMODE_bm;
	adc->PRESCALER = ADC_PRESCALER_DIV512_gc;
	adc->CTRLA |= ADC_ENABLE_bm;
}
void adc_readData(ADC_t* adc, uint8_t pin){
	uint16_t value;
	ADC_CH_t *adc_ch;
	
	adc_ch = &adc->CH0;
	adc_ch->CTRL = ADC_CH_INPUTMODE0_bm;
	adc_ch->MUXCTRL = pin<<3 ;				//choose number of pins
	//adc->CTRLB = ADC_IMPMODE_bm;
	//adc->CTRLA |= ADC_ENABLE_bm;
	adc->CTRLA |= ADC_CH0START_bm;
	while((adc->INTFLAGS & ADC_CH0IF_bm) != ADC_CH0IF_bm){}
	adc->INTFLAGS |= ADC_CH0IF_bm;
	value = adc_getUnsignedResult(adc);
	
	ANALOG_INPUT_t *adc_det;
	adc_det = adc_selectADC(adc, pin);
	utils_avgValue(adc_det, value);
	
	//return adc_det->value;
	
}
ANALOG_INPUT_t* adc_selectADC(ADC_t *adc,uint8_t pin){
	ANALOG_INPUT_t *pADC;
	pADC = &ADC_PA_OUT_1;
	if (adc == &ADCB){
		switch(pin){
			/*case ADC_CH_1:{
				pADC = (ANALOG_INPUT_t*) &ADC_PA_OUT_0;
				break;
			}			
			case ADC_CH_2:{
				pADC = (ANALOG_INPUT_t*) &ADC_PA_OUT_0;
				break;
			}
			case ADC_CH_3:{
				pADC = (ANALOG_INPUT_t*) &ADC_PA_OUT_0;
				break;
			}
			case ADC_CH_4:{
				pADC = (ANALOG_INPUT_t*) &ADC_PA_OUT_0;
				break;
			}
			case ADC_CH_5:{
				pADC = (ANALOG_INPUT_t*) &ADC_PA_OUT_0;
				break;
			}*/
			case ADC_CH_6:{
				pADC = (ANALOG_INPUT_t*) &ADC_PA_BW_1;//
				break;
			}
			case ADC_CH_7:{
				pADC = (ANALOG_INPUT_t*) &ADC_PA_OUT_1;//
				break;
			}
		}
	}
	else if (adc == &ADCA){
		switch(pin){
			case ADC_CH_2:{
				pADC = (ANALOG_INPUT_t*) &ADC_PA_OUT_2;//
				break;
			}
			case ADC_CH_3:{
				pADC = (ANALOG_INPUT_t*) &ADC_PA_BW_2;//
				break;
			}
			case ADC_CH_4:{
				pADC = (ANALOG_INPUT_t*) &ADC_PA_OUT_3;//
				break;
			}
			case ADC_CH_5:{
				pADC = (ANALOG_INPUT_t*) &ADC_PA_BW_3;//
				break;
			}
			case ADC_CH_6:{
				pADC = (ANALOG_INPUT_t*) &ADC_PA_BW_4;//
				break;
			}
			case ADC_CH_7:{
				pADC = (ANALOG_INPUT_t*) &ADC_PA_OUT_4;//
				break;
			}
		}
	}
	return pADC;
}
void adc_enable(ADC_t *adc){
	uint8_t flags = utils_irqSave();
	adc->CTRLA |= ADC_ENABLE_bm;
	utils_irqRestore(flags);
}
void adc_disable(ADC_t *adc){
	uint8_t flags = utils_irqSave();
	adc->CTRLA &= ~ADC_ENABLE_bm;
	utils_irqRestore(flags);
}