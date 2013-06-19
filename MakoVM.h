#ifndef MAKOVM
#define MAKOVM

#define MEM_SIZE	260

#define OP_CONST   0
#define OP_CALL    1
#define OP_JUMP    2
#define OP_JUMPZ   3
#define OP_JUMPIF  4

#define OP_LOAD    10
#define OP_STOR    11
#define OP_RETURN  12
#define OP_DROP    13
#define OP_SWAP    14
#define OP_DUP     15
#define OP_OVER    16
#define OP_STR     17
#define OP_RTS     18

#define OP_ADD     19
#define OP_SUB     20
#define OP_MUL     21
#define OP_DIV     22
#define OP_MOD     23
#define OP_AND     24
#define OP_OR      25
#define OP_XOR     26
#define OP_NOT     27
#define OP_SGT     28
#define OP_SLT     29
#define OP_SYNC    30
#define OP_NEXT    31

#define PC   0 // program counter
#define DP   1 // data stack pointer
#define RP   2 // return stack pointer

#define GP   3 // grid pointer
#define GT   4 // grid tile pointer
/*#define SP   5 // sprite pointer
#define ST   6 // sprite tile pointer
#define SX   7 // scroll X
#define SY   8 // scroll Y
#define GS   9 // grid horizontal skip
#define CL  10 // clear color*/
#define RN  11 // random number
#define KY  12 // key input

#define CO  13 // character-out (debug)
#define AU  14 // audio-out (8khz, 8-bit)
#define KB  15 // keyboard-in

#define XO  16 // bidirectional external IO
#define XA  17 // external argument 
#define XS  18 // external status

#define RESERVED_HEADER  19

#define H_MIRROR_MASK  0x10000 // sprite is mirrored horizontally?
#define V_MIRROR_MASK  0x20000 // sprite is mirrored vertically?
#define GRID_Z_MASK  0x40000000 // grid tile is drawn above sprites?

#define KEY_UP  0x01
#define KEY_RT  0x02
#define KEY_DN  0x04
#define KEY_LF  0x08
#define KEY_A   0x10
#define KEY_B   0x20
#define KEY_MASK  KEY_UP | KEY_RT | KEY_DN | KEY_LF | KEY_A | KEY_B

#define X_CLOSE       0
#define X_OPEN_READ   1
#define X_OPEN_WRITE  2

void vm_run();
int vm_load(int addr);
void vm_stor(int addr, int value);

#endif