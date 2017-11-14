
#include <jackshit.h>

byte core::ldabc( void )
{
	regs.b.a = mem[regs.w.bc];
	regs.w.pc++;
	return 2;
}
