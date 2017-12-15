
#include <jackshit.h>

byte core::slaa( void )
{
	if ( regs.b.a & 128 )
		regs.b.f = CYFLAG;
	else
		regs.b.f = 0;

	regs.b.a <<= 1;

	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 2;
}

byte core::slab( void )
{
	if ( regs.b.b & 128 )
		regs.b.f = CYFLAG;
	else
		regs.b.f = 0;

	regs.b.b <<= 1;

	ZUPDATE( regs.b.b );

	regs.w.pc++;
	return 2;
}

byte core::slac( void )
{
	if ( regs.b.c & 128 )
		regs.b.f = CYFLAG;
	else
		regs.b.f = 0;

	regs.b.c <<= 1;

	ZUPDATE( regs.b.c );

	regs.w.pc++;
	return 2;
}

byte core::slad( void )
{
	if ( regs.b.d & 128 )
		regs.b.f = CYFLAG;
	else
		regs.b.f = 0;

	regs.b.d <<= 1;

	ZUPDATE( regs.b.d );

	regs.w.pc++;
	return 2;
}

byte core::slae( void )
{
	if ( regs.b.e & 128 )
		regs.b.f = CYFLAG;
	else
		regs.b.f = 0;

	regs.b.e <<= 1;

	ZUPDATE( regs.b.e );

	regs.w.pc++;
	return 2;
}

byte core::slah( void )
{
	if ( regs.b.h & 128 )
		regs.b.f = CYFLAG;
	else
		regs.b.f = 0;

	regs.b.h <<= 1;

	ZUPDATE( regs.b.h );

	regs.w.pc++;
	return 2;
}

byte core::slal( void )
{
	if ( regs.b.l & 128 )
		regs.b.f = CYFLAG;
	else
		regs.b.f = 0;

	regs.b.l <<= 1;

	ZUPDATE( regs.b.l );

	regs.w.pc++;
	return 2;
}
