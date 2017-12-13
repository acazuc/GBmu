
#include <jackshit.h>

byte core::rla( void )
{
	byte cy;

	if ( regs.b.a & 128 )
		cy = CYFLAG;
	else
		cy = 0;

	if ( regs.b.f & CYFLAG )
		regs.b.a = ( regs.b.a << 1 ) + 1;
	else
		regs.b.a <<= 1;

	regs.b.f = cy;

	regs.w.pc++;
	return 1;
}
