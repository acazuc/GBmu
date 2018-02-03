
#include <jackshit.h>

byte core::di( void )
{
	ime = false;

	regs.w.pc++;
	return 1;
}
