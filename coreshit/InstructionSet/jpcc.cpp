
#include <jackshit.h>

void core::jpnz( void )
{
	if ( !( regs.b.f & ZFLAG ) )
		regs.w.pc = mem[regs.w.pc + 1];
	else
		regs.w.pc++;
}

void core::jpz( void )
{
	if ( regs.b.f & ZFLAG )
		regs.w.pc = mem[regs.w.pc + 1];
	else
		regs.w.pc++;
}

void core::jpnc( void )
{
	if ( !( regs.b.f & CYFLAG ) )
		regs.w.pc = mem[regs.w.pc + 1];
	else
		regs.w.pc++;
}

void core::jpc( void )
{
	if ( regs.b.f & CYFLAG )
		regs.w.pc = mem[regs.w.pc + 1];
	else
		regs.w.pc++;
}
