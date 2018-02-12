
#include <jackshit.h>

byte core::srahl( void )
{
	byte b = mem[regs.w.hl];

	if ( b & 1 )
		regs.b.f = CYFLAG;
	else
		regs.b.f = 0;

	b >>= 1;
	if ( b & 64 )
		b |= 128;

	ZUPDATE( b );

	mem[regs.w.hl] = b;
	regs.w.pc++;
	return 2;
}
