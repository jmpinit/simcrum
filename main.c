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
	
	screen_print_string("hi world");
	screen_newline();
	for(int i=0; i<15; i++)
		screen_print_char(disk_read(i));

	/*for(;;) {
		screen_set_pos(0, 0);
		screen_print_hex(adc_read(0));
		screen_print_char(' ');
		screen_print_hex(adc_read(1));
	}*/

	screen_clear(0x00);

	unsigned char last_level1 = 0;
	unsigned char last_level2 = 0;
    for(;;) {
		unsigned int level1 = adc_read(0)>>3; if(level1>=84) level1 = 83;
		unsigned int level2 = adc_read(1)>>3; if(level2>=84) level2 = 83;

		//clear
		screen_draw_pos(level1, 0);
		for(unsigned char i=level1; i<last_level1; i++)
			screen_draw_slice(0);

		screen_draw_pos(level2, 2);
		for(unsigned char i=level2; i<last_level2; i++)
			screen_draw_slice(0);

		//draw
		screen_draw_pos(0, 0);
		for(unsigned char i=0; i<level1; i++)
			screen_draw_slice(0xFF);

		screen_draw_pos(0, 2);
		for(unsigned char i=0; i<level2; i++)
			screen_draw_slice(0xFF);

		last_level1 = level1;
		last_level2 = level2;

		/*while(uart_available()) {
			char c = uart_read_buff();
			screen_print_char(c);
		}*/
    }
    
    // Never reached.
    return(0);
}
