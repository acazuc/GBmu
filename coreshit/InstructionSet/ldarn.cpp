
#include <jackshit.h>

byte core::ldarn( void )
{
	regs.b.a = mem[0xFF00 + ( byte ) mem[regs.w.pc + 1]];
	regs.w.pc += 2;
	return 3;
}
