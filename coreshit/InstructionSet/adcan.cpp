
#include <jackshit.h>

byte core::adcan( void )
{
	byte a;

	a = regs.b.a;
	regs.b.a += ( byte ) mem[regs.w.pc + 1];
	if ( regs.b.f & CYFLAG )
		regs.b.a++;

	regs.b.f = 0;
	CARRYUPDATE( a, regs.b.a );
	ZUPDATE( regs.b.a );

	regs.w.pc += 2;
	return 1;	
}
