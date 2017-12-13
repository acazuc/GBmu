
#include <jackshit.h>

byte core::incrhl( void )
{
	byte be;
	byte af;

	be = mem[regs.w.hl]++;
	af = be + 1;

	regs.b.f &= ~NFLAG;
	HUPDATE( be, af );
	ZUPDATE( af );

	regs.w.pc++;
	return 3;
}
