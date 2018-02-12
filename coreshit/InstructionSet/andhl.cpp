
#include <jackshit.h>

byte core::andhl( void )
{
	regs.b.a &=( byte ) mem[regs.w.hl];

	regs.b.f = HFLAG;
	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 2;
}
