
#include <jackshit.h>

byte core::incrhl( void )
{
	byte be;
	byte af;

	af = mem[regs.w.hl]++;
	be = af - 1;

	regs.b.f &= ~NFLAG;
	HUPDATE( be, af );
	ZUPDATE( af );

	regs.w.pc++;
	return 3;
}
