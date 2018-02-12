
#include <jackshit.h>

byte core::anda( void )
{
	regs.b.a &= regs.b.a;

	regs.b.f = HFLAG;
	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 1;
}

byte core::andb( void )
{
	regs.b.a &= regs.b.b;

	regs.b.f = HFLAG;
	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 1;
}

byte core::andc( void )
{
	regs.b.a &= regs.b.c;

	regs.b.f = HFLAG;
	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 1;
}

byte core::andd( void )
{
	regs.b.a &= regs.b.d;

	regs.b.f = HFLAG;
	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 1;
}

byte core::ande( void )
{
	regs.b.a &= regs.b.e;

	regs.b.f = HFLAG;
	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 1;
}

byte core::andh( void )
{
	regs.b.a &= regs.b.h;

	regs.b.f = HFLAG;
	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 1;
}

byte core::andl( void )
{
	regs.b.a &= regs.b.l;

	regs.b.f = HFLAG;
	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 1;
}
