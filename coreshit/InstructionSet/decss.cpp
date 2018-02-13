
#include <jackshit.h>

byte core::decbc( void )
{
	regs.w.bc--;
	regs.w.pc++;
	return 2;
}

byte core::decde( void )
{
	regs.w.de--;
	regs.w.pc++;
	return 2;
}

byte core::dechl( void )
{
	regs.w.hl--;
	regs.w.pc++;
	return 2;
}

byte core::decsp( void )
{
	regs.w.sp--;
	regs.w.pc++;
	return 2;
}
