
#include <jackshit.h>

byte core::addspe( void )
{
	byte csave;
	char e;
	word cy;

	csave = regs.b.sph;
	e = ( char ) mem[regs.w.pc + 1];
	cy = regs.b.l + e;
	regs.w.sp += e;

	regs.b.f = 0;
	if ( cy & 0x0100 )
	{
		CARRYUPDATEWITHCARRY( csave, regs.b.h );
	}
	else
	{
		CARRYUPDATE( csave, regs.b.h );
	}

	regs.w.pc += 2;
	return 4;
}
