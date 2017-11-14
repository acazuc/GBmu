
#include <jackshit.h>

int main( int ac, char **av )
{
	if ( ac < 2 )
	{
		cout << RED << "Give me a rom, you shit !" << DEFAULT << endl;
		return EXIT_FAILURE;
	}

	core::init();
	core::mem.romload( av[1] );

	for ( ; ; )
	{
		const char *s;
		const char *s2;
		struct timespec stime;

		cout << GREY << std::hex << core::getpc() << WHITE << " : ";
		if ( s = core::cue() )
		{
			if ( *s == '_' )
				cout << DARK << s;
			else
			{
				s2 = strchr( s, ' ' );
				cout << BLUE;
				if ( !s2 )
					cout << s;
				else
				{
					cout.write( s, s2 - s );
					cout << WHITE << s2;
				}
			}
		}
		cout << endl;

		stime.tv_sec = 0;
		stime.tv_nsec = PERIODE; 
		nanosleep( &stime, NULL );
	}
}
