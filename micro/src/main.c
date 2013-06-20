#ifndef SIMULATE
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#else
#include "delay.h"
#include <inttypes.h>
#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_thread.h"
#include "bootstrap.h"
#endif

#include "inc/Analog.h"
#include "inc/Disk.h"
#include "inc/Screen.h"
#include "inc/Serial.h"

#include "inc/MakoVM.h"

//#include "logo.h"

#define TRUE	0xFF
#define FALSE	0x00

#define CMD_SIZE 32

void boot(void) {
	//start the LCD
	screen_initialize();
	screen_clear(0xAA);
	
	uart_init(12);
	disk_init();
	adc_init();
}

int run(void* ptr) {
	screen_print_string("running vm");
	screen_newline();
	vm_run();
	screen_newline();
	screen_print_string("vm done");

	for(;;) { __asm__ volatile("NOP"); }

	for(;;) {
		//uart_tx_str("hello world!");
		//uart_tx(13);
		screen_clear(0xFF);
		
		_delay_ms(500);
	}
	
	//print welcome message
	screen_print_string("hello world!");

	for(;;) {
		while(uart_available()) {
			char c = uart_read_buff();
			switch(c) {
				case 13:	//carriage return
					//screen_print_newline();
					break;
				case 12:	//form feed
					screen_clear(0x00);
					break;
				default:
					screen_print_char(c);
			}
		}
	}

	return 0;
}

int main(void) {
	boot();

#ifndef SIMULATE
	run();
#else
	SDL_Thread *thread;

	thread = SDL_CreateThread(run, (void *)NULL);

	if( NULL == thread ) {
		printf("\nSDL_CreateThread failed: %s\n", SDL_GetError()); 
	}

	idle();
#endif

    return(0);
}
