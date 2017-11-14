
#include <jackshit.h>

void core::ldade( void )
{
	regs.b.a = mem[regs.w.de];
	regs.w.pc++;
}
