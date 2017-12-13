
#include <jackshit.h>

byte core::ldarn( void )
{
	regs.b.a = mem[0xFF + ( byte ) mem[regs.w.pc]];
	regs.w.pc += 2;
	return 3;
}
