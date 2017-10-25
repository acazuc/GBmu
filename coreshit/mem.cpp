
#include <jackshit.h>

memboy::memboy( void )
{
	map = new byte [0x10000];
	bank1chardts = new byte [0x2000];
	svbk2to7 = new byte [0x6000];
}

byte &memboy::operator []( word addr )
{
	if ( addr < 0x8000 )
		return map[addr];
	if ( addr < 0xA000 )
	{
		if ( map[VBK] & 1 )
			return bank1chardts[addr - 0x8000];
		return map[addr];
	}
	if ( addr < 0xD000 )
		return map[addr];
	if ( addr < 0xE000 )
	{
		byte bkid = map[SVBK] & 7;

		if ( bkid > 1 )
			return svbk2to7[0x1000 * ( bkid - 2 ) + ( addr - 0xD000 )];
		return map[addr];
	}
	return map[addr];
}

memboy::~memboy( void )
{
	delete [] map;
	delete [] bank1chardts;
	delete [] svbk2to7;
}
