#include "PROGM_.h"

const uint8_t _VERSION[] PROGMEM="\n%UBTS_3U_H00S00*";
const uint8_t _Tboard[] PROGMEM="\ntb=";
const uint8_t _Tpa1[] PROGMEM="\nt0=";
const uint8_t _Tpa2[] PROGMEM="\nt1=";
const uint8_t _Tpa3[] PROGMEM="\nt2=";
const uint8_t _Tpa4[] PROGMEM="\nt3=";

const uint8_t _1_1P[] PROGMEM="\n1_1";
const uint8_t _1_2P[] PROGMEM="\n1_2";
const uint8_t _1_3P[] PROGMEM="\n1_3";
const uint8_t _1_OFF[] PROGMEM="\n1_off";
const uint8_t _2_1P[] PROGMEM="\n2_1";
const uint8_t _2_2P[] PROGMEM="\n2_2";
const uint8_t _2_3P[] PROGMEM="\n2_3";
const uint8_t _2_OFF[] PROGMEM="\n2_off";
const uint8_t _3_1P[] PROGMEM="\n3_1";
const uint8_t _3_2P[] PROGMEM="\n3_2";
const uint8_t _3_3P[] PROGMEM="\n3_3";
const uint8_t _3_OFF[] PROGMEM="\n3_off";
const uint8_t _4_1P[] PROGMEM="\n4_1";
const uint8_t _4_2P[] PROGMEM="\n4_2";
const uint8_t _4_3P[] PROGMEM="\n4_3";
const uint8_t _4_OFF[] PROGMEM="\n4_off";
const uint8_t _COMM_ERR[] PROGMEM="\nchannel error";
const uint8_t _3_2100P[] PROGMEM="\n3_2100";
const uint8_t _4_2100P[] PROGMEM="\n4_2100";

const uint8_t _PA1_ADDR[] PROGMEM="\nPA0_address=";
const uint8_t _PA2_ADDR[] PROGMEM="\nPA1_address=";
const uint8_t _PA3_ADDR[] PROGMEM="\nPA2_address=";
const uint8_t _PA4_ADDR[] PROGMEM="\nPA3_address=";
const uint8_t _PA1_BAND[] PROGMEM="\nPA0_band=";
const uint8_t _PA2_BAND[] PROGMEM="\nPA1_band=";
const uint8_t _PA3_BAND[] PROGMEM="\nPA2_band=";
const uint8_t _PA4_BAND[] PROGMEM="\nPA3_band=";
const uint8_t _PA1_FANPIN[] PROGMEM="\nPA0_fanpin=";
const uint8_t _PA2_FANPIN[] PROGMEM="\nPA1_fanpin=";
const uint8_t _PA3_FANPIN[] PROGMEM="\nPA2_fanpin=";
const uint8_t _PA4_FANPIN[] PROGMEM="\nPA3_fanpin=";
const uint8_t _PA1_ISACTIVE[] PROGMEM="\nPA0_isactive=";
const uint8_t _PA2_ISACTIVE[] PROGMEM="\nPA1_isactive=";
const uint8_t _PA3_ISACTIVE[] PROGMEM="\nPA2_isactive=";
const uint8_t _PA4_ISACTIVE[] PROGMEM="\nPA3_isactive=";

const uint8_t _INA_VOLT[] PROGMEM="\nV=";
const uint8_t _INA_CALIB[] PROGMEM="\nCA=";
const uint8_t _INA_CONFIG[] PROGMEM="\nCO=";
const uint8_t _INA_CURRENT[] PROGMEM="\nI=";
const uint8_t _INA_ID[] PROGMEM="\nID=";
const uint8_t _INA_POWER[] PROGMEM="\nW=";
const uint8_t _INA_SHUNT[] PROGMEM="\nSH=";

