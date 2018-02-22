#include "initDevice.h"

void init_clock(){
	/*OSC.CTRL=OSC_RC32MEN_bm;
	OSC.PLLCTRL=OSC_PLLSRC_RC32M_gc;
	while ((OSC.STATUS&OSC_RC32MRDY_bm)==0);
	CCP=CCP_IOREG_gc;
	CLK.CTRL=CLK_SCLKSEL_RC32M_gc;*/
	OSC.XOSCCTRL=OSC_FRQRANGE_12TO16_gc|OSC_XOSCSEL_XTAL_16KCLK_gc;
	OSC.CTRL=OSC_XOSCEN_bm;
	OSC.PLLCTRL=OSC_PLLSRC_XOSC_gc;
	while ((OSC.STATUS&OSC_XOSCRDY_bm)==0);
	CCP=CCP_IOREG_gc;
	CLK.CTRL=CLK_SCLKSEL_XOSC_gc;
}
void init_port(){
	
	/*PORTA.DIR=0xff;
	PORTA.OUT=0x00;
	PORTB.DIR=0xff;
	PORTB.OUT=0x00;*/
	
	PORTC.DIR=0xff;
	PORTC.OUT=0x00;
	/*PORTC.DIRSET=PIN3_bm;					//uart tx
	PORTC.OUTSET=PIN3_bm;					//1
	PORTC.DIRCLR=PIN2_bm;					//uart rx
	PORTC.OUTCLR=PIN2_bm;		*/			//0
	PORTC.DIRCLR=PIN6_bm;
	
	PORTD.DIR=0xff;
	PORTD.OUT=0x00;
	PORTD.OUTSET=PIN4_bm;		//ss
	PORTD.DIRCLR=PIN6_bm;		//miso
	
	PORTE.DIR=0xff;
	PORTE.OUT=0x00;
	PORTE.OUTSET=PIN4_bm;						//set 1 for spi cs w5200
	PORTE.DIRSET=PIN7_bm|PIN5_bm|PIN4_bm;		//set pins as output spi outputs w5200
	PORTE.DIRCLR=PIN6_bm;						//set pin as input for miso w5200
	/*PORTE.DIRSET=PIN3_bm;					//uart tx
	PORTE.OUTSET=PIN3_bm;					//1
	PORTE.DIRCLR=PIN2_bm;					//uart rx
	PORTE.OUTCLR=PIN2_bm;					//0*/
	
	//PORTE.OUT=0x00;
	//PORTCFG.CLKEVOUT=PORTCFG_CLKOUT_PE7_gc;
	PORTF.DIR=0xff;
	PORTF.OUT=0x00;
	PORTF.INTCTRL = PORT_INT0LVL_MED_gc;//PORT_INT0LVL_LO_gc;
	PORTF.DIRCLR=PIN2_bm;						//set input for interrupt from w5200
	PORTF.INT0MASK=PIN2_bm;
	PORTF.PIN2CTRL=PORT_OPC_PULLUP_gc | PORT_ISC_LEVEL_gc;
	PORTF.OUTSET=PIN3_bm;						//set 1 for reset w5200
	PORTF.PIN3CTRL=PORT_OPC_PULLUP_gc;			//reset w5200
	
	PORTF.DIRSET = PIN4_bm | PIN5_bm | PIN6_bm | PIN7_bm;
	PORTF.OUTSET &= ~(PIN4_bm | PIN5_bm | PIN6_bm | PIN7_bm);
	
	PORTJ.DIR=0xff;
	PORTJ.OUT=0x00;
	PORTJ.INTCTRL = PORT_INT0LVL_MED_gc;				//set input for interrupt from dc-dc on-off button
	PORTJ.DIRCLR = PIN5_bm;						
	PORTJ.INT0MASK = PIN5_bm;
	PORTJ.PIN5CTRL = PORT_ISC_FALLING_gc;
	
	PORTH.DIR=0xff;
	PORTH.OUT=0x00;
	
	PORTK.DIR=0xff;
	PORTK.OUT=0x00;
	
	PORTQ.DIR=0xff;
	PORTQ.OUT=0x00;
}
void startDCs(){
	spi_setRegDouble(&SPID, &PORTJ, REGISTERS.dcDcState, MCU_C4_CS0_SREG);				//dc-dc on bts all;
	spi_setReg(&SPIC, &PORTK, REGISTERS.nmGpsWifiPpsState, MCU_SREG_NM_GPS);			//
	spi_setReg(&SPIC, &PORTQ, REGISTERS.resetWifiGpsNmState, MCU_SREG_Reset);			//reset wifi,nm,gps
	
	volatile uint8_t temp = findDuplicate();
	command_exec(0x70);						//holding power on
	commutator_decoder(0x00);				//set default commutator
}
void init_all(){
	cli();
	ISR_init();
	init_clock();
	init_port();
	spi_init(&SPIC, 1000);			//mcu ds0 (pc5,pc6 - pa_onoff,
	spi_init(&SPID, 1000);			//mcu ds1 (face led,
	spi_init(&SPIE, 1000000);		//w5200
	spi_resetRegs();
	usart_init(&USARTE0,BAUD_RATE_OUT);
	usart_init(&USARTC0,BAUD_RATE_GPS);
	usart_init(&USARTD0,BAUD_RATE_NM);
	adc_init(&ADCA);
	adc_init(&ADCB);
	
	twi_init(&TWIC);		//temp board
	twi_init(&TWID);		//temp pa0, pa1
	twi_init(&TWIE);		//ina sensors
	twi_init(&TWIF);		//temp pa2, pa3
	
	reset_w5200();
	w5200_init();
	sei();
	
	init_ina();
}
void reset_w5200(){
	RESET_w5200_on;
	_delay_us(2);
	RESET_w5200_off;
	_delay_ms(150);
}
void init_ina(){
	//////////////////////////////////////////ina bts//////////////////////////////////////////
	TRANSFER.buffer = configBuff;
	TRANSFER.pointer = INA_CONFIG_REG;						//configuration register
	twi_start(&TWIE, &INA_BTS, true, 2);
	twi_start(&TWIE, &INA_BTS, false, 2);
	
	TRANSFER.buffer = calibBuff;
	TRANSFER.pointer = INA_CALIB_REG;						//calibration register
	twi_start(&TWIE, &INA_BTS, true, 2);
	twi_start(&TWIE, &INA_BTS, false, 2);
	
	TRANSFER.pointer = INA_SHUNT_REG;
	twi_start(&TWIE, &INA_BTS, true, 0);
	twi_start(&TWIE, &INA_BTS, false, 2);
	
	TRANSFER.pointer = INA_ID_REG;
	twi_start(&TWIE, &INA_BTS, true, 0);
	twi_start(&TWIE, &INA_BTS, false, 2);
	///////////////////////////////////////////ina periphery////////////////////////////////////
	TRANSFER.buffer = configBuff;
	TRANSFER.pointer = INA_CONFIG_REG;						//configuration register
	twi_start(&TWIE, &INA_PERIPHERY, true, 2);
	twi_start(&TWIE, &INA_PERIPHERY, false, 2);
	
	TRANSFER.buffer = calibBuff;
	TRANSFER.pointer = INA_CALIB_REG;						//calibration register
	twi_start(&TWIE, &INA_PERIPHERY, true, 2);
	twi_start(&TWIE, &INA_PERIPHERY, false, 2);
	
	TRANSFER.pointer = INA_SHUNT_REG;						//shunt register
	twi_start(&TWIE, &INA_PERIPHERY, true, 0);
	twi_start(&TWIE, &INA_PERIPHERY, false, 2);
	
	TRANSFER.pointer = INA_ID_REG;
	twi_start(&TWIE, &INA_PERIPHERY, true, 0);
	twi_start(&TWIE, &INA_PERIPHERY, false, 2);
	/////////////////////////////////////////////////////////////////////////////////////////////
}

