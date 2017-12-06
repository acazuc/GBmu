
#include <jackshit.h>

byte core::xorhl( void )
{
	regs.b.a ^=( byte ) mem[regs.w.hl];

	regs.b.f = 0;
	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 2;
}
