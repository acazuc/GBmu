
#include <jackshit.h>

memboy core::mem;
byte core::cycle;
struct core::instruction *core::next;
union core::registers core::regs;
bool core::ime;
byte core::state;
bool core::x2speed;
bool core::on;

void core::init( void )
{
	cycle = 0;
	ime = false;
	state = CPU_RUN;
	x2speed = false;
	on = true;
	regs.w.pc = ref::start;
	regs.w.sp = 0xFFFE;
	regs.w.af = 0;
	regs.w.bc = 0;
	regs.w.de = 0;
	regs.w.hl = 0;
}

const char *core::cue( void )
{
	if ( !on )
		return nullptr;

	if ( cycle )
	{
		cycle--;
		return nullptr;
	}

	if ( mem[IF] && ime )
	{
		byte req = mem[IF] & mem[IE];

		for ( byte i = 1, off = 0 ; i != 32 ; i <<= 1, off += 8 )
		{
			if ( req & i )
			{
				mem[regs.w.sp -= 2] = ( word ) regs.w.pc;
				regs.w.pc = 0x40 + off;
				state = CPU_RUN;
				mem[IF] &= ~i;
				ime = false;
				goto decode;
			}
		}
	}

	if ( state != CPU_RUN )
		return nullptr;

decode:	next = &decode[( byte ) mem[regs.w.pc]];
	if ( !(*next).function )	
		next = &extdec[( byte ) mem[++regs.w.pc]];
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

byte core::getstate( void )
{
	return state;
}

bool core::is2xspeed( void )
{
	return x2speed;
}

bool core::getime( void )
{
	return ime;
}

void core::switchon( void )
{
	on = true;
}

void core::switchoff( void )
{
	on = false;
}
