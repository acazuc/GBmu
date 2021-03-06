
#include <jackshit.h>

byte core::callnz( void )
{
	if ( !( regs.b.f & ZFLAG ) )
	{
		mem[regs.w.sp -= 2] = ( word ) ( regs.w.pc + 3 );
		regs.w.pc = mem[regs.w.pc + 1];
		return 6;
	}
	else
	{
		regs.w.pc += 3;
		return 3;
	}
}

byte core::callz( void )
{
	if ( regs.b.f & ZFLAG )
	{
		mem[regs.w.sp -= 2] = ( word ) ( regs.w.pc + 3 );
		regs.w.pc = mem[regs.w.pc + 1];
		return 6;
	}
	else
	{
		regs.w.pc += 3;
		return 3;
	}
}

byte core::callnc( void )
{
	if ( !( regs.b.f & CYFLAG ) )
	{
		mem[regs.w.sp -= 2] = ( word ) ( regs.w.pc + 3 );
		regs.w.pc = mem[regs.w.pc + 1];
		return 6;
	}
	else
	{
		regs.w.pc += 3;
		return 3;
	}
}

byte core::callc( void )
{
	if ( regs.b.f & CYFLAG )
	{
		mem[regs.w.sp -= 2] = ( word ) ( regs.w.pc + 3 );
		regs.w.pc = mem[regs.w.pc + 1];
		return 6;
	}
	else
	{
		regs.w.pc += 3;
		return 3;
	}
}
