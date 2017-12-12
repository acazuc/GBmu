
#include <jackshit.h>

byte core::ret( void )
{
	regs.w.pc = mem[regs.w.sp];
	regs.w.sp += 2;
	return 4;
}
