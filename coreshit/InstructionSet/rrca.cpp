
#include <jackshit.h>

byte core::rrca( void )
{
	if ( regs.b.a & 1 )
	{
		regs.b.a = ( regs.b.a >> 1 ) + 128;
		regs.b.f = CYFLAG;
	}
	else
	{
		regs.b.a >>= 1;
		regs.b.f = 0;
	}

	regs.w.pc++;
	return 1;
}
