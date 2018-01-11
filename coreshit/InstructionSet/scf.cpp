
#include <jackshit.h>

byte core::scf( void )
{
	regs.b.f |= CYFLAG;

	regs.w.pc++;
	return 1;
}
