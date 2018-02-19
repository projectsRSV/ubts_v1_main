#ifndef NVM_H
#define NVM_H



uint8_t nvm_read_byte(uint8_t nvm_cmd, uint16_t address);


static inline uint8_t nvm_read_production_signature_row(uint16_t address){
	return nvm_read_byte(NVM_CMD_READ_CALIB_ROW_gc, address);
}


#endif /* NVM_H */
