
#include <jackshit.h>

byte core::jphl( void )
{
	regs.w.pc = mem[regs.w.hl];
	return 1;
}
