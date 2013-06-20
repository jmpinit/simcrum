#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "SDL/SDL.h"
#include "SDL/SDL_thread.h"

#include "Screen.h"
#include "font.h"

SDL_Surface *screen;

#include "util.c"

#define SCREEN_WIDTH	84
#define SCREEN_HEIGHT	48
#define COLUMNS			SCREEN_WIDTH / 6
#define ROWS			SCREEN_HEIGHT / 8
#define ZOOM			4

bool pixels[SCREEN_WIDTH*SCREEN_HEIGHT];
int cursor_x = 0;
int cursor_y = 0;
char text_shadow[84];
const char HEX_TABLE[] = "0123456789ABCDEF";

bool setup = false;

void set(int x, int y);
void unset(int x, int y);
bool get(int x, int y);
void render(void);

void cleanup() {
	SDL_Quit();
}

void setup_SDL() {
	setbuf(stdout, NULL);

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Could not initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}
	
	screen = SDL_SetVideoMode(SCREEN_WIDTH*ZOOM, SCREEN_HEIGHT*ZOOM, 0, SDL_HWPALETTE);
	
	if (screen == NULL) {
		printf("Couldn't set screen mode to 640 x 480: %s\n", SDL_GetError());
		exit(1);
	}
	
	SDL_WM_SetCaption("simulacrum simulator", NULL);
	
	atexit(cleanup);

	setup = true;
}

void screen_initialize() {
	if(!setup) setup_SDL();

	screen_clear(0x00);
	screen_clear_shadow();
}

void screen_clear(unsigned char color) {
	cursor_x = 0;
	cursor_y = 0;

	if(color) {
		for(int y=0; y<SCREEN_HEIGHT; y++) {
			for(int x=0; x<SCREEN_WIDTH; x++) {
				set(x, y);
			}
		}
	} else {
		for(int y=0; y<SCREEN_HEIGHT; y++) {
			for(int x=0; x<SCREEN_WIDTH; x++) {
				unset(x, y);
			}
		}
	}

	render();
}

void screen_clear_shadow() {
	for(int i=0; i<84; i++) text_shadow[i] = ' ';
}

void screen_print_string(char* addr) {
	char c;
	while((c=*addr)) {
		screen_print_char(c);
		addr++;
	}
}

void screen_print_hex(unsigned char val) {
	screen_print_char(HEX_TABLE[val>>4]);
	screen_print_char(HEX_TABLE[val&0x0F]);
}

void screen_print_char(char c) {
	if(invert)
		screen_draw_inverted_char(cursor_x, cursor_y, c);
	else
		screen_draw_char(cursor_x, cursor_y, c);


	cursor_x++;

	if(cursor_x >= COLUMNS) {
		cursor_x = 0;
		cursor_y++;
	}

	if(cursor_y >= ROWS)
		screen_scrollup();

	printf("%c", c);
}

/*
void screen_draw_pos(unsigned char x, unigned char y);
void screen_draw_slice(unsigned char);
void screen_draw_bitmap();
*/

void screen_draw_char(unsigned char x, unsigned char y, char c) {
	text_shadow[y*COLUMNS+x] = c;

	int index = (c-32)*6;
	for(int col=0; col < 6; col++) {
		for(int dy=0; dy < 8; dy++) {
			if(font[index+col]&(1<<dy))
				unset(cursor_x*6+col, cursor_y*8+dy);
			else
				set(cursor_x*6+col, cursor_y*8+dy);
		}
	}

	render();
}

void screen_draw_inverted_char(unsigned char x, unsigned char y, char c) {
	text_shadow[y*COLUMNS+x] = c;

	screen_set_pos(x*6, y);

	int index = (c-32)*6;
	for(int col=0; col < 6; col++) {
		for(int dy=0; dy < 8; dy++) {
			if(font[index+col]&(1<<dy))
				set(cursor_x+col, cursor_y*8+dy);
			else
				unset(cursor_x+col, cursor_y*8+dy);
		}
	}

	render();
}

unsigned char screen_get_x() {
	return cursor_x;
}

unsigned char screen_get_y() {
	return cursor_y;
}

void screen_set_pos(unsigned char x, unsigned char y) {
	cursor_x = x;
	cursor_y = y;
}

void screen_scrollup(void) {
	for(unsigned char i=0; i<70; i++)
        text_shadow[i] = text_shadow[i+14];
   
    for(unsigned char i=70; i<84; i++)
        text_shadow[i] = ' ';
   
    screen_clear(0x00);
   
    for(unsigned char i=0; i<70; i++)
        screen_print_char(text_shadow[i]);
   
    cursor_x = 0;
    cursor_y = ROWS-1;
}

void screen_backspace(void) {
	cursor_x--;
	   
	if(cursor_x < 0 && cursor_y > 0) {
		cursor_x = COLUMNS-1;
		cursor_y--;
	}
}

void screen_newline(void) {
	cursor_x = 0;
	cursor_y++;

	if(cursor_y >= ROWS)
		screen_scrollup();

	printf("\n");
}

/* INTERNAL STUFF */

void set(int x, int y) {
	pixels[y*SCREEN_WIDTH+x] = true;
}

void unset(int x, int y) {
	pixels[y*SCREEN_WIDTH+x] = false;
}

bool get(int x, int y) {
	return pixels[y*SCREEN_WIDTH+x];
}

void render(void) {
	if(SDL_MUSTLOCK(screen)) {
		if(SDL_LockSurface(screen) < 0) {
			fprintf(stderr, "Can't lock screen: %s\n", SDL_GetError());
			return;
		}
	}

	Uint32 white = SDL_MapRGB(screen->format, 0xff, 0xff, 0xff);
	Uint32 black = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
	for(int y=0; y < SCREEN_HEIGHT; y++) {
		for(int x=0; x < SCREEN_WIDTH; x++) {
			if(pixels[y*SCREEN_WIDTH+x])
				drawrect(screen, x*ZOOM, y*ZOOM, ZOOM, ZOOM, white);
			else
				drawrect(screen, x*ZOOM, y*ZOOM, ZOOM, ZOOM, black);
		}
	}

    if(SDL_MUSTLOCK(screen)) SDL_UnlockSurface(screen);

	SDL_UpdateRect(screen, 0, 0, screen->w, screen->h);
}
