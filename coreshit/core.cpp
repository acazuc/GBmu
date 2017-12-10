
#include <jackshit.h>

memboy core::mem;
byte core::cycle;
struct core::instruction *core::next;
union core::registers core::regs;

void core::init( void )
{
	cycle = 0;
	regs.w.pc = 0x100;
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

byte core::geta( void )
{
	return regs.b.a;
}

byte core::getb( void )
{
	return regs.b.b;
}

byte core::getc( void )
{
	return regs.b.c;
}

byte core::getd( void )
{
	return regs.b.d;
}

byte core::gete( void )
{
	return regs.b.e;
}

byte core::geth( void )
{
	return regs.b.h;
}

byte core::getl( void )
{
	return regs.b.l;
}

byte core::getflags( void )
{
	return regs.b.f;
}

word core::getpc( void )
{
	return regs.w.pc;
}

word core::getsp( void )
{
	return regs.w.sp;
}
