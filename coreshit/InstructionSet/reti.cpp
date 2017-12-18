
#include <jackshit.h>

byte core::reti( void )
{
	regs.w.pc = mem[regs.w.sp];
	regs.w.sp += 2;
	mem[IE] = 0xFF;
	return 4;
}
