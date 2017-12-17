
#include <fstream>
#include <cstdlib>
#include <ascii.h>

struct reg
{
	char letter;
	char id;
};

struct reg regs[7] =
{
	{ 'a', 7 },
	{ 'b', 0 },
	{ 'c', 1 },
	{ 'd', 5 },
	{ 'e', 3 },
	{ 'h', 4 },
	{ 'l', 5 }
};

/*void setbr( void )
{
	ZUPDATE( ( regs.b.j & ( 1 << i ) ) );
	regs.w.pc++;
	return 2;
}*/

using namespace std;

int main( void )
{
	ofstream out;

	out.open( "./setbhl.cpp" );
	if ( !out )
		return EXIT_FAILURE;

	out << endl << "#include <jackshit.h>" << endl;

	for ( int i = 0 ; i < 8 ; i++ )
	{
		out << endl << "void core::set" << i << "hl( void )" << endl;
		out << '{' << endl;
		out << HT << "mem[regs.w.hl] |= " << ( 1 << i ) << ";" << endl;
		out << HT << "regs.w.pc++;" << endl;
		out << HT << "return 4;" << endl << '}' << endl;
	}
}
