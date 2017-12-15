
#include <jackshit.h>

byte core::slahl( void )
{
	byte b = mem[regs.w.hl];

	if ( b & 128 )
		regs.b.f = CYFLAG;
	else
		regs.b.f = 0;

	b <<= 1;

	ZUPDATE( b );

	mem[regs.w.hl] = b;
	regs.w.pc++;
	return 4;
}
