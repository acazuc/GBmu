
#include <jackshit.h>

int main( int ac, char **av )
{
	if ( ac < 2 )
	{
		cout << RED << "Give me a rom, you shit !" << DEFAULT << endl;
		return EXIT_FAILURE;
	}

	core::init();
	core::mem.romload( *av );

	for ( ; ; )
	{
		cout << SKY << core::getpc() << WHITE << " : " << core::cue() << endl;
	}
}