const uint8_t _ADC_1[] PROGMEM="\nADC_1=";
const uint8_t _ADC_2[] PROGMEM="\nADC_2=";
const uint8_t _ADC_3[] PROGMEM="\nADC_3=";
const uint8_t _ADC_4[] PROGMEM="\nADC_4=";
const uint8_t _ADC_5[] PROGMEM="\nADC_5=";
const uint8_t _ADC_6[] PROGMEM="\nADC_6=";
const uint8_t _ADC_8[] PROGMEM="\nADC_8=";
const uint8_t _ADC_9[] PROGMEM="\nADC_9=";
const uint8_t _ADC_10[] PROGMEM="\nADC_10=";
const uint8_t _ADC_11[] PROGMEM="\nADC_11=";
const uint8_t _ADC_12[] PROGMEM="\nADC_12=";
const uint8_t _ADC_13[] PROGMEM="\nADC_12=";

const uint8_t _ADC_OUT_PA_1[] PROGMEM="\nPA1=";
const uint8_t _ADC_OUT_PA_2[] PROGMEM="\nPA2=";
const uint8_t _ADC_OUT_PA_3[] PROGMEM="\nPA3=";
const uint8_t _ADC_OUT_PA_4[] PROGMEM="\nPA4=";
const uint8_t _ADC_BW_PA_1[] PROGMEM="\nPA_BW1=";
const uint8_t _ADC_BW_PA_2[] PROGMEM="\nPA_BW2=";
const uint8_t _ADC_BW_PA_3[] PROGMEM="\nPA_BW3=";
const uint8_t _ADC_BW_PA_4[] PROGMEM="\nPA_BW4=";

const uint8_t _PA1[] PROGMEM="\nPA0= ";
const uint8_t _PA2[] PROGMEM="\nPA1= ";
const uint8_t _PA3[] PROGMEM="\nPA2= ";
const uint8_t _PA4[] PROGMEM="\nPA3= ";
const uint8_t _ATT_1[] PROGMEM="\natt_1= ";
const uint8_t _ATT_2[] PROGMEM="\natt_2= ";
const uint8_t _ATT_3[] PROGMEM="\natt_3= ";
const uint8_t _ATT_4[] PROGMEM="\natt_4= ";


//const uint8_t _ZIRO4KA[] PROGMEM="*\n";
//const uint8_t _LINE_FEED[] PROGMEM ="\n";
//const uint8_t _COMMA[] PROGMEM=",";

const uint8_t _GPS_ON[] PROGMEM="\nGPS ON";
const uint8_t _GPS_OFF[] PROGMEM="\nGPS OFF";
const uint8_t _NM_ON[] PROGMEM="\nNM ON";
const uint8_t _NM_OFF[] PROGMEM="\nNM OFF";
const uint8_t _WIFI_ON[] PROGMEM="\nwifi always on";
const uint8_t _WIFI_OFF[] PROGMEM="\nwifi always off";

const uint8_t _OPEN_MAIN[] PROGMEM ="\n**OPENED main**";
const uint8_t _OPEN_NM[] PROGMEM ="\n**OPENED nm**";
const uint8_t _OPEN_DEBUG[] PROGMEM ="\n**OPENED debug**";
const uint8_t _OPEN_GPS[] PROGMEM ="\n**OPENED gps**";
const uint8_t _OPEN_UDP[] PROGMEM ="\n**OPENED udp**";
const uint8_t _CLOSE[] PROGMEM ="\n*******CLOSED*******";
const uint8_t _JMP_BOOTLOADER[] PROGMEM="\nJMP_BOOTLOADER";
const uint8_t _MCU_REBOOT[] PROGMEM="\nMCU_REBOOT";
const uint8_t _ERROR[] PROGMEM ="\n%error*";
const uint8_t _SHUT_DOWN[] PROGMEM ="\nwaiting off...";
const uint8_t _COMBINATION[] PROGMEM ="\ncombination= ";
const uint8_t _OVER_TEMP[] PROGMEM ="\novertemperature";
const uint8_t _OVER_POWER[] PROGMEM ="\nover power= ";
const uint8_t _OVER_POWER_BW[] PROGMEM ="\nover bw power= ";


