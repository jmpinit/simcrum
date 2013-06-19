#ifndef DISK
#define DISK

void disk_init(void);
void disk_read_page(unsigned int address, unsigned char* data, unsigned int len);
unsigned char disk_read(unsigned int address);
void disk_write_page(unsigned int address, unsigned char* data, unsigned char len);
void disk_write(unsigned int address, unsigned char data);

#endif