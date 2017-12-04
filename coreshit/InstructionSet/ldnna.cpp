
#include <jackshit.h>

byte core::ldnna( void )
{
	mem[mem[regs.w.pc + 1]] = regs.b.a;
	regs.w.pc += 3;
	return 4;
}
