
#include <jackshit.h>

byte core::addaa( void )
{
	byte a;

	a = regs.b.a;
	regs.b.a += regs.b.a;

	regs.b.f = 0;
	CARRYUPDATE( a, regs.b.a );
	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 1;	
}

byte core::addab( void )
{
	byte a;

	a = regs.b.a;
	regs.b.a += regs.b.b;

	regs.b.f = 0;
	CARRYUPDATE( a, regs.b.a );
	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 1;	
}

byte core::addac( void )
{
	byte a;

	a = regs.b.a;
	regs.b.a += regs.b.c;

	regs.b.f = 0;
	CARRYUPDATE( a, regs.b.a );
	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 1;	
}

byte core::addad( void )
{
	byte a;

	a = regs.b.a;
	regs.b.a += regs.b.d;

	regs.b.f = 0;
	CARRYUPDATE( a, regs.b.a );
	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 1;	
}

byte core::addae( void )
{
	byte a;

	a = regs.b.a;
	regs.b.a += regs.b.e;

	regs.b.f = 0;
	CARRYUPDATE( a, regs.b.a );
	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 1;	
}

byte core::addah( void )
{
	byte a;

	a = regs.b.a;
	regs.b.a += regs.b.h;

	regs.b.f = 0;
	CARRYUPDATE( a, regs.b.a );
	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 1;	
}

byte core::addal( void )
{
	byte a;

	a = regs.b.a;
	regs.b.a += regs.b.l;

	regs.b.f = 0;
	CARRYUPDATE( a, regs.b.a );
	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 1;	
}

