
#include <jackshit.h>

byte core::rlhl( void )
{
	byte cy;
	byte b = mem[regs.w.hl];

	if ( b & 128 )
		cy = CYFLAG;
	else
		cy = 0;

	if ( regs.b.f & CYFLAG )
		b = ( b << 1 ) + 1;
	else
		b <<= 1;

	regs.b.f = cy;
	ZUPDATE( b );

	mem[regs.w.hl];
	regs.w.pc++;
	return 4;
}
