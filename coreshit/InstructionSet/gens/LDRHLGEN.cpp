
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

/*void ldrhl( void )
{
	regs.b.x = mem[regs.w.hl];
	regs.w.pc++;
}*/

using namespace std;

int main( void )
{
	ofstream out;

	out.open( "./ldrhl.cpp" );
	if ( !out )
		return EXIT_FAILURE;

	out << endl << "#include <jackshit.h>" << endl;

	for ( int i = 0 ; i < 7 ; i++ )
	{
		out << endl << "void core::ld" << regs[i].letter << "hl( void )" << endl;
		out << '{' << endl;
		out << HT << "regs.b." << regs[i].letter << " = mem[regs.w.hl];" << endl;
		out << HT << "regs.w.pc += 2;" << endl << '}' << endl;
	}
}
