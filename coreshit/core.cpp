
#include <jackshit.h>

memboy core::mem;
byte core::cycle;
struct core::instruction *core::next;
union core::registers core::regs;

void core::init( void )
{
	cycle = 0;
	regs.w.pc = 0x000;
	regs.w.sp = 0xFFFE;
	regs.w.af = 0;
	regs.w.bc = 0;
	regs.w.de = 0;
	regs.w.hl = 0;
}

const char *core::cue( void )
{
	if ( cycle )
	{
		cycle--;
		return nullptr;
	}
	next = &decode[( byte ) mem[regs.w.pc]];
	cycle = (*next).function() - 1;
	return (*next).mnemonic;
}

word core::getpc( void )
{
	return regs.w.pc;
}
