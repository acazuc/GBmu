
#include <jackshit.h>

byte core::ora( void )
{
	regs.b.a |= regs.b.a;

	regs.b.f = 0;
	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 1;
}

byte core::orb( void )
{
	regs.b.a |= regs.b.b;

	regs.b.f = 0;
	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 1;
}

byte core::orc( void )
{
	regs.b.a |= regs.b.c;

	regs.b.f = 0;
	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 1;
}

byte core::ord( void )
{
	regs.b.a |= regs.b.d;

	regs.b.f = 0;
	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 1;
}

byte core::ore( void )
{
	regs.b.a |= regs.b.e;

	regs.b.f = 0;
	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 1;
}

byte core::orh( void )
{
	regs.b.a |= regs.b.h;

	regs.b.f = 0;
	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 1;
}

byte core::orl( void )
{
	regs.b.a |= regs.b.l;

	regs.b.f = 0;
	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 1;
}
