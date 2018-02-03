
#include <jackshit.h>

byte core::halt( void )
{
	state = CPU_HALT;

	regs.w.pc++;
	return 1;
}
