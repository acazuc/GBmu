
#include <jackshit.h>

byte core::ldnnsp( void )
{
	mem[mem[regs.w.pc + 1]] = regs.w.sp;
	regs.w.pc += 3;
	return 5;
}
