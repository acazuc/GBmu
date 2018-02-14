
#include <jackshit.h>

byte core::daa( void )
{
	if ( regs.b.f & NFLAG )
	{
		if ( regs.b.f & CYFLAG )
			regs.b.a -= 0x60;
		if ( regs.b.f & HFLAG )
			regs.b.a -= 0x06;
	}
	else
	{
		if ( ( regs.b.f & HFLAG ) || ( ( regs.b.a & 0x0f ) > 0x09 ) )
			regs.b.a += 0x06;

		if ( ( regs.b.f & CYFLAG ) || ( ( regs.b.a & 0xf0 ) > 0x90 ) )
		{
			regs.b.a += 0x60;
			regs.b.f |= CYFLAG;
		}
	}

	regs.b.f &= ~NFLAG;
	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 1;
}
