
#include <jackshit.h>

byte core::ldbcnn( void )
{
	regs.w.bc = mem[regs.w.pc + 1];
	regs.w.pc += 3;
	return 3;
}

byte core::lddenn( void )
{
	regs.w.de = mem[regs.w.pc + 1];
	regs.w.pc += 3;
	return 3;
}

byte core::ldhlnn( void )
{
	regs.w.hl = mem[regs.w.pc + 1];
	regs.w.pc += 3;
	return 3;
}

byte core::ldspnn( void )
{
	regs.w.sp = mem[regs.w.pc + 1];
	regs.w.pc += 3;
	return 3;
}
