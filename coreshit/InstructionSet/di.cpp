
#include <jackshit.h>

byte core::di( void )
{
	mem[IE] = 0x00;

	regs.w.pc++;
	return 1;
}
