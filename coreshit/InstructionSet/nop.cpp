
#include <jackshit.h>

byte core::nop( void )
{
	regs.w.pc++;
	return 1;
}
