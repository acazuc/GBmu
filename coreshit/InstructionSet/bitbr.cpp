
#include <jackshit.h>

byte core::bit0a( void )
{
	regs.b.f &= ~NFLAG;
	regs.b.f |= HFLAG;

	ZUPDATE( ( regs.b.a & ( 1 << 0 ) ) );
	regs.w.pc++;
	return 2;
}

byte core::bit0b( void )
{
	regs.b.f &= ~NFLAG;
	regs.b.f |= HFLAG;

	ZUPDATE( ( regs.b.b & ( 1 << 0 ) ) );
	regs.w.pc++;
	return 2;
}

byte core::bit0c( void )
{
	regs.b.f &= ~NFLAG;
	regs.b.f |= HFLAG;

	ZUPDATE( ( regs.b.c & ( 1 << 0 ) ) );
	regs.w.pc++;
	return 2;
}

byte core::bit0d( void )
{
	regs.b.f &= ~NFLAG;
	regs.b.f |= HFLAG;

	ZUPDATE( ( regs.b.d & ( 1 << 0 ) ) );
	regs.w.pc++;
	return 2;
}

byte core::bit0e( void )
{
	regs.b.f &= ~NFLAG;
	regs.b.f |= HFLAG;

	ZUPDATE( ( regs.b.e & ( 1 << 0 ) ) );
	regs.w.pc++;
	return 2;
}

byte core::bit0h( void )
{
	regs.b.f &= ~NFLAG;
	regs.b.f |= HFLAG;

	ZUPDATE( ( regs.b.h & ( 1 << 0 ) ) );
	regs.w.pc++;
	return 2;
}

byte core::bit0l( void )
{
	regs.b.f &= ~NFLAG;
	regs.b.f |= HFLAG;

	ZUPDATE( ( regs.b.l & ( 1 << 0 ) ) );
	regs.w.pc++;
	return 2;
}

byte core::bit1a( void )
{
	regs.b.f &= ~NFLAG;
	regs.b.f |= HFLAG;

	ZUPDATE( ( regs.b.a & ( 1 << 1 ) ) );
	regs.w.pc++;
	return 2;
}

byte core::bit1b( void )
{
	regs.b.f &= ~NFLAG;
	regs.b.f |= HFLAG;

	ZUPDATE( ( regs.b.b & ( 1 << 1 ) ) );
	regs.w.pc++;
	return 2;
}

byte core::bit1c( void )
{
	regs.b.f &= ~NFLAG;
	regs.b.f |= HFLAG;

	ZUPDATE( ( regs.b.c & ( 1 << 1 ) ) );
	regs.w.pc++;
	return 2;
}

byte core::bit1d( void )
{
	regs.b.f &= ~NFLAG;
	regs.b.f |= HFLAG;

	ZUPDATE( ( regs.b.d & ( 1 << 1 ) ) );
	regs.w.pc++;
	return 2;
}

byte core::bit1e( void )
{
	regs.b.f &= ~NFLAG;
	regs.b.f |= HFLAG;

	ZUPDATE( ( regs.b.e & ( 1 << 1 ) ) );
	regs.w.pc++;
	return 2;
}

byte core::bit1h( void )
{
	regs.b.f &= ~NFLAG;
	regs.b.f |= HFLAG;

	ZUPDATE( ( regs.b.h & ( 1 << 1 ) ) );
	regs.w.pc++;
	return 2;
}

byte core::bit1l( void )
{
	regs.b.f &= ~NFLAG;
	regs.b.f |= HFLAG;

	ZUPDATE( ( regs.b.l & ( 1 << 1 ) ) );
	regs.w.pc++;
	return 2;
}

byte core::bit2a( void )
{
	regs.b.f &= ~NFLAG;
	regs.b.f |= HFLAG;

	ZUPDATE( ( regs.b.a & ( 1 << 2 ) ) );
	regs.w.pc++;
	return 2;
}

byte core::bit2b( void )
{
	regs.b.f &= ~NFLAG;
	regs.b.f |= HFLAG;

	ZUPDATE( ( regs.b.b & ( 1 << 2 ) ) );
	regs.w.pc++;
	return 2;
}

byte core::bit2c( void )
{
	regs.b.f &= ~NFLAG;
	regs.b.f |= HFLAG;

	ZUPDATE( ( regs.b.c & ( 1 << 2 ) ) );
	regs.w.pc++;
	return 2;
}

byte core::bit2d( void )
{
	regs.b.f &= ~NFLAG;
	regs.b.f |= HFLAG;

	ZUPDATE( ( regs.b.d & ( 1 << 2 ) ) );
	regs.w.pc++;
	return 2;
}

