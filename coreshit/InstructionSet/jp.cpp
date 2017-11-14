
#include <jackshit.h>

byte core::jp( void )
{
	regs.w.pc = mem[regs.w.pc + 1];
	return 4;
}
