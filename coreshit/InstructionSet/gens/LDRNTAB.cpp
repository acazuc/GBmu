
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
	int cnt = 6;

	out.open( "./tabldrn.cpp" );
	if ( !out )
		return EXIT_FAILURE;

	for ( int i = 0 ; i < 8 ; i++ ) for ( int j = 0 ; j < 8 ; j++ )
	{
		if ( !( cnt % 10 ) )
			out << endl << "// " << cnt << endl;

		out << '{' << endl;

		if ( i == 6 || j > 0 )
			out << HT << "\"__ NO INSTRUCTION __\"," << endl;
		else
			out << HT << "\"ld " << regs[i] << ", n\"," << endl;

		if ( i == 6 || j > 0 )
			out << HT << "1," << endl;
		else
			out << HT << "2," << endl;

		if ( i == 6 || j > 0 )
			out << HT << "&_blank" << endl;
		else
			out << HT << "&ld" << regs[i] << 'n' << endl;

		out << "}," << endl;
		cnt++;
	}
}
