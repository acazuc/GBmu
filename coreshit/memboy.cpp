
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
	map = new byte [0x10000];
	bank1chardts = new byte [0x2000];
	svbk2to7 = new byte [0x6000];
	rombank = new byte [0x100];
	romxtend = new byte [0x800];

	for ( int i = 0 ; i < MEMBOY_MAXSTACK ; i++ )
		block[i].ref = this;

	for ( int i = 0 ; i < MEMREF_MAXSTACK ; i++ )
		rblock[i].ref = this;

	blockid = 0;
	rblockid = 0;

	joyparrows = 0x0f;
	joypbuttons = 0x0f;

	map[RBK] = 0;
	map[DMA] = 0;

	map[BCPS] = 0;
	map[OCPS] = 0;

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

void memboy::bgpset( byte &addr, byte b )
{
	cgbbgpalette[map[BCPS] & 0b00111111] = b;
	if ( map[BCPS] & 0b10000000 )
		map[BCPS] = ( map[BCPS] + 1 ) & 0b00111111;
}

byte memboy::bgpget( byte &addr )
{
	return cgbbgpalette[map[BCPS] & 0b00111111];
}

void memboy::sppset( byte &addr, byte b )
{
	cgbsppalette[map[OCPS] & 0b00111111] = b;
	if ( map[OCPS] & 0b10000000 )
		map[OCPS] = ( map[OCPS] + 1 ) & 0b00111111;
}

byte memboy::sppget( byte &addr )
{
	return cgbsppalette[map[OCPS] & 0b00111111];
}

memboy::memref *memboy::deref( word addr )
{
	memref *ref;

	if ( rblockid == MEMREF_MAXSTACK )
		rblockid = 0;
	ref = &rblock[rblockid++];

	// Bios & RST/IRQ Sector
	if ( addr < 0x0100 )
	{
		(*ref).getfunc = &memboy::classicget;
		(*ref).setfunc = &memboy::classicset;

		if ( map[RBK] & 1 )
		{
			(*ref).addr = &map[addr];
			return ref;
		}
		
		(*ref).addr = &rombank[addr];
		return ref;
	}

	// Rom Sector
	if ( addr < 0x8000 )
	{
		(*ref).getfunc = &memboy::classicget;
		(*ref).setfunc = &memboy::classicset;
		if ( ( addr >= 0x0200 ) && ( addr < 0x1000 ) )
		{
			if ( map[RBK] & 1 )
			{
				(*ref).addr = &map[addr];
				return ref;
			}

			(*ref).addr = &romxtend[addr - 0x0200];
			return ref;
		}
		(*ref).addr = &map[addr];
		return ref;
	}

	// VRAM Sector
	if ( addr < 0xA000 )
	{
		(*ref).getfunc = &memboy::classicget;
		(*ref).setfunc = &memboy::classicset;

		if ( map[VBK] & 1 )
		{
			(*ref).addr = &bank1chardts[addr - 0x8000];
			return ref;
		}

		(*ref).addr = &map[addr];
		return ref;
	}

	// WRAM Sector
	if ( addr < 0xD000 )
	{
		(*ref).getfunc = &memboy::classicget;
		(*ref).setfunc = &memboy::classicset;
		(*ref).addr = &map[addr];
		return ref;
	}

	// WRAM Bank Sector
	if ( addr < 0xE000 )
	{
		byte bkid = map[SVBK] & 7;

		(*ref).getfunc = &memboy::classicget;
		(*ref).setfunc = &memboy::classicset;

		if ( bkid > 1 )
		{
			(*ref).addr = &svbk2to7[0x1000 * ( bkid - 2 ) + ( addr - 0xD000 )];
			return ref;
		}

		(*ref).addr = &map[addr];
		return ref;
	}

	// Registers Sector
	if ( addr == 0xFF00 )
	{
		(*ref).getfunc = &memboy::joypget;
		(*ref).setfunc = &memboy::joypset;
		(*ref).addr = &map[addr];
		return ref;
	}

	if ( addr == BCPD )
	{
		(*ref).getfunc = &memboy::bgpget;
		(*ref).setfunc = &memboy::bgpset;
		(*ref).addr = &map[addr];
		return ref;
	}

	if ( addr == OCPD )
	{
		(*ref).getfunc = &memboy::sppget;
		(*ref).setfunc = &memboy::sppset;
		(*ref).addr = &map[addr];
		return ref;
	}

	// End Sector
	(*ref).getfunc = &memboy::classicget;
	(*ref).setfunc = &memboy::classicset;
	(*ref).addr = &map[addr];
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
	return map[addr];
}

byte &memboy::cbank1( word addr )
{
	if ( addr < 0x8000 || addr > 0x9fff )
		return map[addr];
	return bank1chardts[addr - 0x8000];
}

byte &memboy::sysregs( word addr )
{
	return map[addr];
}

byte *memboy::sppalette( byte id )
{
	if ( id > 8 )
		return NULL;
	return &cgbsppalette[id * 8];
}

byte *memboy::bgpalette( byte id )
{
	if ( id > 8 )
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

	for ( byte *cmap = rombank ; cmap < ( rombank + 0x100 ) ; cmap++ )
	{
		*cmap = in.get();
		if ( in.eof() )
		{
			*cmap = 0;
			return true;
		}
		//cout << hex << cmap - rombank << " : " << ( int ) *cmap << ' ';
	}

	if ( len <= 0x200 )
		return true;

	in.seekg( 0x200, in.beg );
	for ( byte *cmap = romxtend ; cmap < ( romxtend + 0x800 ) ; cmap++ )
	{
		*cmap = in.get();
		if ( in.eof() )
		{
			*cmap = 0;
			return true;
		}
		//cout << hex << cmap - romxtend << " : " << ( int ) *cmap << ' ';
	}

	return false;
}

bool memboy::romload( const char *path )
{
	ifstream in;

	in.open( path );
	if ( !in || in.eof() )
		return false;

	for ( byte *cmap = map ; cmap < ( map + 0x10000 ) ; cmap++ )
	{
		*cmap = in.get();
		if ( in.eof() )
			return true;
	}
	return false;
}

void memboy::ramclear( void )
{
	memset( &map[0x8000], 0, 0x8000 );
	memset( bank1chardts, 0, 0x2000 );
	memset( svbk2to7, 0, 0x6000 );
}

memboy::~memboy( void )
{
	delete [] map;
	delete [] bank1chardts;
	delete [] svbk2to7;
	delete [] rombank;
}
