
#include <jackshit.h>

byte core::ldahld( void )
{
	regs.b.a = mem[regs.w.hl];
	regs.w.hl--;
	regs.w.pc++;
	return 2;
}
