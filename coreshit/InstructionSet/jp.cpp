
#include <jackshit.h>

void core::jp( void )
{
	regs.w.pc = mem[regs.w.pc + 1];
}
