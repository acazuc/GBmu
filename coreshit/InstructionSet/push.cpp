
#include <jackshit.h>

byte core::pushbc( void )
{
	mem[regs.w.sp -= 2] = regs.w.bc;
	regs.w.pc++;
	return 4;
}

byte core::pushde( void )
{
	mem[regs.w.sp -= 2] = regs.w.de;
	regs.w.pc++;
	return 4;
}

byte core::pushhl( void )
{
	mem[regs.w.sp -= 2] = regs.w.hl;
	regs.w.pc++;
	return 4;
}

byte core::pushaf( void )
{
	mem[regs.w.sp -= 2] = regs.w.af;
	regs.w.pc++;
	return 4;
}
