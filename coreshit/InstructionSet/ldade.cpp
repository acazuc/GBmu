
#include <jackshit.h>

byte core::ldade( void )
{
	regs.b.a = mem[regs.w.de];
	regs.w.pc++;
	return 2;
}
