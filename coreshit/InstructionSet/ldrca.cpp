
#include <jackshit.h>

byte core::ldrca( void )
{
	mem[0xFF00 + regs.b.c] = regs.b.a;
	regs.w.pc++;
	return 2;
}
