
#include <jackshit.h>

byte core::rlra( void )
{
	byte cy;

	if ( regs.b.a & 128 )
		cy = CYFLAG;
	else
		cy = 0;

	if ( regs.b.f & CYFLAG )
		regs.b.a = ( regs.b.a << 1 ) + 1;
	else
		regs.b.a <<= 1;

	regs.b.f = cy;
	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 2;
}

byte core::rlrb( void )
{
	byte cy;

	if ( regs.b.b & 128 )
		cy = CYFLAG;
	else
		cy = 0;

	if ( regs.b.f & CYFLAG )
		regs.b.b = ( regs.b.b << 1 ) + 1;
	else
		regs.b.b <<= 1;

	regs.b.f = cy;
	ZUPDATE( regs.b.b );

	regs.w.pc++;
	return 2;
}

byte core::rlrc( void )
{
	byte cy;

	if ( regs.b.c & 128 )
		cy = CYFLAG;
	else
		cy = 0;

	if ( regs.b.f & CYFLAG )
		regs.b.c = ( regs.b.c << 1 ) + 1;
	else
		regs.b.c <<= 1;

	regs.b.f = cy;
	ZUPDATE( regs.b.c );

	regs.w.pc++;
	return 2;
}

byte core::rlrd( void )
{
	byte cy;

	if ( regs.b.d & 128 )
		cy = CYFLAG;
	else
		cy = 0;

	if ( regs.b.f & CYFLAG )
		regs.b.d = ( regs.b.d << 1 ) + 1;
	else
		regs.b.d <<= 1;

	regs.b.f = cy;
	ZUPDATE( regs.b.d );

	regs.w.pc++;
	return 2;
}

byte core::rlre( void )
{
	byte cy;

	if ( regs.b.e & 128 )
		cy = CYFLAG;
	else
		cy = 0;

	if ( regs.b.f & CYFLAG )
		regs.b.e = ( regs.b.e << 1 ) + 1;
	else
		regs.b.e <<= 1;

	regs.b.f = cy;
	ZUPDATE( regs.b.e );

	regs.w.pc++;
	return 2;
}

byte core::rlrh( void )
{
	byte cy;

	if ( regs.b.h & 128 )
		cy = CYFLAG;
	else
		cy = 0;

	if ( regs.b.f & CYFLAG )
		regs.b.h = ( regs.b.h << 1 ) + 1;
	else
		regs.b.h <<= 1;

	regs.b.f = cy;
	ZUPDATE( regs.b.h );

	regs.w.pc++;
	return 2;
}

byte core::rlrl( void )
{
	byte cy;

	if ( regs.b.l & 128 )
		cy = CYFLAG;
	else
		cy = 0;

	if ( regs.b.f & CYFLAG )
		regs.b.l = ( regs.b.l << 1 ) + 1;
	else
		regs.b.l <<= 1;

	regs.b.f = cy;
	ZUPDATE( regs.b.l );

	regs.w.pc++;
	return 2;
}
