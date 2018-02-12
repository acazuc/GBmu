
#include <jackshit.h>

byte core::cpn( void )
{
	byte a;

	a = regs.b.a - ( byte ) mem[regs.w.pc + 1];

	regs.b.f = NFLAG;
	CARRYREVUPDATE( regs.b.a, a );
	ZUPDATE( a );

	regs.w.pc += 2;
	return 2;	
}
