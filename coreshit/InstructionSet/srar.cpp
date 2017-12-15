
#include <jackshit.h>

byte core::sraa( void )
{
	if ( regs.b.a & 1 )
		regs.b.f = CYFLAG;
	else
		regs.b.f = 0;

	regs.b.a >>= 1;
	if ( regs.b.a & 64 )
		regs.b.a |= 128;

	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 2;
}

byte core::srab( void )
{
	if ( regs.b.b & 1 )
		regs.b.f = CYFLAG;
	else
		regs.b.f = 0;

	regs.b.b >>= 1;
	if ( regs.b.b & 64 )
		regs.b.b |= 128;

	ZUPDATE( regs.b.b );

	regs.w.pc++;
	return 2;
}

byte core::srac( void )
{
	if ( regs.b.c & 1 )
		regs.b.f = CYFLAG;
	else
		regs.b.f = 0;

	regs.b.c >>= 1;
	if ( regs.b.c & 64 )
		regs.b.c |= 128;

	ZUPDATE( regs.b.c );

	regs.w.pc++;
	return 2;
}

byte core::srad( void )
{
	if ( regs.b.d & 1 )
		regs.b.f = CYFLAG;
	else
		regs.b.f = 0;

	regs.b.d >>= 1;
	if ( regs.b.d & 64 )
		regs.b.d |= 128;

	ZUPDATE( regs.b.d );

	regs.w.pc++;
	return 2;
}

byte core::srae( void )
{
	if ( regs.b.e & 1 )
		regs.b.f = CYFLAG;
	else
		regs.b.f = 0;

	regs.b.e >>= 1;
	if ( regs.b.e & 64 )
		regs.b.e |= 128;

	ZUPDATE( regs.b.e );

	regs.w.pc++;
	return 2;
}

byte core::srah( void )
{
	if ( regs.b.h & 1 )
		regs.b.f = CYFLAG;
	else
		regs.b.f = 0;

	regs.b.h >>= 1;
	if ( regs.b.h & 64 )
		regs.b.h |= 128;

	ZUPDATE( regs.b.h );

	regs.w.pc++;
	return 2;
}

byte core::sral( void )
{
	if ( regs.b.l & 1 )
		regs.b.f = CYFLAG;
	else
		regs.b.f = 0;

	regs.b.l >>= 1;
	if ( regs.b.l & 64 )
		regs.b.l |= 128;

	ZUPDATE( regs.b.l );

	regs.w.pc++;
	return 2;
}
