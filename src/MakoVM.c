#include <stdint.h>
#include "inc/MakoVM.h"
#include "inc/Screen.h"

//uint32_t m[MEM_SIZE]; // main memory
uint32_t m[] = {
	139,    160,    210,    0,      0,      0,      0,      0,
	0,      0,      0,      0,      0,      0,      0,      0,
	0,      0,      0,      26,     4,      26,     0,      -1,
	2,      28,     0,      0,      12,     26,     4,      36,
	0,      0,      2,      38,     0,      -1,     12,     17,
	12,     2,      43,     0,      13,     11,     12,     0,
	10,     2,      41,     0,      9,      2,      41,     0,
	32,     2,      41,     0,      1,      20,     17,     1,
	55,     31,     63,     18,     13,     12,     16,     16,
	23,     17,     22,     18,     12,     0,      10,     1,
	70,     0,      48,     19,     14,     15,     3,      92,
	1,      77,     2,      93,     13,     2,      41,     15,
	0,      0,      29,     3,      108,    0,      45,     1,
	41,     0,      -1,     21,     2,      77,     1,      95,
	2,      55,     10,     2,      110,    15,     10,     15,
	3,      126,    1,      41,     2,      129,    13,     13,
	12,     0,      1,      19,     2,      117,    12,     1,
	117,    2,      47,     2,      154,    104,    101,    108,
	108,    111,    32,     119,    111,    114,    108,    100,
	33,     0,      0,      141,    1,      135,    2,      -1,
	0,      0,      0,      0,      0,      0,      0,      0,
	0,      0,      0,      0,      0,      0,      0,      0,
	0,      0,      0,      0,      0,      0,      0,      0,
	0,      0,      0,      0,      0,      0,      0,      0,
	0,      0,      0,      0,      0,      0,      0,      0,
	0,      0,      0,      0,      0,      0,      0,      0,
	0,      0,      0,      0,      0,      0,      0,      0,
	0,      0,      0,      0,      0,      0,      0,      0,
	0,      0,      0,      0,      0,      0,      0,      0,
	0,      0,      0,      0,      0,      0,      0,      0,
	0,      0,      0,      0,      0,      0,      0,      0,
	0,      0,      0,      0,      0,      0,      0,      0,
    0,      0,      0,      0,
};
int keys = 0;

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
		case OP_LOAD   : push(vm_load(pop()));                       break;
		case OP_STOR   : vm_stor(pop(),pop());                       break;
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
	}
}

void vm_run(void) {
	while(m[m[PC]] != OP_SYNC) {
		tick();
		if (m[PC] == -1) break;
	}
	m[PC]++;
}

int vm_load(int addr) {
	//if (addr == RN) { return rand.nextInt(); } // TODO - implement random
	if (addr == KY) { return keys; }
	if (addr == KB) { return -1; }
	if (addr == XS) { return 0; } // TODO - XO features
	return m[addr];
}

void vm_stor(int addr, int value) {
	if(addr == XO) { screen_print_char((char)value); }
	else {
		m[addr] = value;
	}
}

/*void drawTile(int tile, int px, int py) {
	tile &= ~GRID_Z_MASK;
	if (tile < 0) { return; }
	int i = m[GT] + (tile * 8 * 8);
	g.drawRGB(m, i, 8, px, py, 8, 8, true);
}

int[] s = new int[4096]; // sprite buffer
void drawSprite(int tile, int status, int px, int py, Graphics g) {
	if (status % 2 == 0) { return; }
	final int w = (((status & 0x0F00) >>  8) + 1) << 3;
	final int h = (((status & 0xF000) >> 12) + 1) << 3;
	int xd = 1; int x0 = 0; int x1 = w;
	int yd = 1; int y0 = 0; int y1 = h;
	if ((status & H_MIRROR_MASK) != 0) { xd = -1; x0 = w - 1; x1 = -1; }
	if ((status & V_MIRROR_MASK) != 0) { yd = -1; y0 = h - 1; y1 = -1; }
	int i = m[ST] + (tile * w * h);

	for(int y = y0; y != y1; y += yd) {
		for(int x = x0; x != x1; x += xd) {
			s[x + (y * 64)] = m[i++];
		}
	}
	g.drawRGB(s, 0, 64, px, py, w, h, true);
}

private void drawGrid(boolean hiz, int scrollx, int scrolly, Graphics g) {
	int i = m[GP];
	for(int y = 0; y < 31; y++) {
		for(int x = 0; x < 41; x++) {
			if (!hiz && (m[i] & GRID_Z_MASK) != 0) { i++; continue; }
			if ( hiz && (m[i] & GRID_Z_MASK) == 0) { i++; continue; }
			drawTile(m[i++], x*8 - scrollx, y*8 - scrolly, g);
		}
		i += m[GS];
	}
}

public void sync(Graphics g) {
	final int scrollx = m[SX];
	final int scrolly = m[SY];

	// clear screen
	g.setColor(m[CL]);
	g.fillRect(0, 0, 320, 240);

	drawGrid(false, scrollx, scrolly, g);
	for(int sprite = 0; sprite < 1024; sprite += 4) {
		final int status = m[m[SP] + sprite    ];
		final int tile   = m[m[SP] + sprite + 1];
		final int px     = m[m[SP] + sprite + 2];
		final int py     = m[m[SP] + sprite + 3];
		drawSprite(tile, status, px - scrollx, py - scrolly, g);
	}
	drawGrid(true, scrollx, scrolly, g);
}*/