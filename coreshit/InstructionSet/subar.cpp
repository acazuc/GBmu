
#include <jackshit.h>

byte core::subaa( void )
{
	byte a;

	a = regs.b.a;
	regs.b.a -= regs.b.a;

	regs.b.f = NFLAG;
	CARRYREVUPDATE( a, regs.b.a );
	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 1;	
}

byte core::subab( void )
{
	byte a;

	a = regs.b.a;
	regs.b.a -= regs.b.b;

	regs.b.f = NFLAG;
	CARRYREVUPDATE( a, regs.b.a );
	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 1;	
}

byte core::subac( void )
{
	byte a;

	a = regs.b.a;
	regs.b.a -= regs.b.c;

	regs.b.f = NFLAG;
	CARRYREVUPDATE( a, regs.b.a );
	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 1;	
}

byte core::subad( void )
{
	byte a;

	a = regs.b.a;
	regs.b.a -= regs.b.d;

	regs.b.f = NFLAG;
	CARRYREVUPDATE( a, regs.b.a );
	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 1;	
}

byte core::subae( void )
{
	byte a;

	a = regs.b.a;
	regs.b.a -= regs.b.e;

	regs.b.f = NFLAG;
	CARRYREVUPDATE( a, regs.b.a );
	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 1;	
}

byte core::subah( void )
{
	byte a;

	a = regs.b.a;
	regs.b.a -= regs.b.h;

	regs.b.f = NFLAG;
	CARRYREVUPDATE( a, regs.b.a );
	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 1;	
}

byte core::subal( void )
{
	byte a;

	a = regs.b.a;
	regs.b.a -= regs.b.l;

	regs.b.f = NFLAG;
	CARRYREVUPDATE( a, regs.b.a );
	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 1;	
}
