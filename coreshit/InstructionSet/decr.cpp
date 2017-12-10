
#include <jackshit.h>

byte core::deca( void )
{
	byte a;

	a = regs.b.a--;

	regs.b.f |= NFLAG;
	HREVUPDATE( a, regs.b.a );
	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 1;
}

byte core::decb( void )
{
	byte b;

	b = regs.b.b--;

	regs.b.f |= NFLAG;
	HREVUPDATE( b, regs.b.b );
	ZUPDATE( regs.b.b );

	regs.w.pc++;
	return 1;
}

byte core::decc( void )
{
	byte c;

	c = regs.b.c--;

	regs.b.f |= NFLAG;
	HREVUPDATE( c, regs.b.c );
	ZUPDATE( regs.b.c );

	regs.w.pc++;
	return 1;
}

byte core::decd( void )
{
	byte d;

	d = regs.b.d--;

	regs.b.f |= NFLAG;
	HREVUPDATE( d, regs.b.d );
	ZUPDATE( regs.b.d );

	regs.w.pc++;
	return 1;
}

byte core::dece( void )
{
	byte e;

	e = regs.b.e--;

	regs.b.f |= NFLAG;
	HREVUPDATE( e, regs.b.e );
	ZUPDATE( regs.b.e );

	regs.w.pc++;
	return 1;
}

byte core::dech( void )
{
	byte h;

	h = regs.b.h--;

	regs.b.f |= NFLAG;
	HREVUPDATE( h, regs.b.h );
	ZUPDATE( regs.b.h );

	regs.w.pc++;
	return 1;
}

byte core::decl( void )
{
	byte l;

	l = regs.b.l--;

	regs.b.f |= NFLAG;
	HREVUPDATE( l, regs.b.l );
	ZUPDATE( regs.b.l );

	regs.w.pc++;
	return 1;
}


{
	"dec b",
	1,
	&decb,
},
{
	"dec c",
	1,
	&decc,
},
{
	"dec d",
	1,
	&decd,
},
{
	"dec e",
	1,
	&dece,
},
{
	"dec h",
	1,
	&dech,
},
{
	"dec l",
	1,
	&decl,
},
{
	"dec (hl)",
	1,
	&dec(hl),
},
{
	"dec a",
	1,
	&deca,
},
