
#include <jackshit.h>

byte core::ldhlspe( void )
{
	byte csave;
	xword off;
	word cy;

	csave = regs.b.h;
	off.w = ( char ) mem[regs.w.pc + 1];
	cy = regs.b.spl + off.b.l;
	regs.w.hl = regs.w.sp + off.w;

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
	return 3;
}
