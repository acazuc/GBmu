
#include <jackshit.h>

byte core::rlcra( void )
{
	if ( regs.b.a & 128 )
	{
		regs.b.a = ( regs.b.a << 1 ) + 1;
		regs.b.f = CYFLAG;
	}
	else
	{
		regs.b.a <<= 1;
		regs.b.f = 0;
	}

	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 2;
}

byte core::rlcrb( void )
{
	if ( regs.b.b & 128 )
	{
		regs.b.b = ( regs.b.b << 1 ) + 1;
		regs.b.f = CYFLAG;
	}
	else
	{
		regs.b.b <<= 1;
		regs.b.f = 0;
	}

	ZUPDATE( regs.b.b );

	regs.w.pc++;
	return 2;
}

byte core::rlcrc( void )
{
	if ( regs.b.c & 128 )
	{
		regs.b.c = ( regs.b.c << 1 ) + 1;
		regs.b.f = CYFLAG;
	}
	else
	{
		regs.b.c <<= 1;
		regs.b.f = 0;
	}

	ZUPDATE( regs.b.c );

	regs.w.pc++;
	return 2;
}

byte core::rlcrd( void )
{
	if ( regs.b.d & 128 )
	{
		regs.b.d = ( regs.b.d << 1 ) + 1;
		regs.b.f = CYFLAG;
	}
	else
	{
		regs.b.d <<= 1;
		regs.b.f = 0;
	}

	ZUPDATE( regs.b.d );

	regs.w.pc++;
	return 2;
}

byte core::rlcre( void )
{
	if ( regs.b.e & 128 )
	{
		regs.b.e = ( regs.b.e << 1 ) + 1;
		regs.b.f = CYFLAG;
	}
	else
	{
		regs.b.e <<= 1;
		regs.b.f = 0;
	}

	ZUPDATE( regs.b.e );

	regs.w.pc++;
	return 2;
}

byte core::rlcrh( void )
{
	if ( regs.b.h & 128 )
	{
		regs.b.h = ( regs.b.h << 1 ) + 1;
		regs.b.f = CYFLAG;
	}
	else
	{
		regs.b.h <<= 1;
		regs.b.f = 0;
	}

	ZUPDATE( regs.b.h );

	regs.w.pc++;
	return 2;
}

byte core::rlcrl( void )
{
	if ( regs.b.l & 128 )
	{
		regs.b.l = ( regs.b.l << 1 ) + 1;
		regs.b.f = CYFLAG;
	}
	else
	{
		regs.b.l <<= 1;
		regs.b.f = 0;
	}

	ZUPDATE( regs.b.l );

	regs.w.pc++;
	return 2;
}
