
#include <jackshit.h>

byte core::ldan( void )
{
	regs.b.a = mem[regs.w.pc + 1];
	regs.w.pc += 2;
	return 2;
}

byte core::ldbn( void )
{
	regs.b.b = mem[regs.w.pc + 1];
	regs.w.pc += 2;
	return 2;
}

byte core::ldcn( void )
{
	regs.b.c = mem[regs.w.pc + 1];
	regs.w.pc += 2;
	return 2;
}

byte core::lddn( void )
{
	regs.b.d = mem[regs.w.pc + 1];
	regs.w.pc += 2;
	return 2;
}

byte core::lden( void )
{
	regs.b.e = mem[regs.w.pc + 1];
	regs.w.pc += 2;
	return 2;
}

byte core::ldhn( void )
{
	regs.b.h = mem[regs.w.pc + 1];
	regs.w.pc += 2;
	return 2;
}

byte core::ldln( void )
{
	regs.b.l = mem[regs.w.pc + 1];
	regs.w.pc += 2;
	return 2;
}
