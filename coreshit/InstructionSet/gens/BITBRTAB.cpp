
#include <fstream>
#include <cstdlib>
#include <ascii.h>

char regs[8] =
{
	'b',
	'c',
	'd',
	'e',
	'h',
	'l',
	NUL,
	'a'
};

using namespace std;

int main( void )
{
	ofstream out;
	int cnt = 64;

	out.open( "./tabbitbr.cpp" );
	if ( !out )
		return EXIT_FAILURE;

	for ( int i = 0 ; i < 8 ; i++ ) for ( int j = 0 ; j < 8 ; j++ )
	{
		if ( !( cnt % 10 ) )
			out << endl << "// " << cnt << endl;

		out << '{' << endl;

		if ( j == 6 )
		{
			out << HT << "\"bit " << i << ", (hl)\"," << endl;
			out << HT << "3," << endl;
			out << HT << "&bit" << i << "hl" << endl;
		}
		else
		{
			out << HT << "\"bit " << i << ", " << regs[j] << "\"," << endl;
			out << HT << "2," << endl;
			out << HT << "&bit" << i << regs[j] << endl;
		}

		out << "}," << endl;
		cnt++;
	}
}
