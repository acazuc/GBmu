
#include <jackshit.h>

byte core::andn( void )
{
	regs.b.a &=( byte ) mem[regs.w.pc + 1];

	regs.b.f = 0;
	ZUPDATE( regs.b.a );

	regs.w.pc += 2;
	return 2;
}
