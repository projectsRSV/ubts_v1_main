#ifndef DEFINES_H_
#define DEFINES_H_


#include <avr/io.h>


#define F_CPU				14745600
//#define F_CPU				32000000
	
#define BOOT_SECTION			0x10000
#define RESET_SECTION			0x0000

//#define DEBUG					0
#define START_ANIME_PAUSE		100
#define SHUTDOWN_LEVEL			116

#define PAUSE_OVER				15

//////*********************************************************************//////
#define MAIN_CH				0
#define DEBUG_CH			1
#define NM_CH				2
#define UDP_CH				3
#define GPS_CH				4

#define MAIN_CH_h			0x01
#define DEBUG_CH_h			0x02
#define NM_CH_h				0x04
#define UDP_CH_h			0x08
#define GPS_CH_h			0x10

#define MAIN_PORT		5000
#define DEBUG_POR		5001
#define GPS_PORT		4000
#define NM_PORT			6000
#define UDP_PORT		5000
//////////////////////////////////////////////************************************

#define  _ADCB					ADCB
#define  _ADCA					ADCA

#define ADC_CH_1			1
#define ADC_CH_2			2
#define ADC_CH_3			3
#define ADC_CH_4			4
#define ADC_CH_5			5
#define ADC_CH_6			6
#define ADC_CH_7			7

#define CS_ON				PORTE.OUTCLR=PIN4_bm
#define CS_OFF				PORTE.OUTSET=PIN4_bm
#define RESET_w5200_on		PORTF.OUTCLR=PIN3_bm
#define RESET_w5200_off		PORTF.OUTSET=PIN3_bm
#define INT_w5200			PORTF.IN&PIN2_bm

#define TGL_RED_LED_left			PORTC.OUTTGL=PIN4_bm
#define TGL_RED_LED_right			PORTD.OUTTGL=PIN4_bm
#define RED_LED_OFF					PORTD.OUTSET=PIN4_bm, PORTC.OUTSET=PIN4_bm
#define RED_LED_ON					PORTD.OUTCLR=PIN4_bm, PORTC.OUTCLR=PIN4_bm

#define BUFFER_SIZE				256		//only 256, if not add	 fifo.tail &= BUFFER_SIZE-1
#define BUFF_SIZE_COMM_DATA		145
#define FILTER_SAMPLES			16

#define BAUD_RATE_OUT			115200
#define BAUD_RATE_GPS			9600
#define BAUD_RATE_NM			115200

//******************I2C addresses********************
		
#define I2C_PERIPHERY		0x40		
#define I2C_BTS				0x41		

#define TEMP_base			0x48
#define TEMP_BOARD			0x48

#define TEMP_PA0			0x49
#define TEMP_PA1			0x4a
#define TEMP_PA2			0x4b
#define TEMP_PA3			0x4c

//**********************INA**************************

#define INA_CONFIG_REG		0x00
#define INA_SHUNT_REG		0x01
#define INA_VOLT_REG		0x02
#define INA_POWER_REG		0x03
#define INA_CURRENT_REG		0x04
#define INA_CALIB_REG		0x05
#define INA_ID_REG			0xfe

//***************************************************

#define GPS_ON			0x0080
//#define GPS_OFF			~0x80 & 0xff
#define NM_ON			0x0010
#define WIFI_ON			0x0040
//#define NM_OFF			~0x10 & 0xff

#define EMPTY_CMD					0xfd
#define SHUTTING_DOWN				0x72
#define DC_DC_ON					0x70
#define DC_DC_OFF					0x71
#define EMULATE_DC_DC_INTERR		0x73
#define NOCOMBINATION				0xff


//***************************************************
#define FAN_PA1			5
#define FAN_PA2			6
#define FAN_PA3			7
#define FAN_PA4			0
#define FAN_VICOR		3
#define FAN_BACK		4

#define PA_ENABLE_1		0
#define PA_ENABLE_2		1
#define PA_ENABLE_3		2
#define PA_ENABLE_4		3

//**********************REGISTERS*******************

#define TX_SREG_SPI_1		PIN4_bm
#define TX_SREG_SPI_2		PIN5_bm
#define TX_SREG_SPI_3		PIN6_bm
#define ST_SREG_SPI_4		PIN7_bm				//att of channels 1-3
#define ST_SREG_SPI_5		PIN0_bm				//att of channels 2-4

#define RX_SREG_SPI_1		PIN0_bm
#define RX_SREG_SPI_2		PIN1_bm
#define RX_SREG_SPI_3		PIN2_bm

//**************************************************

#define MCU_C4_CS0_SREG		PIN4_bm		//dc
#define MCU_SREG_Reset		PIN2_bm		//reset wifi,nm,gps
#define MCU_SREG_PA			PIN6_bm		//pa on off
#define MCU_SREG_NM_GPS		PIN7_bm		//nm, gps
#define MCU_SREG_LED_FAN	PIN0_bm		//led fan

#define LED_POWER_1			PIN3_bm
#define LED_POWER_2			PIN5_bm
#define LED_POWER_3			PIN6_bm

#define LED_CH_REG			PIN7_bm
#define LED_CH1				(1 << 0)
#define LED_CH2				(1 << 1)
#define LED_CH3				(1 << 2)
#define LED_CH4				(1 << 3)
//#define LED_CH4				(1 << 3)
#define LED_FAN_G		(1 << 5)
#define LED_FAN_Y		(1 << 6)
#define LED_FAN_R		(1 << 7)

#define pa1				1
#define pa2				2
#define pa3				4
#define nul				0
#define p13				5

//**************************************************

#define MCU_ON_DCDC_RELAYS_VDC_IN		PORTK.OUTSET=PIN4_bm
#define MCU_OFF_DCDC_RELAYS_VDC_IN		PORTK.OUTCLR=PIN4_bm

//************************temperature***************************

#define TEMP_SHUTDOWN			72
#define TEMP_RED				67
#define TEMP_YELLOW				48
#define TEMP_GREEN				42

#endif /* DEFINES_H_ */

