
#include <jackshit.h>

byte core::reti( void )
{
	regs.w.pc = mem[regs.w.sp];
	regs.w.sp += 2;
	ime = true;
	return 4;
}
