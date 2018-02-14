
#include <jackshit.h>

byte core::addspe( void )
{
	byte csave;
	xword off;
	word cy;

	csave = regs.b.sph;
	off.w = ( char ) mem[regs.w.pc + 1];
	cy = regs.b.spl + off.b.l;
	regs.w.sp += off.w;

	regs.b.f = 0;
	if ( cy & 0x0100 )
	{
		CARRYUPDATEWITHCARRY( csave, regs.b.sph );
	}
	else
	{
		CARRYUPDATE( csave, regs.b.sph );
	}

	regs.w.pc += 2;
	return 4;
}
