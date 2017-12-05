
#include <jackshit.h>

byte core::sbcan( void )
{
	byte a;

	a = regs.b.a;
	regs.b.a -= ( byte ) mem[regs.w.pc + 1];
	if ( regs.b.f & CYFLAG )
		regs.b.f--;

	regs.b.f = 1;
	CARRYREVUPDATE( a, regs.b.a );
	ZUPDATE( regs.b.a );

	regs.w.pc += 2;
	return 2;
}
