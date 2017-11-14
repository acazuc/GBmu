
#include <jackshit.h>

void core::ldahl( void )
{
	regs.b.a = mem[regs.w.hl];
	regs.w.pc++;
}

void core::ldbhl( void )
{
	regs.b.b = mem[regs.w.hl];
	regs.w.pc++;
}

void core::ldchl( void )
{
	regs.b.c = mem[regs.w.hl];
	regs.w.pc++;
}

void core::lddhl( void )
{
	regs.b.d = mem[regs.w.hl];
	regs.w.pc++;
}

void core::ldehl( void )
{
	regs.b.e = mem[regs.w.hl];
	regs.w.pc++;
}

void core::ldhhl( void )
{
	regs.b.h = mem[regs.w.hl];
	regs.w.pc++;
}

void core::ldlhl( void )
{
	regs.b.l = mem[regs.w.hl];
	regs.w.pc++;
}
