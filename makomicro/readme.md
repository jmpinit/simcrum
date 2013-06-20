8bit Mako
=========
__Original Explanation:__
Mako is a simple stack-based virtual game console, designed to be as simple as possible to implement. Maker is a compiler for a Forth-like language that targets the Mako VM.

Mako has two stacks- a parameter stack and a return stack. Most MakoVM instructions manipulate the top elements of the parameter stack. Instructions are normally a single word (signed 32-bit integer), but some (like JUMP and CALL) are followed by a second word which provides an argument. The Mako memory layout is controlled by a number of memory-mapped registers starting in the lowest address- 0. In addition to the program counter and stack pointers, Mako has registers which control a pixel-scrollable 31x41 grid of 8x8 background tiles, a set of 256 variable-size sprites, a random number generator, optional character I/O facilities for debugging and an 8-bit audio output port. Some implementations additionally provide simple support for filesystem I/O.

__New Explanation:__
8bit Mako is a modified [Mako VM](https://github.com/JohnEarnest/Mako) designed for constrained systems (like the 8 bit microcontroller in [Simulacrum](https://github.com/jmptable/simulacrum)). The most important change is the switch from 32 bits to 8. Other changes optimize the compiler and virtual machine for running with low footprint.