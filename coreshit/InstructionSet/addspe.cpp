
#include <jackshit.h>

byte core::addspe( void )
{
	byte csave;

	csave = regs.b.sph;
	regs.w.sp += ( byte ) mem[regs.w.pc + 1];

	regs.b.f = 0;
	CARRYUPDATE( csave, regs.b.sph );

	regs.w.pc += 2;
	return 4;
}
