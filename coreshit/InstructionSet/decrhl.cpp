
#include <jackshit.h>

byte core::decrhl( void )
{
	byte be;
	byte af;

	af = mem[regs.w.hl]--;
	be = af + 1;

	regs.b.f |= NFLAG;
	HREVUPDATE( be, af );
	ZUPDATE( af );

	regs.w.pc++;
	return 3;
}
