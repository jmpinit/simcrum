#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include "Analog.h"
#include "Disk.h"
#include "Screen.h"
#include "Serial.h"

//#include "logo.h"

#define TRUE	0xFF
#define FALSE	0x00

#define CMD_SIZE 32

void boot(void) {
	//start the LCD
	screen_initialize();
    screen_clear(0x00);
	
	uart_init(12);
	disk_init();
	adc_init();
}

int main(void) {
	boot();
	
	screen_clear(0x00);

    for(;;) {
		while(uart_available()) {
			switch(c) {
				case 13:	//carriage return
					screen_print_newline();
					break
				case 12:	//form feed
					screen_clear(0x00);
					break;
				default:
					char c = uart_read_buff();
					screen_print_char(c);
			}
		}
    }
    
    // Never reached.
    return(0);
}
