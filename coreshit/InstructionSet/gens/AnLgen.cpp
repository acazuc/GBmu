
#include <iostream>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fstream>
#include <ascii.h>
#include <fcntl.h>
#include <colors.h>
#include <cstring>

using namespace std;

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

int main( int ac, char **av )
{
	int fd;
	char *addr;
	char *yay;
	char *end;
	struct stat bdts;

	if ( !*++av )
		return -1;

	if ( ( fd = open( *av, O_RDONLY ) ) == -1 )
	{
		cout << RED << "Can't open " << *av << LF;
		return -1;
	}
	if ( fstat( fd, &bdts ) )
	{
		cout << RED << "Can't stat " << *av << LF;
		return -1;
	}
	if ( ( addr = ( char * ) mmap( NULL, bdts.st_size, PROT_READ, MAP_PRIVATE, fd, 0 ) ) == MAP_FAILED )
	{
		cout << RED << "Can't map " << *av << LF;
		return -1;
	}
	close( fd );

	end = addr + bdts.st_size;

	if ( !( yay = strstr( addr, "//" ) ) )
		return -1;
	yay += 2;

	ofstream out;

	out.open( "./DONE.cpp" );
	if ( !out )
		return -1;

	out << endl << "#include <jackshit.h>" << endl;

	for ( int i = 0 ; i < 7 ; i++ )
	{
		char *aja = yay;

		while ( aja != end )
		{
			if ( *aja == 'X' )
				out << regs[i].letter;
			else
				out << *aja;
			aja++;
		}
	}

	out << endl << endl;

	end = yay - 2;

	for ( int i = 0 ; i < 8 ; i++ )
	{
		char *aja = addr;

		while ( aja != end )
		{
			if ( *aja == 'X' )
				if ( regs2[i] )
					out << regs2[i];
				else
					out << "(hl)";
			else
				out << *aja;
			aja++;
		}
	}


	return 0;
}
