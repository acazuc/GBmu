
#include <memboy.h>
#include <iostream>

memboy::mempassthru::operator byte( void )
{
	return (*ref).deref( ptchosen );
}

memboy::mempassthru::operator word( void )
{
	union xword ret;

	ret.b.l = (*ref).deref( ptchosen );
	ret.b.h = (*ref).deref( ptchosen + 1 );
	return ret.w;
}

memboy::mempassthru::operator char( void )
{
	return ( char ) (*ref).deref( ptchosen );
}

memboy::mempassthru &memboy::mempassthru::operator =( byte b )
{
	(*ref).deref( ptchosen ) = b;
	return *this;
}

memboy::mempassthru &memboy::mempassthru::operator =( word w )
{
	union xword &in = *( union xword * ) &w;

	(*ref).deref( ptchosen ) = in.b.l;
	(*ref).deref( ptchosen + 1 ) = in.b.h;
	return *this;
}

memboy::mempassthru &memboy::mempassthru::operator =( mempassthru &m )
{
	(*ref).deref( ptchosen ) = (*ref).deref( m.ptchosen );
	return *this;
}

memboy::mempassthru &memboy::mempassthru::operator ++( int n )
{
	(*ref).deref( ptchosen )++;
	return *this;
}

memboy::mempassthru &memboy::mempassthru::operator --( int n )
{
	(*ref).deref( ptchosen )--;
	return *this;
}

memboy::memboy( void )
{
	map = new byte [0x10000];
	bank1chardts = new byte [0x2000];
	svbk2to7 = new byte [0x6000];

	for ( int i = 0 ; i < MEMBOY_MAXSTACK ; i++ )
		block[i].ref = this;

	blockid = 0;
}

byte &memboy::deref( word addr )
{
	if ( addr < 0x8000 )
		return map[addr];
	if ( addr < 0xA000 )
	{
		if ( map[VBK] & 1 )
			return bank1chardts[addr - 0x8000];
		else
			return map[addr];
	}
	if ( addr < 0xD000 )
		return map[addr];
	if ( addr < 0xE000 )
	{
		byte bkid = map[SVBK] & 7;

		if ( bkid > 1 )
			return svbk2to7[0x1000 * ( bkid - 2 ) + ( addr - 0xD000 )];
		else
			return map[addr];
	}
	return map[addr];
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

memboy::~memboy( void )
{
	delete [] map;
	delete [] bank1chardts;
	delete [] svbk2to7;
}
