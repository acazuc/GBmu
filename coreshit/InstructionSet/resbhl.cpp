
#include <jackshit.h>

byte core::res0hl( void )
{
	mem[regs.w.hl] &= ~1;
	regs.w.pc++;
	return 4;
}

byte core::res1hl( void )
{
	mem[regs.w.hl] &= ~2;
	regs.w.pc++;
	return 4;
}

byte core::res2hl( void )
{
	mem[regs.w.hl] &= ~4;
	regs.w.pc++;
	return 4;
}

byte core::res3hl( void )
{
	mem[regs.w.hl] &= ~8;
	regs.w.pc++;
	return 4;
}

byte core::res4hl( void )
{
	mem[regs.w.hl] &= ~16;
	regs.w.pc++;
	return 4;
}

byte core::res5hl( void )
{
	mem[regs.w.hl] &= ~32;
	regs.w.pc++;
	return 4;
}

byte core::res6hl( void )
{
	mem[regs.w.hl] &= ~64;
	regs.w.pc++;
	return 4;
}

byte core::res7hl( void )
{
	mem[regs.w.hl] &= ~128;
	regs.w.pc++;
	return 4;
}
