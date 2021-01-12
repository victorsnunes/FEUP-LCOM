#include <lcom/lcf.h>

#include <stdint.h>

int(util_get_LSB)(uint16_t val, uint8_t *lsb) { //Returns the LSB of a 2 byte integer.
	if (lsb == 0) 
		return 1;

	*lsb = (uint8_t) val;
  	return 0;
}

int(util_get_MSB)(uint16_t val, uint8_t *msb) { //Returns the MSB of a 2 byte integer.
	if (msb == 0) 
		return 1;

	val = val >> 8;
	*msb = (uint8_t)val;
  	return 0;
}

int (util_sys_inb)(int port, uint8_t *value) { //Invokes sys_inb() system call but reads the value into a uint8_t variable.
	uint32_t aux;
	if(sys_inb(port,&aux)!= OK)
		return 1;
    
	*value = (uint8_t) aux;
	return 0;
}
