
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

	out.open( "./incldrn.cpp" );
	if ( !out )
		return EXIT_FAILURE;

	for ( int i = 0 ; i < 7 ; i++ )
	{
		out << "static void core::ld" << regs[i].letter << "n( void );" << endl;
	}
}
