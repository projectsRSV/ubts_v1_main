#include "spi.h"

void spi_init(SPI_t *spi, uint32_t baudrate){
	spi_xmega_set_baud_div(spi,baudrate,F_CPU);
	spi_enable_master_mode(spi);
	spi_enable(spi);
}
void spi_xmega_set_baud_div(SPI_t *spi, uint32_t baudrate, uint32_t clkper_hz){
	uint32_t divisor;
	uint8_t divisor_8bit;
	uint8_t ctrl;

	divisor = (clkper_hz + baudrate - 1) / baudrate;

	divisor_8bit = divisor;

	if (divisor_8bit > 64) {
		ctrl = SPI_PRESCALER_DIV128_gc;
	}
	else if (divisor_8bit > 32) {
		ctrl = SPI_PRESCALER_DIV64_gc;
	}
	else if (divisor_8bit > 16) {
		ctrl = SPI_CLK2X_bm | SPI_PRESCALER_DIV64_gc;
	}
	else if (divisor_8bit > 8) {
		ctrl = SPI_PRESCALER_DIV16_gc;
	}
	else if (divisor_8bit > 4) {
		ctrl = SPI_CLK2X_bm | SPI_PRESCALER_DIV16_gc;
	}
	else if (divisor_8bit > 2) {
		ctrl = SPI_PRESCALER_DIV4_gc;
	}
	else {
		ctrl = SPI_CLK2X_bm | SPI_PRESCALER_DIV4_gc;
	}

	spi->CTRL = (spi->CTRL & ~(SPI_CLK2X_bm | SPI_PRESCALER_gm)) | ctrl;
}
uint8_t spi_sendData(SPI_t* spi, uint8_t data){
	uint16_t count = 0x0000;
	if (spi == &SPIC || spi == &SPIE || spi == &SPID){
		spi->DATA = data;
		while((spi->STATUS & SPI_IF_bm) != SPI_IF_bm) {
			if (count++ >= 0xffff){
				return 0x40;
			}
		}
		return spi->DATA;
	}
	else return 0x40;
}
uint8_t spi_recvData(SPI_t* spi, uint8_t data){
	if (spi == &SPIC || spi == &SPIE || spi == &SPID){
		spi->DATA = 0;
		while((spi->STATUS & SPI_IF_bm) != SPI_IF_bm) {};
		return spi->DATA;
	}
	else {
		return 0x40;
	}
}
void spi_setReg(SPI_t* spi, PORT_t *port, uint8_t data, uint8_t pin){
	spi_sendData(spi, data);
	
	_delay_us(5);
	port->OUTSET=pin;
	_delay_us(5);
	port->OUTCLR=pin;
}
void spi_setRegDouble(SPI_t* spi, PORT_t *port, uint16_t data, uint8_t pin){
	spi_sendData(spi, data >> 8);
	spi_sendData(spi, (uint8_t)data);
	
	_delay_us(10);
	port->OUTSET=pin;
	_delay_us(10);
	port->OUTCLR=pin;
}
void spi_resetRegs(){
	
	spi_sendData(&SPIC,0);
	spi_sendData(&SPID,0);
	spi_sendData(&SPID,0);
	
	PORTF.OUTSET = PIN0_bm | PIN4_bm | PIN5_bm | PIN6_bm | PIN7_bm;
	_delay_us(1);
	PORTF.OUTCLR = PIN0_bm | PIN4_bm | PIN5_bm | PIN6_bm | PIN7_bm;
	
	//nm,gps,wifi,1Hz,10MHz,PPS
	PORTK.OUTSET=PIN6_bm | PIN7_bm;
	_delay_us(1);
	PORTK.OUTCLR=PIN6_bm | PIN7_bm;
	
	PORTQ.OUTSET = PIN0_bm | PIN1_bm | PIN2_bm | PIN3_bm;
	_delay_us(1);
	PORTQ.OUTCLR = PIN0_bm | PIN1_bm | PIN2_bm | PIN3_bm;
	
	PORTJ.OUTSET=PIN0_bm | PIN1_bm | PIN2_bm | PIN3_bm | PIN5_bm | PIN6_bm | PIN7_bm;
	_delay_us(1);
	PORTJ.OUTCLR=PIN0_bm | PIN1_bm | PIN2_bm | PIN3_bm | PIN5_bm | PIN6_bm | PIN7_bm;
	
	PORTH.OUTSET=PIN0_bm | PIN1_bm | PIN2_bm | PIN3_bm | PIN4_bm | PIN5_bm | PIN6_bm | PIN7_bm;
	_delay_us(1);
	PORTH.OUTCLR=PIN0_bm | PIN1_bm | PIN2_bm | PIN3_bm | PIN4_bm | PIN5_bm | PIN6_bm | PIN7_bm;
	
}
void spi_startAnime(){
	uint8_t ledValueRender = 1;
	for (uint8_t i=0; i<6; i++){
		ledValueRender |= ledValueRender << 1;
		spi_setReg(&SPID, &PORTH, ledValueRender >> 1, LED_POWER_1);
		spi_setReg(&SPID, &PORTH, ledValueRender >> 1, LED_POWER_2);
		spi_setReg(&SPID, &PORTH, ledValueRender >> 1, LED_POWER_3);
		_delay_ms(START_ANIME_PAUSE);
	}
	ledValueRender = 1;
	for (uint8_t i=0; i<4; i++){
		ledValueRender |= ledValueRender << 1;
		spi_setReg(&SPID, &PORTH, ledValueRender >> 1, LED_CH_REG);
		_delay_ms(START_ANIME_PAUSE);
	}
	spi_setReg(&SPIC, &PORTQ, REGISTERS.ledFanState = LED_FAN_G, MCU_SREG_LED_FAN);
	_delay_ms(START_ANIME_PAUSE);
	spi_setReg(&SPIC, &PORTQ, REGISTERS.ledFanState |= LED_FAN_Y, MCU_SREG_LED_FAN);
	_delay_ms(START_ANIME_PAUSE);
	spi_setReg(&SPIC, &PORTQ, REGISTERS.ledFanState |= LED_FAN_R, MCU_SREG_LED_FAN);
	_delay_ms(START_ANIME_PAUSE);
	
	spi_setRegDouble(&SPID, &PORTJ, REGISTERS.dcDcState | (1 << FAN_BACK), MCU_C4_CS0_SREG);
	_delay_ms(START_ANIME_PAUSE * 2);
	spi_setRegDouble(&SPID, &PORTJ, REGISTERS.dcDcState, MCU_C4_CS0_SREG);
	_delay_ms(START_ANIME_PAUSE * 2);
	spi_setRegDouble(&SPID, &PORTJ, REGISTERS.dcDcState | (1 << FAN_VICOR), MCU_C4_CS0_SREG);
	_delay_ms(START_ANIME_PAUSE * 2);
	spi_setRegDouble(&SPID, &PORTJ, REGISTERS.dcDcState, MCU_C4_CS0_SREG);
	_delay_ms(START_ANIME_PAUSE * 2);
	spi_setRegDouble(&SPID, &PORTJ, REGISTERS.dcDcState | (1 << FAN_PA1), MCU_C4_CS0_SREG);
	_delay_ms(START_ANIME_PAUSE * 2);
	spi_setRegDouble(&SPID, &PORTJ, REGISTERS.dcDcState, MCU_C4_CS0_SREG);
	_delay_ms(START_ANIME_PAUSE * 2);
	spi_setRegDouble(&SPID, &PORTJ, REGISTERS.dcDcState | (1 << FAN_PA2), MCU_C4_CS0_SREG);
	_delay_ms(START_ANIME_PAUSE * 2);
	spi_setRegDouble(&SPID, &PORTJ, REGISTERS.dcDcState, MCU_C4_CS0_SREG);
	_delay_ms(START_ANIME_PAUSE * 2);
	spi_setRegDouble(&SPID, &PORTJ, REGISTERS.dcDcState | (1 << FAN_PA3), MCU_C4_CS0_SREG);
	_delay_ms(START_ANIME_PAUSE * 2);
	spi_setRegDouble(&SPID, &PORTJ, REGISTERS.dcDcState, MCU_C4_CS0_SREG);
	_delay_ms(START_ANIME_PAUSE * 2);
	
	spi_setReg(&SPID, &PORTH, 0, LED_POWER_1);
	spi_setReg(&SPID, &PORTH, 0, LED_POWER_2);
	spi_setReg(&SPID, &PORTH, 0, LED_POWER_3);
	spi_setReg(&SPID, &PORTH, 0, LED_CH_REG);
	spi_setReg(&SPIC, &PORTQ, REGISTERS.ledFanState = 0, MCU_SREG_LED_FAN);
}