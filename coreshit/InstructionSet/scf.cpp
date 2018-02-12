
#include <jackshit.h>

byte core::scf( void )
{
	regs.b.f &= ~( HFLAG | NFLAG );

	regs.b.f |= CYFLAG;

	regs.w.pc++;
	return 1;
}
