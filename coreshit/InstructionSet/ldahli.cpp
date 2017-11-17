
#include <jackshit.h>

byte core::ldahli( void )
{
	regs.b.a = mem[regs.w.hl];
	regs.w.hl++;
	regs.w.pc++;
	return 2;
}
