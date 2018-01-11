
#include <jackshit.h>

byte core::swapa( void )
{
	regs.b.a = ( regs.b.a << 4 ) | ( regs.b.a >> 4 );

	regs.b.f = 0;
	ZUPDATE( regs.b.a );
	
	regs.w.pc++;
	return 2;
}

byte core::swapb( void )
{
	regs.b.b = ( regs.b.b << 4 ) | ( regs.b.b >> 4 );

	regs.b.f = 0;
	ZUPDATE( regs.b.b );
	
	regs.w.pc++;
	return 2;
}

byte core::swapc( void )
{
	regs.b.c = ( regs.b.c << 4 ) | ( regs.b.c >> 4 );

	regs.b.f = 0;
	ZUPDATE( regs.b.c );
	
	regs.w.pc++;
	return 2;
}

byte core::swapd( void )
{
	regs.b.d = ( regs.b.d << 4 ) | ( regs.b.d >> 4 );

	regs.b.f = 0;
	ZUPDATE( regs.b.d );
	
	regs.w.pc++;
	return 2;
}

byte core::swape( void )
{
	regs.b.e = ( regs.b.e << 4 ) | ( regs.b.e >> 4 );

	regs.b.f = 0;
	ZUPDATE( regs.b.e );
	
	regs.w.pc++;
	return 2;
}

byte core::swaph( void )
{
	regs.b.h = ( regs.b.h << 4 ) | ( regs.b.h >> 4 );

	regs.b.f = 0;
	ZUPDATE( regs.b.h );
	
	regs.w.pc++;
	return 2;
}

byte core::swapl( void )
{
	regs.b.l = ( regs.b.l << 4 ) | ( regs.b.l >> 4 );

	regs.b.f = 0;
	ZUPDATE( regs.b.l );
	
	regs.w.pc++;
	return 2;
}
