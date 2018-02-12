
#include <jackshit.h>

byte core::cphl( void )
{
	byte a;

	a = regs.b.a - ( byte ) mem[regs.w.hl];

	regs.b.f = NFLAG;
	CARRYREVUPDATE( regs.b.a, a );
	ZUPDATE( a );

	regs.w.pc++;
	return 2;	
}