byte core::bit2e( void )
{
	regs.b.f &= ~NFLAG;
	regs.b.f |= HFLAG;

	ZUPDATE( ( regs.b.e & ( 1 << 2 ) ) );
	regs.w.pc++;
	return 2;
}

byte core::bit2h( void )
{
	regs.b.f &= ~NFLAG;
	regs.b.f |= HFLAG;

	ZUPDATE( ( regs.b.h & ( 1 << 2 ) ) );
	regs.w.pc++;
	return 2;
}

byte core::bit2l( void )
{
	regs.b.f &= ~NFLAG;
	regs.b.f |= HFLAG;

	ZUPDATE( ( regs.b.l & ( 1 << 2 ) ) );
	regs.w.pc++;
	return 2;
}

byte core::bit3a( void )
{
	regs.b.f &= ~NFLAG;
	regs.b.f |= HFLAG;

	ZUPDATE( ( regs.b.a & ( 1 << 3 ) ) );
	regs.w.pc++;
	return 2;
}

byte core::bit3b( void )
{
	regs.b.f &= ~NFLAG;
	regs.b.f |= HFLAG;

	ZUPDATE( ( regs.b.b & ( 1 << 3 ) ) );
	regs.w.pc++;
	return 2;
}

byte core::bit3c( void )
{
	regs.b.f &= ~NFLAG;
	regs.b.f |= HFLAG;

	ZUPDATE( ( regs.b.c & ( 1 << 3 ) ) );
	regs.w.pc++;
	return 2;
}

byte core::bit3d( void )
{
	regs.b.f &= ~NFLAG;
	regs.b.f |= HFLAG;

	ZUPDATE( ( regs.b.d & ( 1 << 3 ) ) );
	regs.w.pc++;
	return 2;
}

byte core::bit3e( void )
{
	regs.b.f &= ~NFLAG;
	regs.b.f |= HFLAG;

	ZUPDATE( ( regs.b.e & ( 1 << 3 ) ) );
	regs.w.pc++;
	return 2;
}

byte core::bit3h( void )
{
	regs.b.f &= ~NFLAG;
	regs.b.f |= HFLAG;

	ZUPDATE( ( regs.b.h & ( 1 << 3 ) ) );
	regs.w.pc++;
	return 2;
}

byte core::bit3l( void )
{
	regs.b.f &= ~NFLAG;
	regs.b.f |= HFLAG;

	ZUPDATE( ( regs.b.l & ( 1 << 3 ) ) );
	regs.w.pc++;
	return 2;
}

byte core::bit4a( void )
{
	regs.b.f &= ~NFLAG;
	regs.b.f |= HFLAG;

	ZUPDATE( ( regs.b.a & ( 1 << 4 ) ) );
	regs.w.pc++;
	return 2;
}

byte core::bit4b( void )
{
	regs.b.f &= ~NFLAG;
	regs.b.f |= HFLAG;

	ZUPDATE( ( regs.b.b & ( 1 << 4 ) ) );
	regs.w.pc++;
	return 2;
}

byte core::bit4c( void )
{
	regs.b.f &= ~NFLAG;
	regs.b.f |= HFLAG;

	ZUPDATE( ( regs.b.c & ( 1 << 4 ) ) );
	regs.w.pc++;
	return 2;
}

byte core::bit4d( void )
{
	regs.b.f &= ~NFLAG;
	regs.b.f |= HFLAG;

	ZUPDATE( ( regs.b.d & ( 1 << 4 ) ) );
	regs.w.pc++;
	return 2;
}

byte core::bit4e( void )
{
	regs.b.f &= ~NFLAG;
	regs.b.f |= HFLAG;

	ZUPDATE( ( regs.b.e & ( 1 << 4 ) ) );
	regs.w.pc++;
	return 2;
}

byte core::bit4h( void )
{
	regs.b.f &= ~NFLAG;
	regs.b.f |= HFLAG;

	ZUPDATE( ( regs.b.h & ( 1 << 4 ) ) );
	regs.w.pc++;
	return 2;
}

byte core::bit4l( void )
{
	regs.b.f &= ~NFLAG;
	regs.b.f |= HFLAG;

	ZUPDATE( ( regs.b.l & ( 1 << 4 ) ) );
	regs.w.pc++;
	return 2;
}

byte core::bit5a( void )
{
	regs.b.f &= ~NFLAG;
	regs.b.f |= HFLAG;

	ZUPDATE( ( regs.b.a & ( 1 << 5 ) ) );
	regs.w.pc++;
	return 2;
}

byte core::bit5b( void )
{
	regs.b.f &= ~NFLAG;
	regs.b.f |= HFLAG;

	ZUPDATE( ( regs.b.b & ( 1 << 5 ) ) );
	regs.w.pc++;
	return 2;
}

