/*#include <assembler.h>*/

/*# include "gas.h"*/
# include <avr/io.h>






.section .text
.global nvm_read_byte

nvm_read_byte:
	lds r20, NVM_CMD          ; Store NVM command register
	mov ZL, r22               ; Load byte index into low byte of Z.
	mov ZH, r23               ; Load high byte into Z.
	sts NVM_CMD, r24          ; Load prepared command into NVM Command register.
	lpm r24, Z                ; Perform an LPM to read out byte
	sts NVM_CMD, r20          ; Restore NVM command register
	ret


/*ldi  zl,0x20
 ldi  zh,0x00
 ldi a1,0x02 
sts NVM_CMD,a1 
 lpm  a2,z+

 ldi a1,0x02 
sts NVM_CMD,a1 
 
 lpm  a1,z

 sts  ADCA_CAL+0,a2    ;lo
 sts  ADCA_CAL+1,a1    ;hi*/

	


