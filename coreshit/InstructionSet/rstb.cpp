
#include <jackshit.h>

byte core::rst0( void )
{
	mem[regs.w.sp -= 2] = ( word ) ( regs.w.pc + 3 );
	regs.w.pc = 0x0;
	return 4;
}

byte core::rst1( void )
{
	mem[regs.w.sp -= 2] = ( word ) ( regs.w.pc + 3 );
	regs.w.pc = 0x8;
	return 4;
}

byte core::rst2( void )
{
	mem[regs.w.sp -= 2] = ( word ) ( regs.w.pc + 3 );
	regs.w.pc = 0x10;
	return 4;
}

byte core::rst3( void )
{
	mem[regs.w.sp -= 2] = ( word ) ( regs.w.pc + 3 );
	regs.w.pc = 0x18;
	return 4;
}

byte core::rst4( void )
{
	mem[regs.w.sp -= 2] = ( word ) ( regs.w.pc + 3 );
	regs.w.pc = 0x20;
	return 4;
}

byte core::rst5( void )
{
	mem[regs.w.sp -= 2] = ( word ) ( regs.w.pc + 3 );
	regs.w.pc = 0x28;
	return 4;
}

byte core::rst6( void )
{
	mem[regs.w.sp -= 2] = ( word ) ( regs.w.pc + 3 );
	regs.w.pc = 0x30;
	return 4;
}

byte core::rst7( void )
{
	mem[regs.w.sp -= 2] = ( word ) ( regs.w.pc + 3 );
	regs.w.pc = 0x38;
	return 4;
}
