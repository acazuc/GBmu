
#include <memboy.h>
#include <iostream>
#include <cstring>

#pragma GCC diagnostic ignored "-Wint-to-pointer-cast"

void memboy::memref::set( byte b )
{
	( (*ref).*setfunc )( addr, b );
}

byte memboy::memref::get( void )
{
	return ( (*ref).*getfunc )( addr );
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
	rombank1ton = NULL;
	vram = new byte [0x4000];
	cartram = NULL;
	svbk0 = new byte [0x1000];
	svbk1to7 = new byte [0x7000];
	oam = new byte [0x100];
	hram = new byte [0x100];

	memset( hram, 0, 0x100 );

	for ( int i = 0 ; i < MEMBOY_MAXSTACK ; i++ )
		block[i].ref = this;

	for ( int i = 0 ; i < MEMREF_MAXSTACK ; i++ )
		rblock[i].ref = this;

	blockid = 0;
	rblockid = 0;
	joyparrows = 0x0f;
	joypbuttons = 0x0f;

	memset( cgbbgpalette, 0, 64 );
	memset( cgbsppalette, 0, 64 );

	currom = NULL;
	curram = NULL;
	currom0set = &memboy::romset;
	currom1set = &memboy::deadset;
	currom1get = &memboy::deadget;
	curramset = &memboy::deadset;
	curramget = &memboy::deadget;

	dmalock = false;
}

void memboy::classicset( byte *addr, byte b )
{
	*addr = b;
}

byte memboy::classicget( byte *addr )
{
	return *addr;
}

// MBC2 Special RAM Accessers
void memboy::mbc2rset( byte *addr, byte b )
{
	*addr = b & 0x0f;
}

byte memboy::mbc2rget( byte *addr )
{
	return *addr;
}

// ROM Accessers
void memboy::romset( byte *addr, byte b )
{
}

byte memboy::romget( byte *addr )
{
	return *addr;
}

byte memboy::rom0get( byte *addr )
{
	return rombank0[( word ) addr];
}

byte memboy::rom1get( byte *addr )
{
	return currom[( ( word ) addr ) - 0x4000];
}

// ROM MBC1 Setter
void memboy::mbc1set( byte *addr, byte b )
{
	//cout << hex << ( word ) addr << ' ' << ( ( ( word ) addr ) / 0x2000 ) << ' ' << ( int ) b << endl;
	//cout << hex << ( word ) addr << ' ' << ( int ) b << endl;
	switch ( ( ( word ) addr ) / 0x2000 )
	{
		case 0:
			if ( ( b & 0x0f ) == 0x0A )
			{
				curramset = memboy::cramset;
				curramget = memboy::cramget;
			}
			else
			{
				curramset = &memboy::deadset;
				curramget = &memboy::deadget;
				if ( battery )
					dumpsave();
			}
			break;
		case 1:
			if ( !( b & 0b00011111 ) )
				b++;
			rbkid = ( rbkid & 0b11100000 ) | ( b & 0b00011111 );
			if ( rbkid & 0b10000000 )
				currom = rombank1ton + 0x4000 * ( ( rbkid & 0b00011111 ) - 1 );
			else
				currom = rombank1ton + 0x4000 * ( ( rbkid & 0b01111111 ) - 1 );
			break;
		case 2:
			rbkid = ( rbkid & 0b10011111 ) | ( ( b << 5 ) & 0b01100000 );
			if ( rbkid & 0b10000000 )
				curram = cartram + 0x2000 * ( b & 0b00000011 );
			else
				currom = rombank1ton + 0x4000 * ( ( rbkid & 0b01111111 ) - 1 );
			break;
		case 3:
			if ( b & 0x01 )
			{
				curram = cartram + 0x2000 * ( ( rbkid & 0b01100000 ) >> 5 );
				currom = rombank1ton + 0x4000 * ( ( rbkid & 0b00011111 ) - 1 );
				rbkid |= 0b10000000;
			}
			else
			{
				curram = cartram;
				currom = rombank1ton + 0x4000 * ( ( rbkid & 0b01111111 ) - 1 );
				rbkid &= 0b01111111;
			}
			break;
	}
	cout << ( ( rbkid & 0b10000000 ) >> 7 ) << ' ' << ( ( rbkid & 0b01100000 ) >> 5 ) << ' ' << ( rbkid & 0b00011111 ) << endl;
	cout << ( void * ) currom << ' ' << ( void * ) rombank1ton << endl;
	cout << ( void * ) curram << ' ' << ( void * ) cartram << endl;
}

