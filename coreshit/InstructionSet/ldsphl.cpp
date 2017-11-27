
#include <jackshit.h>

byte core::ldsphl( void )
{
	regs.w.sp = regs.w.hl;
	regs.w.pc++;
	return 2;
}

