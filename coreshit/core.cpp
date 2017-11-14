
#include <jackshit.h>

memboy core::mem;
byte core::cycle;
struct core::instruction *core::next;
union core::registers core::regs;

void core::init( void )
{
	cycle = 0;
	regs.w.pc = 0x100;
	regs.w.sp = 0;
	regs.w.af = 0;
	regs.w.bc = 0;
	regs.w.de = 0;
	regs.w.hl = 0;
}

const char *core::cue( void )
{
	switch ( cycle )
	{
		case 0:
			next = &decode[( byte ) mem[regs.w.pc]];
			if ( (*next).cycles > 1 )
			{
				cycle = (*next).cycles - 1;
				return nullptr;
			}
		case 1:
			(*next).function();
			cycle = 0;
			return (*next).mnemonic;
		default:
			cycle--;
			return nullptr;
	}
}

word core::getpc( void )
{
	return regs.w.pc;
}
