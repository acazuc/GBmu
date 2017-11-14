
#include <memboy.h>
#include <iostream>

memboy::mempassthru::operator byte( void )
{
	return *ptchosen;
}

memboy::mempassthru::operator word( void )
{
	return *( word * ) ptchosen;
}

memboy::mempassthru &memboy::mempassthru::operator =( byte b )
{
	*ptchosen = b;
	return *this;
}

memboy::mempassthru &memboy::mempassthru::operator =( mempassthru &m )
{
	*ptchosen = *m.ptchosen;
	return *this;
}

memboy::mempassthru &memboy::mempassthru::operator ++( int n )
{
	(*ptchosen)++;
	return *this;
}

memboy::mempassthru &memboy::mempassthru::operator --( int n )
{
	(*ptchosen)--;
	return *this;
}

memboy::memboy( void )
{
	map = new byte [0x10000];
	bank1chardts = new byte [0x2000];
	svbk2to7 = new byte [0x6000];

	blockid = 0;
}

memboy::mempassthru &memboy::operator []( word addr )
{
	if ( blockid == MEMBOY_MAXSTACK )
		blockid = 0;

	if ( addr < 0x8000 )
	{
		block[blockid].ptchosen = &map[addr];
		return block[blockid++];
	}
	if ( addr < 0xA000 )
	{
		if ( map[VBK] & 1 )
			block[blockid].ptchosen = &bank1chardts[addr - 0x8000];
		else
			block[blockid].ptchosen = &map[addr];
		return block[blockid++];
	}
	if ( addr < 0xD000 )
	{
		block[blockid].ptchosen = &map[addr];
		return block[blockid++];
	}
	if ( addr < 0xE000 )
	{
		byte bkid = map[SVBK] & 7;

		if ( bkid > 1 )
			block[blockid].ptchosen = &svbk2to7[0x1000 * ( bkid - 2 ) + ( addr - 0xD000 )];
		else
			block[blockid].ptchosen = &map[addr];
		return block[blockid++];
	}
	block[blockid].ptchosen = &map[addr];
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
