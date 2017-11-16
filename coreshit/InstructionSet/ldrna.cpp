
#include <jackshit.h>

byte core::ldrna( void )
{
	mem[0xFF + ( byte ) mem[regs.w.pc + 1]] = regs.b.a;
	regs.w.pc++;
	return 3;
}
