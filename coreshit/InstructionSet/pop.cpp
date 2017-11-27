
#include <jackshit.h>

byte core::popbc( void )
{
	regs.w.bc = mem[regs.w.sp];
	regs.w.sp += 2;
	regs.w.pc++;
	return 3;
}

byte core::popde( void )
{
	regs.w.de = mem[regs.w.sp];
	regs.w.sp += 2;
	regs.w.pc++;
	return 3;
}

byte core::pophl( void )
{
	regs.w.hl = mem[regs.w.sp];
	regs.w.sp += 2;
	regs.w.pc++;
	return 3;
}

byte core::popaf( void )
{
	regs.w.af = mem[regs.w.sp];
	regs.w.sp += 2;
	regs.w.pc++;
	return 3;
}




