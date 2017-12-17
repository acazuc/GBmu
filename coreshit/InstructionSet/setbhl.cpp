
#include <jackshit.h>

byte core::set0hl( void )
{
	mem[regs.w.hl] |= 1;
	regs.w.pc++;
	return 4;
}

byte core::set1hl( void )
{
	mem[regs.w.hl] |= 2;
	regs.w.pc++;
	return 4;
}

byte core::set2hl( void )
{
	mem[regs.w.hl] |= 4;
	regs.w.pc++;
	return 4;
}

byte core::set3hl( void )
{
	mem[regs.w.hl] |= 8;
	regs.w.pc++;
	return 4;
}

byte core::set4hl( void )
{
	mem[regs.w.hl] |= 16;
	regs.w.pc++;
	return 4;
}

byte core::set5hl( void )
{
	mem[regs.w.hl] |= 32;
	regs.w.pc++;
	return 4;
}

byte core::set6hl( void )
{
	mem[regs.w.hl] |= 64;
	regs.w.pc++;
	return 4;
}

byte core::set7hl( void )
{
	mem[regs.w.hl] |= 128;
	regs.w.pc++;
	return 4;
}
