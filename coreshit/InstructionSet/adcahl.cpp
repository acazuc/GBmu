
#include <jackshit.h>

byte core::adcahl( void )
{
	byte a;

	a = regs.b.a;
	regs.b.a += ( byte ) mem[regs.w.hl];
	if ( regs.b.f & CYFLAG )
	{
		regs.b.a++;
		regs.b.f = 0;
		CARRYUPDATEWITHCARRY( a, regs.b.a );
	}
	else
	{
		regs.b.f = 0;
		CARRYUPDATE( a, regs.b.a );
	}

	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 2;	
}
