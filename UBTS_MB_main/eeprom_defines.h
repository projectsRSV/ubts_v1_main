#ifndef EEPR_H_
#define EEPR_H_

//#include <avr/eeprom.h>
#include <avr/io.h>

#define OFFSET				64

#define EEPR_PAGE_ADDR_start			1
//#define EEPR_PAGE_ADDR_main			2

#define SERIAL_NUM			4		//4
#define IP_SOURCE			8		//4
#define SUBNET_MASK			12		//4
#define GATEWAY_ADDR		16		//4
#define SOCKET				20		//2

#define LENGTH_3d			OFFSET + 22			//1
#define STRING_3d			OFFSET + 23			//50

#define LENGTH_21			OFFSET + 73			//1
#define STRING_21			OFFSET + 74			//50

#define LENGTH_e8			OFFSET + 124		//1
#define STRING_e8			OFFSET + 125		//150

#define I2C_PA0_EEPR		OFFSET + 275		//1
#define I2C_PA1_EEPR		OFFSET + 276		//1
#define I2C_PA2_EEPR		OFFSET + 277		//1
#define I2C_PA3_EEPR		OFFSET + 278		//1

#define BAND_PA0_EEPR		OFFSET + 279		//1
#define BAND_PA1_EEPR		OFFSET + 280		//1
#define BAND_PA2_EEPR		OFFSET + 281		//1
#define BAND_PA3_EEPR		OFFSET + 282		//1

#define VALID_PA0_EEPR		OFFSET + 283		//1
#define VALID_PA1_EEPR		OFFSET + 284		//1
#define VALID_PA2_EEPR		OFFSET + 285		//1
#define VALID_PA3_EEPR		OFFSET + 286		//1

#define ATT_1_EEPR			OFFSET + 287		//1
#define ATT_2_EEPR			OFFSET + 288		//1
#define ATT_3_EEPR			OFFSET + 289		//1
#define ATT_4_EEPR			OFFSET + 290		//1

#define WIFI_ALWAYS_ON		OFFSET + 291		//1

#define MAC_EEP				OFFSET + 292		//6



#endif /* EEPR_H_ */




