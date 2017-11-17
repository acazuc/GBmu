
#include <jackshit.h>

byte core::ldbca( void )
{
	mem[regs.w.bc] = regs.b.a;
	regs.w.pc++;
	return 2;
}
