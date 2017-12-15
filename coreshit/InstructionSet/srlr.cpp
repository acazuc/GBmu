
#include <jackshit.h>

byte core::srla( void )
{
	if ( regs.b.a & 1 )
		regs.b.f = CYFLAG;
	else
		regs.b.f = 0;

	regs.b.a >>= 1;

	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 2;
}

byte core::srlb( void )
{
	if ( regs.b.b & 1 )
		regs.b.f = CYFLAG;
	else
		regs.b.f = 0;

	regs.b.b >>= 1;

	ZUPDATE( regs.b.b );

	regs.w.pc++;
	return 2;
}

byte core::srlc( void )
{
	if ( regs.b.c & 1 )
		regs.b.f = CYFLAG;
	else
		regs.b.f = 0;

	regs.b.c >>= 1;

	ZUPDATE( regs.b.c );

	regs.w.pc++;
	return 2;
}

byte core::srld( void )
{
	if ( regs.b.d & 1 )
		regs.b.f = CYFLAG;
	else
		regs.b.f = 0;

	regs.b.d >>= 1;

	ZUPDATE( regs.b.d );

	regs.w.pc++;
	return 2;
}

byte core::srle( void )
{
	if ( regs.b.e & 1 )
		regs.b.f = CYFLAG;
	else
		regs.b.f = 0;

	regs.b.e >>= 1;

	ZUPDATE( regs.b.e );

	regs.w.pc++;
	return 2;
}

byte core::srlh( void )
{
	if ( regs.b.h & 1 )
		regs.b.f = CYFLAG;
	else
		regs.b.f = 0;

	regs.b.h >>= 1;

	ZUPDATE( regs.b.h );

	regs.w.pc++;
	return 2;
}

byte core::srll( void )
{
	if ( regs.b.l & 1 )
		regs.b.f = CYFLAG;
	else
		regs.b.f = 0;

	regs.b.l >>= 1;

	ZUPDATE( regs.b.l );

	regs.w.pc++;
	return 2;
}
