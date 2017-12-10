
#include <jackshit.h>

byte core::addhlbc( void )
{
	byte csave;

	csave = regs.b.h;
	regs.w.hl += regs.w.bc;

	regs.b.f &= ~NFLAG;
	CARRYUPDATE( csave, regs.b.h );

	regs.w.pc++;
	return 2;
}

byte core::addhlde( void )
{
	byte csave;

	csave = regs.b.h;
	regs.w.hl += regs.w.de;

	regs.b.f &= ~NFLAG;
	CARRYUPDATE( csave, regs.b.h );

	regs.w.pc++;
	return 2;
}

byte core::addhlhl( void )
{
	byte csave;

	csave = regs.b.h;
	regs.w.hl += regs.w.hl;

	regs.b.f &= ~NFLAG;
	CARRYUPDATE( csave, regs.b.h );

	regs.w.pc++;
	return 2;
}

byte core::addhlsp( void )
{
	byte csave;

	csave = regs.b.h;
	regs.w.hl += regs.w.sp;

	regs.b.f &= ~NFLAG;
	CARRYUPDATE( csave, regs.b.h );

	regs.w.pc++;
	return 2;
}


