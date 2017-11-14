
#include <jackshit.h>

void core::ldhla( void )
{
	mem[regs.w.hl] = regs.b.a;
	regs.w.pc++;
}

void core::ldhlb( void )
{
	mem[regs.w.hl] = regs.b.b;
	regs.w.pc++;
}

void core::ldhlc( void )
{
	mem[regs.w.hl] = regs.b.c;
	regs.w.pc++;
}

void core::ldhld( void )
{
	mem[regs.w.hl] = regs.b.d;
	regs.w.pc++;
}

void core::ldhle( void )
{
	mem[regs.w.hl] = regs.b.e;
	regs.w.pc++;
}

void core::ldhlh( void )
{
	mem[regs.w.hl] = regs.b.h;
	regs.w.pc++;
}

void core::ldhll( void )
{
	mem[regs.w.hl] = regs.b.l;
	regs.w.pc++;
}
