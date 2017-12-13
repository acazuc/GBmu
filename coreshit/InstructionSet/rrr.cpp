
#include <jackshit.h>

byte core::rrra( void )
{
	byte cy;

	if ( regs.b.a & 1 )
		cy = CYFLAG;
	else
		cy = 0;

	if ( regs.b.f & CYFLAG )
		regs.b.a = ( regs.b.a >> 1 ) + 128;
	else
		regs.b.a >>= 1;

	regs.b.f = cy;
	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 2;
}

byte core::rrrb( void )
{
	byte cy;

	if ( regs.b.b & 1 )
		cy = CYFLAG;
	else
		cy = 0;

	if ( regs.b.f & CYFLAG )
		regs.b.b = ( regs.b.b >> 1 ) + 128;
	else
		regs.b.b >>= 1;

	regs.b.f = cy;
	ZUPDATE( regs.b.b );

	regs.w.pc++;
	return 2;
}

byte core::rrrc( void )
{
	byte cy;

	if ( regs.b.c & 1 )
		cy = CYFLAG;
	else
		cy = 0;

	if ( regs.b.f & CYFLAG )
		regs.b.c = ( regs.b.c >> 1 ) + 128;
	else
		regs.b.c >>= 1;

	regs.b.f = cy;
	ZUPDATE( regs.b.c );

	regs.w.pc++;
	return 2;
}

byte core::rrrd( void )
{
	byte cy;

	if ( regs.b.d & 1 )
		cy = CYFLAG;
	else
		cy = 0;

	if ( regs.b.f & CYFLAG )
		regs.b.d = ( regs.b.d >> 1 ) + 128;
	else
		regs.b.d >>= 1;

	regs.b.f = cy;
	ZUPDATE( regs.b.d );

	regs.w.pc++;
	return 2;
}

byte core::rrre( void )
{
	byte cy;

	if ( regs.b.e & 1 )
		cy = CYFLAG;
	else
		cy = 0;

	if ( regs.b.f & CYFLAG )
		regs.b.e = ( regs.b.e >> 1 ) + 128;
	else
		regs.b.e >>= 1;

	regs.b.f = cy;
	ZUPDATE( regs.b.e );

	regs.w.pc++;
	return 2;
}

byte core::rrrh( void )
{
	byte cy;

	if ( regs.b.h & 1 )
		cy = CYFLAG;
	else
		cy = 0;

	if ( regs.b.f & CYFLAG )
		regs.b.h = ( regs.b.h >> 1 ) + 128;
	else
		regs.b.h >>= 1;

	regs.b.f = cy;
	ZUPDATE( regs.b.h );

	regs.w.pc++;
	return 2;
}

byte core::rrrl( void )
{
	byte cy;

	if ( regs.b.l & 1 )
		cy = CYFLAG;
	else
		cy = 0;

	if ( regs.b.f & CYFLAG )
		regs.b.l = ( regs.b.l >> 1 ) + 128;
	else
		regs.b.l >>= 1;

	regs.b.f = cy;
	ZUPDATE( regs.b.l );

	regs.w.pc++;
	return 2;
}