// ROM MBC2 Setter
void memboy::mbc2set( byte *addr, byte b )
{
	switch ( ( ( word ) addr ) / 0x1000 )
	{
		case 0:
			if ( !( ( ( word ) addr ) & 0b00010000 ) )
			{
				if ( ( b & 0x0f ) == 0x0A )
				{
					curramset = memboy::cramset;
					curramget = memboy::cramget;
				}
				else
				{
					curramset = &memboy::deadset;
					curramget = &memboy::deadget;
					if ( battery )
						dumpsave();
				}
			}
			break;
		case 1:
			if ( ( ( word ) addr ) & 0b00010000 )
			{
				b = b & 0x0f;

				if ( b )
					currom = rombank1ton;
				else
					currom = rombank1ton + 0x4000 * ( b - 1 );
				break;
			}
	}
}

// ROM MBC3 Setter
void memboy::mbc3set( byte *addr, byte b )
{
	//cout << hex << ( word ) addr << ' ' << ( ( ( word ) addr ) / 0x2000 ) << ' ' << ( int ) b << endl;
	//cout << hex << ( word ) addr << ' ' << ( int ) b << endl;
	switch ( ( ( word ) addr ) / 0x2000 )
	{
		case 0:
			if ( ( b & 0x0f ) == 0x0A )
			{
				curramset = memboy::cramset;
				curramget = memboy::cramget;
			}
			else
			{
				curramset = &memboy::deadset;
				curramget = &memboy::deadget;
				if ( battery )
					dumpsave();
			}
			break;
		case 1:
			b = b & 0b01111111;

			if ( b )
				currom = rombank1ton;
			else
				currom = rombank1ton + 0x4000 * ( b - 1 );
			break;
		case 2:
			if ( b > 0x03 )
				curram = fakertc;
			else
				curram = cartram + 0x2000 * rambkid5;
			break;
		case 3:
			break;
	}
}


// ROM MBC5 Setter
void memboy::mbc5set( byte *addr, byte b )
{
	//cout << hex << ( word ) addr << ' ' << ( ( ( word ) addr ) / 0x2000 ) << ' ' << ( int ) b << endl;

	//cout << hex << ( word ) addr << ' ' << ( int ) b << endl;

	switch ( ( ( word ) addr ) / 0x1000 )
	{
		case 0:
		case 1:
			if ( ( b & 0x0f ) == 0x0A )
			{
				curramset = memboy::cramset;
				curramget = memboy::cramget;
			}
			else
			{
				curramset = &memboy::deadset;
				curramget = &memboy::deadget;
				if ( battery )
					dumpsave();
			}
			break;
		case 2:
			rombkid5.b.l = b;
			if ( !rombkid5.w )
				currom = rombank0;
			else
				currom = rombank1ton + 0x4000 * ( rombkid5.w - 1 );
			break;
		case 3:
			rombkid5.b.h = b & 0b00000001;
			if ( !rombkid5.w )
				currom = rombank0;
			else
				currom = rombank1ton + 0x4000 * ( rombkid5.w - 1 );
			break;
		case 4:
		case 5:
			rambkid5 = b & 0x0f;
			curram = cartram + 0x2000 * rambkid5;
			break;
	}
}

// Dead Acessers
void memboy::deadset( byte *addr, byte b )
{
}

byte memboy::deadget( byte *addr )
{
	return 0;
}

// P1/JOYP Accessers
void memboy::joypset( byte *addr, byte b )
{
	*addr = b & 0b11110000;
}

byte memboy::joypget( byte *addr )
{
	switch ( *addr & 0b00110000 )
	{
		case 0b00000000:
			return ( joypbuttons & joyparrows ) | *addr;
		case 0b00010000:
			return joypbuttons | *addr;
		case 0b00100000:
			return joyparrows | *addr;
		case 0b00110000:
			return *addr;
	}
}

// Color Palettes Accessers
void memboy::bgpset( byte *addr, byte b )
{
	cgbbgpalette[REGS( BCPS ) & 0b00111111] = b;
	if ( REGS( BCPS ) & 0b10000000 )
		REGS( BCPS ) = ( REGS( BCPS ) + 1 ) & 0b10111111;
}

byte memboy::bgpget( byte *addr )
{
	return cgbbgpalette[REGS( BCPS ) & 0b00111111];
}

void memboy::sppset( byte *addr, byte b )
{
	cgbsppalette[REGS( OCPS ) & 0b00111111] = b;
	if ( REGS( OCPS ) & 0b10000000 )
		REGS( OCPS ) = ( REGS( OCPS ) + 1 ) & 0b10111111;
}

byte memboy::sppget( byte *addr )
{
	return cgbsppalette[REGS( OCPS ) & 0b00111111];
}

