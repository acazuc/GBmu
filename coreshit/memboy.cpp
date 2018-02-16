
#include <memboy.h>
#include <iostream>
#include <cstring>

void memboy::memref::set( byte b )
{
	( (*ref).*setfunc )( *addr, b );
}

byte memboy::memref::get( void )
{
	return ( (*ref).*getfunc )( *addr );
}

memboy::mempassthru::operator byte( void )
{
	memref *mref;

	mref = (*ref).deref( ptchosen );
	return (*mref).get();
}

memboy::mempassthru::operator word( void )
{
	union xword ret;
	memref *mref;

	mref = (*ref).deref( ptchosen );
	ret.b.l = (*mref).get();
	mref = (*ref).deref( ptchosen + 1 );
	ret.b.h = (*mref).get();
	return ret.w;
}

memboy::mempassthru::operator int( void )
{
	memref *mref;

	mref = (*ref).deref( ptchosen );
	return (*mref).get();
}

memboy::mempassthru::operator char( void )
{
	memref *mref;

	mref = (*ref).deref( ptchosen );
	return ( char ) (*mref).get();
}

memboy::mempassthru::operator bool( void )
{
	memref *mref;

	mref = (*ref).deref( ptchosen );
	if ( (*mref).get() )
		return true;
	return false;
}

memboy::mempassthru &memboy::mempassthru::operator =( byte b )
{
	memref *mref;

	mref = (*ref).deref( ptchosen );
	(*mref).set( b );
	return *this;
}

memboy::mempassthru &memboy::mempassthru::operator =( word w )
{
	union xword &in = *( union xword * ) &w;
	memref *mref;

	mref = (*ref).deref( ptchosen );
	(*mref).set( in.b.l );
	mref = (*ref).deref( ptchosen + 1 );
	(*mref).set( in.b.h );
	return *this;
}

memboy::mempassthru &memboy::mempassthru::operator =( int n )
{
	memref *mref;

	mref = (*ref).deref( ptchosen );
	(*mref).set( n );
	return *this;
}

memboy::mempassthru &memboy::mempassthru::operator =( mempassthru &m )
{
	memref *mref;
	memref *mref2;

	mref = (*ref).deref( ptchosen );
	mref2 = (*ref).deref( m.ptchosen );
	(*mref).set( (*mref2).get() );
	return *this;
}

memboy::mempassthru &memboy::mempassthru::operator |=( byte b )
{
	memref *mref;

	mref = (*ref).deref( ptchosen );
	(*mref).set( (*mref).get() | b );
	return *this;
}

memboy::mempassthru &memboy::mempassthru::operator |=( int n )
{
	memref *mref;

	mref = (*ref).deref( ptchosen );
	(*mref).set( (*mref).get() | n );
	return *this;
}

memboy::mempassthru &memboy::mempassthru::operator &=( byte b )
{
	memref *mref;

	mref = (*ref).deref( ptchosen );
	(*mref).set( (*mref).get() & b );
	return *this;
}

memboy::mempassthru &memboy::mempassthru::operator &=( int n )
{
	memref *mref;

	mref = (*ref).deref( ptchosen );
	(*mref).set( (*mref).get() & n );
	return *this;
}

memboy::mempassthru &memboy::mempassthru::operator ++( int n )
{
	memref *mref;

	mref = (*ref).deref( ptchosen );
	(*mref).set( (*mref).get() + 1 );
	return *this;
}

memboy::mempassthru &memboy::mempassthru::operator --( int n )
{
	memref *mref;

	mref = (*ref).deref( ptchosen );
	(*mref).set( (*mref).get() - 1 );
	return *this;
}

memboy::memboy( void )
{
	biosrombank = new byte [0x100];
	biosromxtend = new byte [0x800];
	rombank0 = new byte [0x4000];
	rombank1ton = new byte [0x4000];
	vram = new byte [0x4000];
	cartram = new byte [0x2000];
	svbk0 = new byte [0x1000];
	svbk1to7 = new byte [0x7000];
	oam = new byte [0x100];
	hram = new byte [0x100];

	for ( int i = 0 ; i < MEMBOY_MAXSTACK ; i++ )
		block[i].ref = this;

	for ( int i = 0 ; i < MEMREF_MAXSTACK ; i++ )
		rblock[i].ref = this;

	blockid = 0;
	rblockid = 0;

	joyparrows = 0x0f;
	joypbuttons = 0x0f;

	sysregs( RBK ) = 0;
	sysregs( DMA ) = 0;

	sysregs( BCPS ) = 0;
	sysregs( OCPS ) = 0;

	memset( cgbbgpalette, 0, 64 );
	memset( cgbsppalette, 0, 64 );

	dmalock = false;
}

void memboy::classicset( byte &addr, byte b )
{
	addr = b;
}

byte memboy::classicget( byte &addr )
{
	return addr;
}

