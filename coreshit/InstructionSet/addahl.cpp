
#include <jackshit.h>

byte core::addahl( void )
{
	byte a;

	a = regs.b.a;
	regs.b.a += ( byte ) mem[regs.w.hl];

	regs.b.f = 0;
	CARRYUPDATE( a, regs.b.a );
	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 2;
}
