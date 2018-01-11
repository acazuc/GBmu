
#include <jackshit.h>

byte core::swaphl( void )
{
	byte b = mem[regs.w.hl];

	b = ( b << 4 ) | ( b >> 4 );

	regs.b.f = 0;
	ZUPDATE( b );

	mem[regs.w.hl] = b;
	regs.w.pc++;
	return 2;
}
