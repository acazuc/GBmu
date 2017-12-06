
#include <jackshit.h>

byte core::xora( void )
{
	regs.b.a ^= regs.b.a;

	regs.b.f = 0;
	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 1;
}

byte core::xorb( void )
{
	regs.b.a ^= regs.b.b;

	regs.b.f = 0;
	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 1;
}

byte core::xorc( void )
{
	regs.b.a ^= regs.b.c;

	regs.b.f = 0;
	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 1;
}

byte core::xord( void )
{
	regs.b.a ^= regs.b.d;

	regs.b.f = 0;
	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 1;
}

byte core::xore( void )
{
	regs.b.a ^= regs.b.e;

	regs.b.f = 0;
	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 1;
}

byte core::xorh( void )
{
	regs.b.a ^= regs.b.h;

	regs.b.f = 0;
	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 1;
}

byte core::xorl( void )
{
	regs.b.a ^= regs.b.l;

	regs.b.f = 0;
	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 1;
}
