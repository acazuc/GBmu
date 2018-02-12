
#include <jackshit.h>

byte core::cpla( void )
{
	regs.b.a = ~regs.b.a;
	regs.b.f |= HFLAG | NFLAG;
	regs.w.pc++;
	return 1;
}
