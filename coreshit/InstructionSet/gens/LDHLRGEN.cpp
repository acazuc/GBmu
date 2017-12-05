
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

char regs2[8] =
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


/*void ldhlr( void )
{
	mem[regs.w.hl] = regs.b.x;
	regs.w.pc++;
}*/

using namespace std;

int main( void )
{
	ofstream out;

	out.open( "./ldhlr.cpp" );
	if ( !out )
		return EXIT_FAILURE;

	out << endl << "#include <jackshit.h>" << endl;

	for ( int i = 0 ; i < 7 ; i++ )
	{
		out << endl << "void core::ldhl" << regs[i].letter << "( void )" << endl;
		out << '{' << endl;
		out << HT << "mem[regs.w.hl] = regs.b." << regs[i].letter << ';' << endl;
		out << HT << "regs.w.pc++;" << endl << '}' << endl;
	}
}
