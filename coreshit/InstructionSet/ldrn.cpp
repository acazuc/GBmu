
#include <jackshit.h>

void core::ldan( void )
{
	regs.b.a = mem[regs.w.pc + 1];
	regs.w.pc += 2;
}

void core::ldbn( void )
{
	regs.b.b = mem[regs.w.pc + 1];
	regs.w.pc += 2;
}

void core::ldcn( void )
{
	regs.b.c = mem[regs.w.pc + 1];
	regs.w.pc += 2;
}

void core::lddn( void )
{
	regs.b.d = mem[regs.w.pc + 1];
	regs.w.pc += 2;
}

void core::lden( void )
{
	regs.b.e = mem[regs.w.pc + 1];
	regs.w.pc += 2;
}

void core::ldhn( void )
{
	regs.b.h = mem[regs.w.pc + 1];
	regs.w.pc += 2;
}

void core::ldln( void )
{
	regs.b.l = mem[regs.w.pc + 1];
	regs.w.pc += 2;
}
