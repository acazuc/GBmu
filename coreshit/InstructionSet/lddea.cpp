
#include <jackshit.h>

byte core::lddea( void )
{
	mem[regs.w.de] = regs.b.a;
	regs.w.pc++;
	return 2;
}
