
#include <jackshit.h>

byte core::jphl( void )
{
	regs.w.pc = regs.w.hl;
	return 1;
}
