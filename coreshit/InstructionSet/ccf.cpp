
#include <jackshit.h>

byte core::ccf( void )
{
	regs.b.f &= ~( HFLAG | NFLAG );

	if ( regs.b.f & CYFLAG )
		regs.b.f &= ~CYFLAG;
	else
		regs.b.f |= CYFLAG;

	regs.w.pc++;
	return 1;
}
