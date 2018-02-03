
#include <jackshit.h>

byte core::ldhlspe( void )
{
	byte csave;

	csave = regs.b.sph;
	regs.w.hl = regs.w.sp + ( char ) mem[regs.w.pc + 1];

	regs.b.f = 0;
	CARRYUPDATE( csave, regs.b.sph );

	regs.w.pc += 2;
	return 3;
}
