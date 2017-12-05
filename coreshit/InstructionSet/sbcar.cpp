
#include <jackshit.h>

byte core::sbcaa( void )
{
	byte a;

	a = regs.b.a;
	regs.b.a -= regs.b.a;
	if ( regs.b.f & CYFLAG )
		regs.b.f--;

	regs.b.f = 1;
	CARRYREVUPDATE( a, regs.b.a );
	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 1;	
}

byte core::sbcab( void )
{
	byte a;

	a = regs.b.a;
	regs.b.a -= regs.b.b;
	if ( regs.b.f & CYFLAG )
		regs.b.f--;

	regs.b.f = 1;
	CARRYREVUPDATE( a, regs.b.a );
	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 1;	
}

byte core::sbcac( void )
{
	byte a;

	a = regs.b.a;
	regs.b.a -= regs.b.c;
	if ( regs.b.f & CYFLAG )
		regs.b.f--;

	regs.b.f = 1;
	CARRYREVUPDATE( a, regs.b.a );
	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 1;	
}

byte core::sbcad( void )
{
	byte a;

	a = regs.b.a;
	regs.b.a -= regs.b.d;
	if ( regs.b.f & CYFLAG )
		regs.b.f--;

	regs.b.f = 1;
	CARRYREVUPDATE( a, regs.b.a );
	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 1;	
}

byte core::sbcae( void )
{
	byte a;

	a = regs.b.a;
	regs.b.a -= regs.b.e;
	if ( regs.b.f & CYFLAG )
		regs.b.f--;

	regs.b.f = 1;
	CARRYREVUPDATE( a, regs.b.a );
	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 1;	
}

byte core::sbcah( void )
{
	byte a;

	a = regs.b.a;
	regs.b.a -= regs.b.h;
	if ( regs.b.f & CYFLAG )
		regs.b.f--;

	regs.b.f = 1;
	CARRYREVUPDATE( a, regs.b.a );
	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 1;	
}

byte core::sbcal( void )
{
	byte a;

	a = regs.b.a;
	regs.b.a -= regs.b.l;
	if ( regs.b.f & CYFLAG )
		regs.b.f--;

	regs.b.f = 1;
	CARRYREVUPDATE( a, regs.b.a );
	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 1;	
}
