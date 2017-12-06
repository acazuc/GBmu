
#include <jackshit.h>

byte core::jr( void )
{
	regs.w.pc += ( char ) mem[regs.w.pc + 1] + 2;
	return 3;
}
