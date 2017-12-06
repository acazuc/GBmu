
#include <jackshit.h>

byte core::jrnz( void )
{
	if ( !( regs.b.f & ZFLAG ) )
	{
		regs.w.pc += ( char ) mem[regs.w.pc + 1] + 2;
		return 3;
	}
	else
	{
		regs.w.pc += 2;
		return 2;
	}
}

byte core::jrz( void )
{
	if ( regs.b.f & ZFLAG )
	{
		regs.w.pc += ( char ) mem[regs.w.pc + 1] + 2;
		return 3;
	}
	else
	{
		regs.w.pc += 2;
		return 2;
	}
}

byte core::jrnc( void )
{
	if ( !( regs.b.f & CYFLAG ) )
	{
		regs.w.pc += ( char ) mem[regs.w.pc + 1] + 2;
		return 3;
	}
	else
	{
		regs.w.pc += 2;
		return 2;
	}
}

byte core::jrc( void )
{
	if ( regs.b.f & CYFLAG )
	{
		regs.w.pc += ( char ) mem[regs.w.pc + 1] + 2;
		return 3;
	}
	else
	{
		regs.w.pc += 2;
		return 2;
	}
}
