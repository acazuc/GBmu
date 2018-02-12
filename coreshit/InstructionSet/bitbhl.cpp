
#include <jackshit.h>

byte core::bit0hl( void )
{
	regs.b.f &= ~NFLAG;
	regs.b.f |= HFLAG;

	ZUPDATE( ( mem[regs.w.hl] & ( 1 << 0 ) ) );
	regs.w.pc++;
	return 2;
}

byte core::bit1hl( void )
{
	regs.b.f &= ~NFLAG;
	regs.b.f |= HFLAG;

	ZUPDATE( ( mem[regs.w.hl] & ( 1 << 1 ) ) );
	regs.w.pc++;
	return 2;
}

byte core::bit2hl( void )
{
	regs.b.f &= ~NFLAG;
	regs.b.f |= HFLAG;

	ZUPDATE( ( mem[regs.w.hl] & ( 1 << 2 ) ) );
	regs.w.pc++;
	return 2;
}

byte core::bit3hl( void )
{
	regs.b.f &= ~NFLAG;
	regs.b.f |= HFLAG;

	ZUPDATE( ( mem[regs.w.hl] & ( 1 << 3 ) ) );
	regs.w.pc++;
	return 2;
}

byte core::bit4hl( void )
{
	regs.b.f &= ~NFLAG;
	regs.b.f |= HFLAG;

	ZUPDATE( ( mem[regs.w.hl] & ( 1 << 4 ) ) );
	regs.w.pc++;
	return 2;
}

byte core::bit5hl( void )
{
	regs.b.f &= ~NFLAG;
	regs.b.f |= HFLAG;

	ZUPDATE( ( mem[regs.w.hl] & ( 1 << 5 ) ) );
	regs.w.pc++;
	return 2;
}

byte core::bit6hl( void )
{
	regs.b.f &= ~NFLAG;
	regs.b.f |= HFLAG;

	ZUPDATE( ( mem[regs.w.hl] & ( 1 << 6 ) ) );
	regs.w.pc++;
	return 2;
}

byte core::bit7hl( void )
{
	regs.b.f &= ~NFLAG;
	regs.b.f |= HFLAG;

	ZUPDATE( ( mem[regs.w.hl] & ( 1 << 7 ) ) );
	regs.w.pc++;
	return 2;
}
