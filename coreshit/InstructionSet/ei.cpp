
#include <jackshit.h>

byte core::ei( void )
{
	mem[IE] = 0xFF;

	regs.w.pc++;
	return 1;
}
