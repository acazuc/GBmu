
#include <jackshit.h>

byte core::cpa( void )
{
	byte a;

	a = regs.b.a - regs.b.a;

	regs.b.f = 1;
	CARRYREVUPDATE( regs.b.a, a );
	ZUPDATE( a );

	regs.w.pc++;
	return 1;	
}

byte core::cpb( void )
{
	byte a;

	a = regs.b.a - regs.b.b;

	regs.b.f = 1;
	CARRYREVUPDATE( regs.b.a, a );
	ZUPDATE( a );

	regs.w.pc++;
	return 1;	
}

byte core::cpc( void )
{
	byte a;

	a = regs.b.a - regs.b.c;

	regs.b.f = 1;
	CARRYREVUPDATE( regs.b.a, a );
	ZUPDATE( a );

	regs.w.pc++;
	return 1;	
}

byte core::cpd( void )
{
	byte a;

	a = regs.b.a - regs.b.d;

	regs.b.f = 1;
	CARRYREVUPDATE( regs.b.a, a );
	ZUPDATE( a );

	regs.w.pc++;
	return 1;	
}

byte core::cpe( void )
{
	byte a;

	a = regs.b.a - regs.b.e;

	regs.b.f = 1;
	CARRYREVUPDATE( regs.b.a, a );
	ZUPDATE( a );

	regs.w.pc++;
	return 1;	
}

byte core::cph( void )
{
	byte a;

	a = regs.b.a - regs.b.h;

	regs.b.f = 1;
	CARRYREVUPDATE( regs.b.a, a );
	ZUPDATE( a );

	regs.w.pc++;
	return 1;	
}

byte core::cpl( void )
{
	byte a;

	a = regs.b.a - regs.b.l;

	regs.b.f = 1;
	CARRYREVUPDATE( regs.b.a, a );
	ZUPDATE( a );

	regs.w.pc++;
	return 1;	
}
