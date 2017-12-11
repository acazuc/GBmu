
#include <jackshit.h>

byte core::subahl( void )
{
	byte a;

	a = regs.b.a;
	regs.b.a -= ( byte ) mem[regs.w.hl];

	regs.b.f = NFLAG;
	CARRYREVUPDATE( a, regs.b.a );
	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 2;	
}
