
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

/*void ldrr( void )
{
	regs.b.x = regs.b.y;
	regs.w.pc++;
}*/

using namespace std;

int main( void )
{
	ofstream out;

	out.open( "./ldrr.cpp" );
	if ( !out )
		return EXIT_FAILURE;

	out << endl << "#include <jackshit.h>" << endl;

	for ( int i = 0 ; i < 7 ; i++ ) for ( int j = 0 ; j < 7 ; j++ )
	{
		out << endl << "void ld" << regs[i].letter << regs[j].letter << "( void )" << endl;
		out << '{' << endl;
		out << HT << "regs.b." << regs[i].letter << " = regs.b." << regs[j].letter << ";" << endl;
		out << HT << "regs.w.pc++;" << endl << '}' << endl;
	}
}
