
#include <jackshit.h>

byte core::call( void )
{
	mem[regs.w.sp -= 2] = ( word ) regs.w.pc + 3;
	regs.w.pc = mem[regs.w.pc + 1];
	return 6;
}
