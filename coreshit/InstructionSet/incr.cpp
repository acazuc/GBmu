
#include <jackshit.h>

byte core::inca( void )
{
	byte a;

	a = regs.b.a++;

	regs.b.f &= ~NFLAG;
	HUPDATE( a, regs.b.a );
	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 1;	
}

byte core::incb( void )
{
	byte b;

	b = regs.b.b++;

	regs.b.f &= ~NFLAG;
	HUPDATE( b, regs.b.b );
	ZUPDATE( regs.b.b );

	regs.w.pc++;
	return 1;	
}

byte core::incc( void )
{
	byte c;

	c = regs.b.c++;

	regs.b.f &= ~NFLAG;
	HUPDATE( c, regs.b.c );
	ZUPDATE( regs.b.c );

	regs.w.pc++;
	return 1;	
}

byte core::incd( void )
{
	byte d;

	d = regs.b.d++;

	regs.b.f &= ~NFLAG;
	HUPDATE( d, regs.b.d );
	ZUPDATE( regs.b.d );

	regs.w.pc++;
	return 1;	
}

byte core::ince( void )
{
	byte e;

	e = regs.b.e++;

	regs.b.f &= ~NFLAG;
	HUPDATE( e, regs.b.e );
	ZUPDATE( regs.b.e );

	regs.w.pc++;
	return 1;	
}

byte core::inch( void )
{
	byte h;

	h = regs.b.h++;

	regs.b.f &= ~NFLAG;
	HUPDATE( h, regs.b.h );
	ZUPDATE( regs.b.h );

	regs.w.pc++;
	return 1;	
}

byte core::incl( void )
{
	byte l;

	l = regs.b.l++;

	regs.b.f &= ~NFLAG;
	HUPDATE( l, regs.b.l );
	ZUPDATE( regs.b.l );

	regs.w.pc++;
	return 1;	
}
