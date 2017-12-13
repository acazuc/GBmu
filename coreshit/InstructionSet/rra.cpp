
#include <jackshit.h>

byte core::rra( void )
{
	byte cy;

	if ( regs.b.a & 1 )
		cy = CYFLAG;
	else
		cy = 0;

	if ( regs.b.f & CYFLAG )
		regs.b.a = ( regs.b.a >> 1 ) + 128;
	else
		regs.b.a >>= 1;

	regs.b.f = cy;

	regs.w.pc++;
	return 1;
}