// ROM Accessers
void memboy::romset( byte &addr, byte b )
{
}

byte memboy::romget( byte &addr )
{
	return addr;
}

// Dead Acessers
void memboy::deadset( byte &addr, byte b )
{
}

byte memboy::deadget( byte &addr )
{
	return 0;
}

// P1/JOYP Accessers
void memboy::joypset( byte &addr, byte b )
{
	addr = b & 0b11110000;
}

byte memboy::joypget( byte &addr )
{
	switch ( addr & 0b00110000 )
	{
		case 0b00000000:
			return ( joypbuttons & joyparrows ) | addr;
		case 0b00010000:
			return joypbuttons | addr;
		case 0b00100000:
			return joyparrows | addr;
		case 0b00110000:
			return addr;
	}
}

// Color Palettes Accessers
void memboy::bgpset( byte &addr, byte b )
{
	cgbbgpalette[REGS( BCPS ) & 0b00111111] = b;
	if ( REGS( BCPS ) & 0b10000000 )
		REGS( BCPS ) = ( REGS( BCPS ) + 1 ) & 0b10111111;
}

byte memboy::bgpget( byte &addr )
{
	return cgbbgpalette[REGS( BCPS ) & 0b00111111];
}

void memboy::sppset( byte &addr, byte b )
{
	cgbsppalette[REGS( OCPS ) & 0b00111111] = b;
	if ( REGS( OCPS ) & 0b10000000 )
		REGS( OCPS ) = ( REGS( OCPS ) + 1 ) & 0b10111111;
}

byte memboy::sppget( byte &addr )
{
	return cgbsppalette[REGS( OCPS ) & 0b00111111];
}

memboy::memref *memboy::deref( word addr )
{
	memref *ref;

	if ( rblockid == MEMREF_MAXSTACK )
		rblockid = 0;
	ref = &rblock[rblockid++];

	// ROM Sector
	if ( addr < 0x8000 )
	{
		(*ref).getfunc = &memboy::romget;
		(*ref).setfunc = &memboy::romset;

		// Bank 0 Sector
		if ( addr < 0x4000 )
		{
			// Bios & RST/IRQ Sector
			if ( addr < 0x0100 )
			{
				if ( REGS( RBK ) & 1 )
				{
					(*ref).addr = &rombank0[addr];
					return ref;
				}

				(*ref).addr = &biosrombank[addr];
				return ref;
			}

			// Bios Xtend Sector
			if ( ( addr >= 0x0200 ) && ( addr < 0x1000 ) )
			{
				if ( REGS( RBK ) & 1 )
				{
					(*ref).addr = &rombank0[addr];
					return ref;
				}

				(*ref).addr = &biosromxtend[addr - 0x0200];
				return ref;
			}

			(*ref).addr = &rombank0[addr];
			return ref;
		}

		// Bank 1 Sector
		(*ref).addr = &rombank1ton[addr - 0x4000];
		return ref;
	}

	// RAM Sector
	if ( addr < 0xff00 )
	{
		// VRAM Sector
		if ( addr < 0xa000 )
		{
			(*ref).getfunc = &memboy::classicget;
			(*ref).setfunc = &memboy::classicset;

			if ( REGS( VBK ) & 1 )
			{
				(*ref).addr = &vram[addr - 0x6000];
				return ref;
			}

			(*ref).addr = &vram[addr - 0x8000];
			return ref;
		}

		// Cartridge RAM Sector
		if ( addr < 0xc000 )
		{
			(*ref).getfunc = &memboy::classicget;
			(*ref).setfunc = &memboy::classicset;
			(*ref).addr = &cartram[addr - 0xa000];
			return ref;	
		}

		// WRAM Bank 0 Sector
		if ( addr < 0xd000 )
		{
echo0:			(*ref).getfunc = &memboy::classicget;
			(*ref).setfunc = &memboy::classicset;
			(*ref).addr = &svbk0[addr - 0xc000];
			return ref;
		}

		// WRAM Bank 1 to 7 Sector
		if ( addr < 0xe000 )
		{
echo1:			byte bkid = REGS( SVBK ) & 7;

			(*ref).getfunc = &memboy::classicget;
			(*ref).setfunc = &memboy::classicset;

			if ( bkid > 0 )
			{
				(*ref).addr = &svbk1to7[0x1000 * ( bkid - 1 ) + ( addr - 0xd000 )];
				return ref;
			}

			(*ref).addr = &svbk1to7[addr - 0xd000];
			return ref;
		}

		// ECHO Ram Sector
		if ( addr < 0xfe00 )
		{
			if ( addr < 0xf000 )
				goto echo0;
			goto echo1;
		}

		// OAM Sector
		if ( addr < 0xfea0 )
		{
			(*ref).getfunc = &memboy::classicget;
			(*ref).setfunc = &memboy::classicset;
			(*ref).addr = &oam[addr - 0xfe00];
			return ref;
		}

		// Dead Zone Sector
		(*ref).getfunc = &memboy::deadget;
		(*ref).setfunc = &memboy::deadset;
		(*ref).addr = NULL;
		return ref;
	}

	// Registers Sector
	if ( addr < 0xff80 )
	{
		if ( addr == JOYP )
		{
			(*ref).getfunc = &memboy::joypget;
			(*ref).setfunc = &memboy::joypset;
			(*ref).addr = &hram[addr - 0xff00];
			return ref;
		}

		if ( addr == BCPD )
		{
			(*ref).getfunc = &memboy::bgpget;
			(*ref).setfunc = &memboy::bgpset;
			(*ref).addr = &hram[addr - 0xff00];
			return ref;
		}

		if ( addr == OCPD )
		{
			(*ref).getfunc = &memboy::sppget;
			(*ref).setfunc = &memboy::sppset;
			(*ref).addr = &hram[addr - 0xff00];
			return ref;
		}
	}

	// HRAM Sector
	(*ref).getfunc = &memboy::classicget;
	(*ref).setfunc = &memboy::classicset;
	(*ref).addr = &hram[addr - 0xff00];
	return ref;
}

