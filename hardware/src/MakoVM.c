#ifndef SIMULATE
#include <stdint.h>
#include <util/delay.h>
#else
#include <stdio.h>
#include <inttypes.h>
#include "delay.h"
#endif

#include "inc/MakoVM.h"
#include "inc/Screen.h"

//uint32_t m[MEM_SIZE]; // main memory
#define PROG_SIZE 113
uint8_t m[] = {
	3,	12,	62,	0,	0,	31,	0,	104,	
	0,	1,	31,	32,	0,	0,	0,	0,	
	0,	0,	0,	0,	0,	0,	0,	0,	
	0,	0,	0,	0,	0,	0,	0,	0,	
	0,	0,	0,	0,	0,	0,	0,	0,	
	0,	0,	0,	0,	0,	0,	0,	0,	
	0,	0,	0,	0,	0,	0,	0,	0,	
	0,	0,	0,	0,	0,	0,	0,	0,	
	0,	0,	0,	0,	0,	0,	0,	0,	
	0,	0,	0,	0,	0,	0,	0,	0,	
	0,	0,	0,	0,	0,	0,	0,	0,	
	0,	0,	0,	0,	0,	0,	0,	0,	
	0,	0,	0,	0,	0,	0,	0,	0,	
	0,	0,	0,	0,	0,	0,	0,	0,	
};

int keys = 0;
int running;

void rom_call(uint8_t routine);

void push(int v)      { m[m[DP]++] = v; }
void rpush(int v)     { m[m[RP]++] = v; }
int pop()             { return m[--m[DP]]; }
int rpop()            { return m[--m[RP]]; }
int mod(int a, int b) { a %= b; return a < 0 ? a+b : a; }

void tick() {
	int o = m[m[PC]++];
	int a, b;

	switch(o) {
		case OP_CONST  : push(m[m[PC]++]);                        break;
		case OP_CALL   : rpush(m[PC]+1); m[PC] = m[m[PC]];        break;
		case OP_JUMP   :                 m[PC] = m[m[PC]];        break;
		case OP_JUMPZ  : m[PC] = pop()==0 ? m[m[PC]] : m[PC]+1;   break;
		case OP_JUMPIF : m[PC] = pop()!=0 ? m[m[PC]] : m[PC]+1;   break;
		case OP_LOAD   : push(vm_load(pop()));                    break;
		case OP_STOR   : vm_stor(pop(),pop());                    break;
		case OP_RETURN : m[PC] = rpop();                          break;
		case OP_DROP   : pop();                                   break;
		case OP_SWAP   : a = pop(); b = pop(); push(a); push(b);  break;
		case OP_DUP    : push(m[m[DP]-1]);                        break;
		case OP_OVER   : push(m[m[DP]-2]);                        break;
		case OP_STR    : rpush(pop());                            break;
		case OP_RTS    : push(rpop());                            break;
		case OP_ADD    : a = pop(); b = pop(); push(b+a);         break;
		case OP_SUB    : a = pop(); b = pop(); push(b-a);         break;
		case OP_MUL    : a = pop(); b = pop(); push(b*a);         break;
		case OP_DIV    : a = pop(); b = pop(); push(b/a);         break;
		case OP_MOD    : a = pop(); b = pop(); push(mod(b,a));    break;
		case OP_AND    : a = pop(); b = pop(); push(b&a);         break;
		case OP_OR     : a = pop(); b = pop(); push(b|a);         break;
		case OP_XOR    : a = pop(); b = pop(); push(b^a);         break;
		case OP_NOT    : push(~pop());                            break;
		case OP_SGT    : a = pop(); b = pop(); push(b>a ? -1:0);  break;
		case OP_SLT    : a = pop(); b = pop(); push(b<a ? -1:0);  break;
		case OP_NEXT   : m[PC] = --m[m[RP]-1]<0?m[PC]+1:m[m[PC]]; break;
		case OP_ROM    : rom_call(pop());                         break;
		case OP_STOP   : running = 0;                             break;
	}
}

void vm_run(void) {
	running = 1;
	while(running) {
		tick();
	}
	m[PC]++;
}

int vm_load(int addr) {
	#ifdef SIMULATE
		if(addr > PROG_SIZE || addr < 0)
			printf("\nLoad violation at %d\n", addr);
	#endif
	return m[addr];
}

void vm_stor(int value, int addr) {
	#ifdef SIMULATE
		if(addr > PROG_SIZE || addr < 0)
			printf("\nStor violation at %d\n", addr);
	#endif
	m[addr] = value;
}

typedef enum {
	ROM_LCD_CLEAR,
	ROM_LCD_CHAR
} rom_call_t;

void rom_call(uint8_t routine) {
	switch(routine) {
		case ROM_LCD_CLEAR:
			screen_clear(0x00);
			break;
		case ROM_LCD_CHAR:
			screen_print_char(pop());
			break;
	}
}