byte core::bit5c( void )
{
	regs.b.f &= ~NFLAG;
	regs.b.f |= HFLAG;

	ZUPDATE( ( regs.b.c & ( 1 << 5 ) ) );
	regs.w.pc++;
	return 2;
}

byte core::bit5d( void )
{
	regs.b.f &= ~NFLAG;
	regs.b.f |= HFLAG;

	ZUPDATE( ( regs.b.d & ( 1 << 5 ) ) );
	regs.w.pc++;
	return 2;
}

byte core::bit5e( void )
{
	regs.b.f &= ~NFLAG;
	regs.b.f |= HFLAG;

	ZUPDATE( ( regs.b.e & ( 1 << 5 ) ) );
	regs.w.pc++;
	return 2;
}

byte core::bit5h( void )
{
	regs.b.f &= ~NFLAG;
	regs.b.f |= HFLAG;

	ZUPDATE( ( regs.b.h & ( 1 << 5 ) ) );
	regs.w.pc++;
	return 2;
}

byte core::bit5l( void )
{
	regs.b.f &= ~NFLAG;
	regs.b.f |= HFLAG;

	ZUPDATE( ( regs.b.l & ( 1 << 5 ) ) );
	regs.w.pc++;
	return 2;
}

byte core::bit6a( void )
{
	regs.b.f &= ~NFLAG;
	regs.b.f |= HFLAG;

	ZUPDATE( ( regs.b.a & ( 1 << 6 ) ) );
	regs.w.pc++;
	return 2;
}

byte core::bit6b( void )
{
	regs.b.f &= ~NFLAG;
	regs.b.f |= HFLAG;

	ZUPDATE( ( regs.b.b & ( 1 << 6 ) ) );
	regs.w.pc++;
	return 2;
}

byte core::bit6c( void )
{
	regs.b.f &= ~NFLAG;
	regs.b.f |= HFLAG;

	ZUPDATE( ( regs.b.c & ( 1 << 6 ) ) );
	regs.w.pc++;
	return 2;
}

byte core::bit6d( void )
{
	regs.b.f &= ~NFLAG;
	regs.b.f |= HFLAG;

	ZUPDATE( ( regs.b.d & ( 1 << 6 ) ) );
	regs.w.pc++;
	return 2;
}

byte core::bit6e( void )
{
	regs.b.f &= ~NFLAG;
	regs.b.f |= HFLAG;

	ZUPDATE( ( regs.b.e & ( 1 << 6 ) ) );
	regs.w.pc++;
	return 2;
}

byte core::bit6h( void )
{
	regs.b.f &= ~NFLAG;
	regs.b.f |= HFLAG;

	ZUPDATE( ( regs.b.h & ( 1 << 6 ) ) );
	regs.w.pc++;
	return 2;
}

byte core::bit6l( void )
{
	regs.b.f &= ~NFLAG;
	regs.b.f |= HFLAG;

	ZUPDATE( ( regs.b.l & ( 1 << 6 ) ) );
	regs.w.pc++;
	return 2;
}

byte core::bit7a( void )
{
	regs.b.f &= ~NFLAG;
	regs.b.f |= HFLAG;

	ZUPDATE( ( regs.b.a & ( 1 << 7 ) ) );
	regs.w.pc++;
	return 2;
}

byte core::bit7b( void )
{
	regs.b.f &= ~NFLAG;
	regs.b.f |= HFLAG;

	ZUPDATE( ( regs.b.b & ( 1 << 7 ) ) );
	regs.w.pc++;
	return 2;
}

byte core::bit7c( void )
{
	regs.b.f &= ~NFLAG;
	regs.b.f |= HFLAG;

	ZUPDATE( ( regs.b.c & ( 1 << 7 ) ) );
	regs.w.pc++;
	return 2;
}

byte core::bit7d( void )
{
	regs.b.f &= ~NFLAG;
	regs.b.f |= HFLAG;

	ZUPDATE( ( regs.b.d & ( 1 << 7 ) ) );
	regs.w.pc++;
	return 2;
}

byte core::bit7e( void )
{
	regs.b.f &= ~NFLAG;
	regs.b.f |= HFLAG;

	ZUPDATE( ( regs.b.e & ( 1 << 7 ) ) );
	regs.w.pc++;
	return 2;
}

byte core::bit7h( void )
{
	regs.b.f &= ~NFLAG;
	regs.b.f |= HFLAG;

	ZUPDATE( ( regs.b.h & ( 1 << 7 ) ) );
	regs.w.pc++;
	return 2;
}

byte core::bit7l( void )
{
	regs.b.f &= ~NFLAG;
	regs.b.f |= HFLAG;

	ZUPDATE( ( regs.b.l & ( 1 << 7 ) ) );
	regs.w.pc++;
	return 2;
}
