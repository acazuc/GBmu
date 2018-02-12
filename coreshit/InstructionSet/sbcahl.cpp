
#include <jackshit.h>

byte core::sbcahl( void )
{
	byte a;

	a = regs.b.a;
	regs.b.a -= ( byte ) mem[regs.w.hl];
	if ( regs.b.f & CYFLAG )
	{
		regs.b.a--;
		regs.b.f = NFLAG;
		CARRYREVUPDATEWITHCARRY( a, regs.b.a );
	}
	else
	{
		regs.b.f = NFLAG;
		CARRYREVUPDATE( a, regs.b.a );
	}

	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 2;
}
