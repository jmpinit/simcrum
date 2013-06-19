#include <util/delay.h>

#include "inc/Disk.h"
#include "inc/i2cmaster.h"

#define ADDRESS 0xA0
#define DISK_SIZE 32767

void disk_init(void) {
	DDRC = (1<<PC5)|(1<<PC4);
	i2c_init();
}

void disk_read_page(unsigned int address, unsigned char* data, unsigned int len) {
	unsigned char ret = i2c_start(ADDRESS+I2C_WRITE);

	if(!ret) {
		i2c_write(address>>8);
		i2c_write(address&0xFF);
		i2c_start(ADDRESS+I2C_READ);

		for(unsigned int i=0; i<len-1; i++)
			data[i] = i2c_readAck();
		data[len-1] = i2c_readNak();

		i2c_stop();
	}
}

unsigned char disk_read(unsigned int address) {
	unsigned char data = 0;

	unsigned char ret = i2c_start(ADDRESS+I2C_WRITE);

	if(!ret) {
		i2c_write(address>>8);
		i2c_write(address&0xFF);
		i2c_start(ADDRESS+I2C_READ);
		data = i2c_readNak();
		i2c_stop();
	}

	return data;
}

void disk_write_page(unsigned int address, unsigned char* data, unsigned char len) {
	unsigned char ret = i2c_start(ADDRESS+I2C_WRITE);
	if(!ret) {
		i2c_write(address>>8);
		i2c_write(address&0xFF);

		for(unsigned char i=0; i<len; i++) {
			i2c_write(data[i]);
		}

		i2c_stop();
	}

	_delay_ms(5);
}

void disk_write(unsigned int address, unsigned char data) {
	unsigned char ret = i2c_start(ADDRESS+I2C_WRITE);

	if(!ret) {
		i2c_write(address>>8);
		i2c_write(address&0xFF);
		i2c_write(data);
		i2c_stop();
	}

	_delay_ms(5);
}
