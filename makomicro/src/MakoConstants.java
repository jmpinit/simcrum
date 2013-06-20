public interface MakoConstants {
	public static final int OP_CONST  = 0;
	public static final int OP_CALL   = 1;
	public static final int OP_JUMP   = 2;
	public static final int OP_JUMPZ  = 3;
	public static final int OP_JUMPIF = 4;

	public static final int OP_LOAD   = 10;
	public static final int OP_STOR   = 11;
	public static final int OP_RETURN = 12;
	public static final int OP_DROP   = 13;
	public static final int OP_SWAP   = 14;
	public static final int OP_DUP    = 15;
	public static final int OP_OVER   = 16;
	public static final int OP_STR    = 17;
	public static final int OP_RTS    = 18;

	public static final int OP_ADD    = 19;
	public static final int OP_SUB    = 20;
	public static final int OP_MUL    = 21;
	public static final int OP_DIV    = 22;
	public static final int OP_MOD    = 23;
	public static final int OP_AND    = 24;
	public static final int OP_OR     = 25;
	public static final int OP_XOR    = 26;
	public static final int OP_NOT    = 27;
	public static final int OP_SGT    = 28;
	public static final int OP_SLT    = 29;
	public static final int OP_NEXT   = 30;
	public static final int OP_ROM    = 31;
	public static final int OP_STOP   = 32;

	public static final int PC =  0; // program counter
	public static final int DP =  1; // data stack pointer
	public static final int RP =  2; // return stack pointer

	public static final int RESERVED_HEADER = 3;
}
