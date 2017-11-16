
#include <jackshit.h>

byte core::jpnz( void )
{
	if ( !( regs.b.f & ZFLAG ) )
	{
		regs.w.pc = mem[regs.w.pc + 1];
		return 4;
	}
	else
	{
		regs.w.pc++;
		return 3;
	}
}

byte core::jpz( void )
{
	if ( regs.b.f & ZFLAG )
	{
		regs.w.pc = mem[regs.w.pc + 1];
		return 4;
	}
	else
	{
		regs.w.pc++;
		return 3;
	}

}

byte core::jpnc( void )
{
	if ( !( regs.b.f & CYFLAG ) )
	{
		regs.w.pc = mem[regs.w.pc + 1];
		return 4;
	}
	else
	{
		regs.w.pc++;
		return 3;
	}

}

byte core::jpc( void )
{
	if ( regs.b.f & CYFLAG )
	{
		regs.w.pc = mem[regs.w.pc + 1];
		return 4;
	}
	else
	{
		regs.w.pc++;
		return 3;
	}

}
