
#include <jackshit.h>

void core::ldhln( void )
{
	mem[regs.w.hl] = mem[regs.w.pc + 1];
	regs.w.pc += 2;
}
