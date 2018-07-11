#include <avr\io.h>

; ---
; This routine reads a byte from flash given by the address in
; R25:R24:R23:R22.
;
; Input:
;     R25:R24:R23:R22.
;
; Returns:
;     R24 - Read byte.
; ---

#define a2	r17
#define a1	r16

/*.macro set_io_reg  		
ldi a1,@1 
sts @0,a1 
.endmacro*/


.section .text
.global adc_initAsm

adc_initAsm:

 ldi  zl,0x20
 ldi  zh,0x00
 ldi a1,0x02 
sts NVM_CMD,a1 
 /*set_io_reg NVM_CMD, 0x02   ;Read calibration row */
 lpm  a2,z+

 ldi a1,0x02 
sts NVM_CMD,a1 
 
 /*set_io_reg NVM_CMD, 0x02   ;Read calibration row */
 lpm  a1,z

 sts  ADCA_CAL+0,a2    ;lo
 sts  ADCA_CAL+1,a1    ;hi



 ldi a1,0x05 
sts ADCA_PRESCALER,a1 
 
 /*set_io_reg ADCA_PRESCALER, 0x05 ;div128 */

 /*ldi a1,0x20*/
 ldi a1,0x00 
sts ADCA_REFCTRL,a1 
 
 /*set_io_reg ADCA_REFCTRL, 0x00  ;1v ref*/
 ldi a1,0x04 
sts ADCA_CTRLB,a1 
 
 /*set_io_reg ADCA_CTRLB, 0x04  ;8-bit result, right adjusted*/
 ldi a1,0x01 
sts ADCA_CH0_CTRL,a1 
 
 /*set_io_reg ADCA_CH0_CTRL, 0x01  ;Single-ended positive input signal*/
 ldi a1,0x15 
sts ADCA_CH0_MUXCTRL,a1 
 
 /*set_io_reg ADCA_CH0_MUXCTRL, 0x25 ;ADC4 pin*/

 ldi a1,0x00 
sts ADCA_CTRLA,a1 
 
 /*set_io_reg ADCA_CTRLA, 0x00  ;stop adc ch0*/

 ldi a1,0x00 
sts NVM_CMD,a1 
 
 /*set_io_reg NVM_CMD, 0x00*/




.section .text
.global adc_readAdc

adc_readAdc:

 ldi a1,0x05 
sts ADCA_CTRLA,a1 
 /*set_io_reg ADCA_CTRLA, 0x05  ;start adc ch0*/

 /*ldi  a1,2   ;*8ms=16ms*/
 /*call wait_xms*/
 a:
 lds a1,0x206
 sbrs a1,0
 rjmp a
 sts 0x206,a1

 lds  r24,ADCA_CH0RES+0   ;lo
 
  ldi a1,0x00 
sts ADCA_CTRLA,a1 
 /*set_io_reg ADCA_CTRLA, 0x00  ;stop adc ch0*/


 /*wait_xms:*/
