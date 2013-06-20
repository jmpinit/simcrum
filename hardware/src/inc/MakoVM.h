#ifndef MAKOVM
#define MAKOVM

void vm_run(void);
int vm_load(int addr);
void vm_stor(int addr, int value);

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
#define OP_NEXT    30
#define OP_ROM     31
#define OP_STOP    32

#define PC   0 // program counter
#define DP   1 // data stack pointer
#define RP   2 // return stack pointer

#define RESERVED_HEADER  3

#endif
