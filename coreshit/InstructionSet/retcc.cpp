
#include <jackshit.h>

byte core::retnz( void )
{
	if ( !( regs.b.f & ZFLAG ) )
	{
		regs.w.pc = mem[regs.w.sp];
		regs.w.sp += 2;
		return 5;
	}
	else
	{
		regs.w.pc++;
		return 2;
	}
}

byte core::retz( void )
{
	if ( regs.b.f & ZFLAG )
	{
		regs.w.pc = mem[regs.w.sp];
		regs.w.sp += 2;
		return 5;
	}
	else
	{
		regs.w.pc++;
		return 2;
	}
}

byte core::retnc( void )
{
	if ( !( regs.b.f & CYFLAG ) )
	{
		regs.w.pc = mem[regs.w.sp];
		regs.w.sp += 2;
		return 5;
	}
	else
	{
		regs.w.pc++;
		return 2;
	}
}

byte core::retc( void )
{
	if ( regs.b.f & CYFLAG )
	{
		regs.w.pc = mem[regs.w.sp];
		regs.w.sp += 2;
		return 5;
	}
	else
	{
		regs.w.pc++;
		return 2;
	}
}
