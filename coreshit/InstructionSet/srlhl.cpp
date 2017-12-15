
#include <jackshit.h>

byte core::srlhl( void )
{
	byte b = mem[regs.w.hl];

	if ( b & 1 )
		regs.b.f = CYFLAG;
	else
		regs.b.f = 0;

	b >>= 1;

	ZUPDATE( b );

	mem[regs.w.hl];
	regs.w.pc++;
	return 2;
}
