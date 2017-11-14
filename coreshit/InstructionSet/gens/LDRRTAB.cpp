
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

	out.open( "./tabldrr.cpp" );
	if ( !out )
		return EXIT_FAILURE;

	for ( int i = 0 ; i < 8 ; i++ ) for ( int j = 0 ; j < 8 ; j++ )
	{
		if ( !( cnt % 10 ) )
			out << endl << "// " << cnt << endl;

		out << '{' << endl;

		if ( i == 6 )
		{
			if ( j == 6 )
			{
				out << HT << "\"__ NO INSTRUCTION __\"," << endl;
				out << HT << "1," << endl;
				out << HT << "&_blank" << endl;
			}
			else
			{
				out << HT << "\"ld (hl), " << regs[j] << "\"," << endl;
				out << HT << "2," << endl;
				out << HT << "&ldhl" << regs[j] << endl;
			}
		}
		else if ( j == 6 )
		{
			out << HT << "\"ld " << regs[i] << ", (hl)\"," << endl;
			out << HT << "2," << endl;
			out << HT << "&ld" << regs[i] << "hl" << endl;
		}
		else
		{
			out << HT << "\"ld " << regs[i] << ", " << regs[j] << "\"," << endl;
			out << HT << "1," << endl;
			out << HT << "&ld" << regs[i] << regs[j] << endl;
		}

		out << "}," << endl;
		cnt++;
	}
}
