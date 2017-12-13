
#include <jackshit.h>

byte core::rrchl( void )
{
	byte b = mem[regs.w.hl];

	if ( b & 1 )
	{
		b = ( b >> 1 ) + 128;
		regs.b.f = CYFLAG;
	}
	else
	{
		b >>= 1;
		regs.b.f = 0;
	}

	ZUPDATE( b );

	mem[regs.w.hl] = b;
	regs.w.pc++;
	return 4;
}
