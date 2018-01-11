
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

/*void rstb( void )
{
	mem[regs.w.sp -= 2] = ( word ) ( regs.w.pc + 3 );
	regs.w.pc = b * 8;
	return 4;
}*/

using namespace std;

int main( void )
{
	ofstream out;

	out.open( "./resb.cpp" );
	if ( !out )
		return EXIT_FAILURE;

	out << endl << "#include <jackshit.h>" << endl;

	for ( int i = 0 ; i < 8 ; i++ )
	{
		out << endl << "byte core::rst" << i << "( void )" << endl;
		out << '{' << endl;
		out << HT << "mem[regs.w.sp -= 2] = ( word ) ( regs.w.pc + 3 );" << endl;
		out << HT << "regs.w.pc = 0x" << hex << i * 8 << ';' << endl;
		out << HT << "return 4;" << endl << '}' << endl;
	}
}
