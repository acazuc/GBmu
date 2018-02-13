
#include <jackshit.h>

byte core::incbc( void )
{
	regs.w.bc++;
	regs.w.pc++;
	return 2;
}

byte core::incde( void )
{
	regs.w.de++;
	regs.w.pc++;
	return 2;
}

byte core::inchl( void )
{
	regs.w.hl++;
	regs.w.pc++;
	return 2;
}

byte core::incsp( void )
{
	regs.w.sp++;
	regs.w.pc++;
	return 2;
}
