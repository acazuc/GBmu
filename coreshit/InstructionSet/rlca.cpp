
#include <jackshit.h>

byte core::rlca( void )
{
	if ( regs.b.a & 128 )
	{
		regs.b.a = ( regs.b.a << 1 ) + 1;
		regs.b.f = CYFLAG;
	}
	else
	{
		regs.b.a <<= 1;
		regs.b.f = 0;
	}

	regs.w.pc++;
	return 1;
}
