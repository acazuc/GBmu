
#include <jackshit.h>

byte core::ldahl( void )
{
	regs.b.a = mem[regs.w.hl];
	regs.w.pc++;
	return 2;
}

byte core::ldbhl( void )
{
	regs.b.b = mem[regs.w.hl];
	regs.w.pc++;
	return 2;
}

byte core::ldchl( void )
{
	regs.b.c = mem[regs.w.hl];
	regs.w.pc++;
	return 2;
}

byte core::lddhl( void )
{
	regs.b.d = mem[regs.w.hl];
	regs.w.pc++;
	return 2;
}

byte core::ldehl( void )
{
	regs.b.e = mem[regs.w.hl];
	regs.w.pc++;
	return 2;
}

byte core::ldhhl( void )
{
	regs.b.h = mem[regs.w.hl];
	regs.w.pc++;
	return 2;
}

byte core::ldlhl( void )
{
	regs.b.l = mem[regs.w.hl];
	regs.w.pc++;
	return 2;
}
