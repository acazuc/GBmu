
#include <jackshit.h>

byte core::ldhln( void )
{
	mem[regs.w.hl] = mem[regs.w.pc + 1];
	regs.w.pc += 2;
	return 3;
}
