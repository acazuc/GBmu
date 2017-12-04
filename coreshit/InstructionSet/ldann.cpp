
#include <jackshit.h>

byte core::ldann( void )
{
	regs.b.a = mem[mem[regs.w.pc]];
	regs.w.pc += 3;
	return 4;
}
