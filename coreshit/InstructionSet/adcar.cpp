
#include <jackshit.h>

byte core::adcaa( void )
{
	byte a;

	a = regs.b.a;
	regs.b.a += regs.b.a;
	if ( regs.b.f & CYFLAG )
	{
		regs.b.a++;
		regs.b.f = 0;
		CARRYUPDATEWITHCARRY( a, regs.b.a );
	}
	else
	{
		regs.b.f = 0;
		CARRYUPDATE( a, regs.b.a );
	}

	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 1;	
}

byte core::adcab( void )
{
	byte a;

	a = regs.b.a;
	regs.b.a += regs.b.b;
	if ( regs.b.f & CYFLAG )
	{
		regs.b.a++;
		regs.b.f = 0;
		CARRYUPDATEWITHCARRY( a, regs.b.a );
	}
	else
	{
		regs.b.f = 0;
		CARRYUPDATE( a, regs.b.a );
	}

	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 1;	
}

byte core::adcac( void )
{
	byte a;

	a = regs.b.a;
	regs.b.a += regs.b.c;
	if ( regs.b.f & CYFLAG )
	{
		regs.b.a++;
		regs.b.f = 0;
		CARRYUPDATEWITHCARRY( a, regs.b.a );
	}
	else
	{
		regs.b.f = 0;
		CARRYUPDATE( a, regs.b.a );
	}

	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 1;	
}

byte core::adcad( void )
{
	byte a;

	a = regs.b.a;
	regs.b.a += regs.b.d;
	if ( regs.b.f & CYFLAG )
	{
		regs.b.a++;
		regs.b.f = 0;
		CARRYUPDATEWITHCARRY( a, regs.b.a );
	}
	else
	{
		regs.b.f = 0;
		CARRYUPDATE( a, regs.b.a );
	}

	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 1;	
}

byte core::adcae( void )
{
	byte a;

	a = regs.b.a;
	regs.b.a += regs.b.e;
	if ( regs.b.f & CYFLAG )
	{
		regs.b.a++;
		regs.b.f = 0;
		CARRYUPDATEWITHCARRY( a, regs.b.a );
	}
	else
	{
		regs.b.f = 0;
		CARRYUPDATE( a, regs.b.a );
	}

	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 1;	
}

byte core::adcah( void )
{
	byte a;

	a = regs.b.a;
	regs.b.a += regs.b.h;
	if ( regs.b.f & CYFLAG )
	{
		regs.b.a++;
		regs.b.f = 0;
		CARRYUPDATEWITHCARRY( a, regs.b.a );
	}
	else
	{
		regs.b.f = 0;
		CARRYUPDATE( a, regs.b.a );
	}

	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 1;	
}

byte core::adcal( void )
{
	byte a;

	a = regs.b.a;
	regs.b.a += regs.b.l;
	if ( regs.b.f & CYFLAG )
	{
		regs.b.a++;
		regs.b.f = 0;
		CARRYUPDATEWITHCARRY( a, regs.b.a );
	}
	else
	{
		regs.b.f = 0;
		CARRYUPDATE( a, regs.b.a );
	}

	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 1;	
}
