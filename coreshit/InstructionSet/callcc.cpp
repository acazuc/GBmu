
#include <jackshit.h>

byte core::callnz( void )
{
	if ( !( regs.b.f & ZFLAG ) )
	{
		mem[--regs.w.sp] = ( word ) regs.w.pc + 2;
		regs.w.pc = mem[regs.w.pc + 1];
		return 6;
	}
	else
	{
		regs.w.pc++;
		return 3;
	}
}

byte core::callz( void )
{
	if ( regs.b.f & ZFLAG )
	{
		mem[--regs.w.sp] = ( word ) regs.w.pc + 2;
		regs.w.pc = mem[regs.w.pc + 1];
		return 6;
	}
	else
	{
		regs.w.pc++;
		return 3;
	}
}

byte core::callnc( void )
{
	if ( !( regs.b.f & CYFLAG ) )
	{
		mem[--regs.w.sp] = ( word ) regs.w.pc + 2;
		regs.w.pc = mem[regs.w.pc + 1];
		return 6;
	}
	else
	{
		regs.w.pc++;
		return 3;
	}
}

byte core::callc( void )
{
	if ( regs.b.f & CYFLAG )
	{
		mem[--regs.w.sp] = ( word ) regs.w.pc + 2;
		regs.w.pc = mem[regs.w.pc + 1];
		return 6;
	}
	else
	{
		regs.w.pc++;
		return 3;
	}
}
