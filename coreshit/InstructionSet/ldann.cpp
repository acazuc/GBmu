
#include <jackshit.h>

byte core::ldann( void )
{
	regs.b.a = mem[mem[regs.w.pc]];
	regs.w.pc++;
	return 4;
}
