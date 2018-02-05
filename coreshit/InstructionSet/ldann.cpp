
#include <jackshit.h>

byte core::ldann( void )
{
	regs.b.a = mem[mem[regs.w.pc + 1]];
	regs.w.pc += 3;
	return 4;
}