memboy::mempassthru &memboy::operator []( word addr )
{
	if ( blockid == MEMBOY_MAXSTACK )
		blockid = 0;

	block[blockid].ptchosen = addr;
	return block[blockid++];
}

byte &memboy::cbank0( word addr )
{
	return vram[addr - 0x8000];
}

byte &memboy::cbank1( word addr )
{
	return vram[addr - 0x6000];
}

byte &memboy::sysregs( word addr )
{
	return hram[addr - 0xff00];
}

byte *memboy::sppalette( byte id )
{
	if ( id >= 8 )
		return NULL;
	return &cgbsppalette[id * 8];
}

byte *memboy::bgpalette( byte id )
{
	if ( id >= 8 )
		return NULL;
	return &cgbbgpalette[id * 8];
}

void memboy::setarrowsstate( byte b )
{
	joyparrows = b & 0x0F;
}

void memboy::setbuttonsstate( byte b )
{
	joypbuttons = b & 0x0F;
}

byte memboy::getarrowsstate( void )
{
	return joyparrows;
}

byte memboy::getbuttonsstate( void )
{
	return joypbuttons;
}

void memboy::dmaswitchon( void )
{
	dmalock = true;
}

void memboy::dmaswitchoff( void )
{
	dmalock = false;
}

bool memboy::biosload( const char *path )
{
	ifstream in;
	int len;

	in.open( path );
	if ( !in || in.eof() )
		return false;

	in.seekg( 0, in.end );
	len = in.tellg();
	in.seekg( 0, in.beg );

	for ( byte *cmap = biosrombank ; cmap < ( biosrombank + 0x100 ) ; cmap++ )
	{
		*cmap = in.get();
		if ( in.eof() )
		{
			*cmap = 0;
			return true;
		}
		//cout << hex << cmap - biosrombank << " : " << ( int ) *cmap << ' ';
	}

	if ( len <= 0x200 )
		return true;

	in.seekg( 0x200, in.beg );
	for ( byte *cmap = biosromxtend ; cmap < ( biosromxtend + 0x800 ) ; cmap++ )
	{
		*cmap = in.get();
		if ( in.eof() )
		{
			*cmap = 0;
			return true;
		}
		//cout << hex << cmap - biosromxtend << " : " << ( int ) *cmap << ' ';
	}

	return false;
}

bool memboy::romload( const char *path )
{
	ifstream in;

	in.open( path );
	if ( !in || in.eof() )
		return false;

	for ( byte *cmap = rombank0 ; cmap < ( rombank0 + 0x4000 ) ; cmap++ )
	{
		*cmap = in.get();
		if ( in.eof() )
			return true;
	}

	for ( byte *cmap = rombank1ton ; cmap < ( rombank1ton + 0x4000 ) ; cmap++ )
	{
		*cmap = in.get();
		if ( in.eof() )
			return true;
	}

	return false;
}

void memboy::ramclear( void )
{
	memset( vram, 0, 0x4000 );
	memset( cartram, 0, 0x2000 );
	memset( svbk0, 0, 0x1000 );
	memset( svbk1to7, 0, 0x7000 );
	memset( oam, 0, 0x100 );
	memset( hram, 0, 0x100 );
}

memboy::~memboy( void )
{
	delete [] biosrombank; // 0000 - 0100
	delete [] biosromxtend; // 0200 - 1000
	delete [] rombank0; // 0000 - 3fff
	delete [] rombank1ton; // 4000 - 7fff
	delete [] vram; // 8000 - 9fff
	delete [] cartram; // a000 - bfff
	delete [] svbk0; // c000 - cfff
	delete [] svbk1to7; // d000 - dfff
	delete [] oam; // fe00 - fe9f
	delete [] hram; // ff00 - ffff
}
