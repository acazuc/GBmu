
#include <memboy.h>
#include <iostream>

using namespace std;

int main( int ac, char **av )
{
	memboy yay;

	yay[VBK] = 0;
	yay[0x8004] = 0xFE;
	yay[VBK] = 1;
	yay[0x8004] = 0xFF;

	yay[VBK] = 0;
	cout << ( int ) yay[0x8004] << endl;
	yay[VBK] = 1;
	cout << ( int ) yay[0x8004] << endl << endl;

	for ( yay[SVBK] = 1 ; yay[SVBK] <= 7 ; yay[SVBK]++ )
	{
		yay[0xD000] = yay[SVBK];
	}

	for ( yay[SVBK] = 1 ; yay[SVBK] <= 7 ; yay[SVBK]++ )
	{
		cout << ( int ) yay[0xD000] << ' ' << ( int ) yay[SVBK] << endl;
	}

	yay[VBK] = 0;
	yay[0x8000] = 45;
	cout << ( int ) yay.cbank0( 0x8000 ) << endl;

	for ( int i = 0 ; i < 0x10000 ; i++ )
		yay[i] = 0;

	return 0;
}
