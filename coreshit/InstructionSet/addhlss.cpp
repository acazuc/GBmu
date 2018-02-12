
#include <jackshit.h>

byte core::addhlbc( void )
{
	byte csave;
	word cy;

	csave = regs.b.h;
	cy = regs.b.l + regs.b.c;
	regs.w.hl += regs.w.bc;

	regs.b.f &= ~NFLAG;
	if ( cy & 0x0100 )
	{
		CARRYUPDATEWITHCARRY( csave, regs.b.h );
	}
	else
	{
		CARRYUPDATE( csave, regs.b.h );
	}

	regs.w.pc++;
	return 2;
}

byte core::addhlde( void )
{
	byte csave;
	word cy;

	csave = regs.b.h;
	cy = regs.b.l + regs.b.e;
	regs.w.hl += regs.w.de;

	regs.b.f &= ~NFLAG;
	if ( cy & 0x0100 )
	{
		CARRYUPDATEWITHCARRY( csave, regs.b.h );
	}
	else
	{
		CARRYUPDATE( csave, regs.b.h );
	}

	regs.w.pc++;
	return 2;
}

byte core::addhlhl( void )
{
	byte csave;
	word cy;

	csave = regs.b.h;
	cy = regs.b.l + regs.b.l;
	regs.w.hl += regs.w.hl;

	regs.b.f &= ~NFLAG;
	if ( cy & 0x0100 )
	{
		CARRYUPDATEWITHCARRY( csave, regs.b.h );
	}
	else
	{
		CARRYUPDATE( csave, regs.b.h );
	}

	regs.w.pc++;
	return 2;
}

byte core::addhlsp( void )
{
	byte csave;
	word cy;

	csave = regs.b.h;
	cy = regs.b.l + regs.b.spl;
	regs.w.hl += regs.w.sp;

	regs.b.f &= ~NFLAG;
	if ( cy & 0x0100 )
	{
		CARRYUPDATEWITHCARRY( csave, regs.b.h );
	}
	else
	{
		CARRYUPDATE( csave, regs.b.h );
	}

	regs.w.pc++;
	return 2;
}


