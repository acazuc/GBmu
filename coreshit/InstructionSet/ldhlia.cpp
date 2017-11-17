
#include <jackshit.h>

byte core::ldhlia( void )
{
	mem[regs.w.hl] = regs.b.a;
	regs.w.hl++;
	regs.w.pc++;
	return 2;
}
