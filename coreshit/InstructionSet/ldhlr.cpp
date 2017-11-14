
#include <jackshit.h>

byte core::ldhla( void )
{
	mem[regs.w.hl] = regs.b.a;
	regs.w.pc++;
	return 2;
}

byte core::ldhlb( void )
{
	mem[regs.w.hl] = regs.b.b;
	regs.w.pc++;
	return 2;
}

byte core::ldhlc( void )
{
	mem[regs.w.hl] = regs.b.c;
	regs.w.pc++;
	return 2;
}

byte core::ldhld( void )
{
	mem[regs.w.hl] = regs.b.d;
	regs.w.pc++;
	return 2;
}

byte core::ldhle( void )
{
	mem[regs.w.hl] = regs.b.e;
	regs.w.pc++;
	return 2;
}

byte core::ldhlh( void )
{
	mem[regs.w.hl] = regs.b.h;
	regs.w.pc++;
	return 2;
}

byte core::ldhll( void )
{
	mem[regs.w.hl] = regs.b.l;
	regs.w.pc++;
	return 2;
}
