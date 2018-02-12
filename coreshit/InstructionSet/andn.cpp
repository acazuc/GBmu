
#include <jackshit.h>

byte core::andn( void )
{
	regs.b.a &=( byte ) mem[regs.w.pc + 1];

	regs.b.f = HFLAG;
	ZUPDATE( regs.b.a );

	regs.w.pc += 2;
	return 2;
}
