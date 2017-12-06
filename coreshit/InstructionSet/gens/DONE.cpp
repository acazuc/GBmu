
#include <jackshit.h>

byte core::cpa( void )
{
	byte a;

	a = regs.b.a - regs.b.a;

	regs.b.f = 1;
	CARRYNEGUPDATE( regs.b.a, a );
	ZUPDATE( a );

	regs.w.pc++;
	return 1;	
}

byte core::cpb( void )
{
	byte a;

	a = regs.b.a - regs.b.b;

	regs.b.f = 1;
	CARRYNEGUPDATE( regs.b.a, a );
	ZUPDATE( a );

	regs.w.pc++;
	return 1;	
}

byte core::cpc( void )
{
	byte a;

	a = regs.b.a - regs.b.c;

	regs.b.f = 1;
	CARRYNEGUPDATE( regs.b.a, a );
	ZUPDATE( a );

	regs.w.pc++;
	return 1;	
}

byte core::cpd( void )
{
	byte a;

	a = regs.b.a - regs.b.d;

	regs.b.f = 1;
	CARRYNEGUPDATE( regs.b.a, a );
	ZUPDATE( a );

	regs.w.pc++;
	return 1;	
}

byte core::cpe( void )
{
	byte a;

	a = regs.b.a - regs.b.e;

	regs.b.f = 1;
	CARRYNEGUPDATE( regs.b.a, a );
	ZUPDATE( a );

	regs.w.pc++;
	return 1;	
}

byte core::cph( void )
{
	byte a;

	a = regs.b.a - regs.b.h;

	regs.b.f = 1;
	CARRYNEGUPDATE( regs.b.a, a );
	ZUPDATE( a );

	regs.w.pc++;
	return 1;	
}

byte core::cpl( void )
{
	byte a;

	a = regs.b.a - regs.b.l;

	regs.b.f = 1;
	CARRYNEGUPDATE( regs.b.a, a );
	ZUPDATE( a );

	regs.w.pc++;
	return 1;	
}


{
	"cp b",
	1,
	&cpb,
},
{
	"cp c",
	1,
	&cpc,
},
{
	"cp d",
	1,
	&cpd,
},
{
	"cp e",
	1,
	&cpe,
},
{
	"cp h",
	1,
	&cph,
},
{
	"cp l",
	1,
	&cpl,
},
{
	"cp (hl)",
	1,
	&cp(hl),
},
{
	"cp a",
	1,
	&cpa,
},
