
#include <jackshit.h>

byte core::ins_nop( void )
{
	regs.w.pc++;
	return 1;
}