void memboy::divset( byte *addr, byte b )
{
	*addr = 0;
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
		// Bank 0 Sector
		if ( addr < 0x4000 )
		{
			// Bios & RST/IRQ Sector
			if ( addr < 0x0100 )
			{
				if ( REGS( RBK ) & 1 )
				{
					(*ref).getfunc = &memboy::rom0get;
					(*ref).setfunc = currom0set;
					(*ref).addr = ( byte * ) addr;
					return ref;
				}

				(*ref).getfunc = &memboy::romget;
				(*ref).setfunc = &memboy::romset;
				(*ref).addr = &biosrombank[addr];
				return ref;
			}

			// Bios Xtend Sector
			if ( ( addr >= 0x0200 ) && ( addr < 0x1000 ) )
			{
				if ( REGS( RBK ) & 1 )
				{
					(*ref).getfunc = &memboy::rom0get;
					(*ref).setfunc = currom0set;
					(*ref).addr = ( byte * ) addr;
					return ref;
				}

				(*ref).getfunc = &memboy::romget;
				(*ref).setfunc = &memboy::romset;
				(*ref).addr = &biosromxtend[addr - 0x0200];
				return ref;
			}

			(*ref).getfunc = &memboy::rom0get;
			(*ref).setfunc = currom0set;
			(*ref).addr = ( byte * ) addr;
			return ref;
		}

		// Bank 1 Sector
		(*ref).getfunc = currom1get;
		(*ref).setfunc = currom1set;
		(*ref).addr = ( byte * ) addr;
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
			(*ref).getfunc = curramget;
			(*ref).setfunc = curramset;
			(*ref).addr = &curram[addr - 0xa000];
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

		if ( addr == DIV )
		{
			(*ref).getfunc = &memboy::classicget;
			(*ref).setfunc = &memboy::divset;
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

bool memboy::isdmalocked( void )
{
	return dmalock;
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

void memboy::startsave( const char *path )
{
	string save( path );
	ifstream insave;

	save.append( ".save" );

	insave.open( save );
	if ( insave )
	{
		insave.read( cartram, nram );	
		insave.close();
	}

	savefile.open( save );
}

void memboy::dumpsave( void )
{
	savefile.seekp( 0 );
	savefile.write( cartram, nram );
}

bool memboy::romload( const char *path )
{
	ifstream in;
	struct header *head;
	int len;
	int nbk;
	int off;
	void ( memboy::*tmpramset )( byte *addr, byte b );
	byte ( memboy::*tmpramget )( byte *addr );

	// Clear existing maps if any
	if ( rombank1ton )
		delete [] rombank1ton;
	rombank1ton = NULL;
	currom = NULL;
	if ( cartram )
		delete [] cartram;
	cartram = NULL;
	curram = NULL;
	currom0set = &memboy::romset;
	currom1set = &memboy::deadset;
	currom1get = &memboy::deadget;
	curramset = &memboy::deadset;
	curramget = &memboy::deadget;
	cramset = &memboy::deadset;
	cramget = &memboy::deadget;
	tmpramset = &memboy::deadset;
	tmpramget = &memboy::deadget;

	// Open ROM, abort if it fails
	in.open( path );
	if ( !in || in.eof() )
		return false;

	// Define file length
	in.seekg( 0, in.end );
	len = in.tellg();
	in.seekg( 0, in.beg );

	nbk = len / 0x4000;
	if ( off = len % 0x4000 )
		nbk++;

	//cout << nbk << ' ' << off << ' ' << hex << len << endl;

	// Return false if ROM doesn't have any byte in program area
	if ( len < 0x151 )
		return false;

	// Load first rom bank in memory
	in.read( ( char * ) rombank0, 0x4000 );

	head = ( struct header * ) &rombank0[0x100];
	switch ( (*head).carttype )
	{
		case 0x00: // ROM Only
			battery = false;
			break;

		case 0x01: // MBC 1
			currom0set = &memboy::mbc1set;
			currom1set = &memboy::mbc1set;
			rbkid = 1;
			battery = false;
			break;

		case 0x02: // MBC 1 + RAM
			currom0set = &memboy::mbc1set;
			currom1set = &memboy::mbc1set;
			cramset = &memboy::classicset;
			cramget = &memboy::classicget;
			rbkid = 1;
			battery = false;
			break;

		case 0x03: // MBC 1 + RAM + Battery
			currom0set = &memboy::mbc1set;
			currom1set = &memboy::mbc1set;
			cramset = &memboy::classicset;
			cramget = &memboy::classicget;
			rbkid = 1;
			battery = true;
			break;

		case 0x05: // MBC 2
			currom0set = &memboy::mbc2set;
			currom1set = &memboy::mbc2set;
			cramset = &memboy::mbc2rset;
			cramget = &memboy::mbc2rget;
			nram = 0x2000;
			cartram = new byte [0x2000];
			curram = cartram;
			battery = false;
			break;

		case 0x06: // MBC 2 + Battery
			currom0set = &memboy::mbc2set;
			currom1set = &memboy::mbc2set;
			cramset = &memboy::mbc2rset;
			cramget = &memboy::mbc2rget;
			nram = 0x2000;
			cartram = new byte [0x2000];
			curram = cartram;
			battery = true;
			break;

		case 0x0a: // MBC 3 + Timer + Battery
			currom0set = &memboy::mbc3set;
			currom1set = &memboy::mbc3set;
			rbkid = 1;
			battery = true;
			break;

		case 0x10: // MBC 3 + RAM + Battery
			currom0set = &memboy::mbc3set;
			currom1set = &memboy::mbc3set;
			cramset = &memboy::classicset;
			cramget = &memboy::classicget;
			rbkid = 1;
			battery = true;
			break;		

		case 0x11: // MBC 3
			currom0set = &memboy::mbc3set;
			currom1set = &memboy::mbc3set;
			rbkid = 1;
			battery = false;
			break;

		case 0x12: // MBC 3 + RAM
			currom0set = &memboy::mbc3set;
			currom1set = &memboy::mbc3set;
			cramset = &memboy::classicset;
			cramget = &memboy::classicget;
			rbkid = 1;
			battery = false;
			break;

		case 0x13: // MBC 3 + RAM + Battery
			currom0set = &memboy::mbc3set;
			currom1set = &memboy::mbc3set;
			cramset = &memboy::classicset;
			cramget = &memboy::classicget;
			rbkid = 1;
			battery = true;
			break;

		case 0x19: // MBC 5
			currom0set = &memboy::mbc5set;
			currom1set = &memboy::mbc5set;
			rombkid5.w = 1;
			battery = false;
			break;

		case 0x1a: // MBC 5 + RAM
			currom0set = &memboy::mbc5set;
			currom1set = &memboy::mbc5set;
			cramset = &memboy::classicset;
			cramget = &memboy::classicget;
			rombkid5.w = 1;
			battery = false;
			break;

		case 0x1b: // MBC 5 + RAM + Battery
			currom0set = &memboy::mbc5set;
			currom1set = &memboy::mbc5set;
			cramset = &memboy::classicset;
			cramget = &memboy::classicget;
			rombkid5.w = 1;
			battery = true;
			break;

		default: // Unhandeled Cartridge Type
			return false;
	}

	cout << hex << ( int ) (*head).romsize << ' ' << ( int ) (*head).ramsize << endl;

	// Load remaining ROM banks if any
	if ( !--nbk )
	{
		if ( off )
			memset( rombank0 + off, 0, 0x4000 - off );
	}
	else
	{
		cout << dec << nbk << endl;
		rombank1ton = new byte [0x4000 * nbk];
		currom = rombank1ton;
		currom1get = &memboy::rom1get;
		in.read( ( char * ) rombank1ton, 0x4000 * nbk );
		if ( off )
			memset( rombank1ton + ( 0x4000 * ( nbk - 1 ) ) + off, 0, 0x4000 - off );
	}

	// Set up Cart RAM ( if any )
	switch ( (*head).ramsize )
	{
		case 0x00:
			break;
		case 0x01:
		case 0x02:
			nram = 0x2000;
			cartram = new byte [0x2000];
			curram = cartram;
			curramset = tmpramset;
			curramget = tmpramget;
			break;
		case 0x03:
			nram = 0x8000;
			cartram = new byte [0x8000];
			curram = cartram;
			curramset = tmpramset;
			curramget = tmpramget;
			break;
		case 0x04:
			nram = 0x2c000;
			cartram = new byte [0x2c000];
			curram = cartram;
			curramset = tmpramset;
			curramget = tmpramget;
			break;
		case 0x05:
			nram = 0x10000;
			cartram = new byte [0x10000];
			curram = cartram;
			curramset = tmpramset;
			curramget = tmpramget;
			break;
	}

	/*for ( int i = 0 ; i < 0x4000 ; i++ )
	  cout << hex << ( int ) rombank0[i] << ' ';
	  for ( int i = 0 ; i < ( nbk * 0x4000 ) ; i++ )
	  cout << hex << ( int ) rombank1ton[i] << ' ';
	  cout << endl;*/

	if ( battery )
		startsave( path );

	return true;
}

void memboy::ramclear( void )
{
	memset( vram, 0, 0x4000 );
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
	if ( rombank1ton )
		delete [] rombank1ton; // 4000 - 7fff
	delete [] vram; // 8000 - 9fff
	if ( cartram )
		delete [] cartram; // a000 - bfff
	delete [] svbk0; // c000 - cfff
	delete [] svbk1to7; // d000 - dfff
	delete [] oam; // fe00 - fe9f
	delete [] hram; // ff00 - ffff
}
