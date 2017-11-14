
#include <jackshit.h>

void core::ldabc( void )
{
	regs.b.a = mem[regs.w.bc];
	regs.w.pc++;
}
