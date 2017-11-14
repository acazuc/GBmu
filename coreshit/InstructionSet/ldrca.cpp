
#include <jackshit.h>

byte core::ldrca( void )
{
	mem[0xFF + regs.b.c] = regs.b.a;
	regs.w.pc++;
	return 2;
}
