
#include <jackshit.h>

byte core::ldhlda( void )
{
	mem[regs.w.hl] = regs.b.a;
	regs.w.hl--;
	regs.w.pc++;
	return 2;
}
