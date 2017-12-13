
#include <jackshit.h>

byte core::decrhl( void )
{
	byte be;
	byte af;

	be = mem[regs.w.hl]--;
	af = be - 1;

	regs.b.f |= NFLAG;
	HREVUPDATE( be, af );
	ZUPDATE( af );

	regs.w.pc++;
	return 3;
}
