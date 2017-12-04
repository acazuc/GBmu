
#include <jackshit.h>

byte core::ldhlspe( void )
{
	byte csave;

	csave = regs.b.sph;
	regs.w.hl = regs.w.sp += ( byte ) mem[regs.w.pc + 1];
	regs.w.pc += 2;

	regs.b.f = 0;
	CARRYUPDATE( csave, regs.w.sp );

	return 3;
}
