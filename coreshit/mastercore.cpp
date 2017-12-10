
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
		word pc;

		pc = core::getpc();
		if ( s = core::cue() )
		{
			cout << GREY << "0x" << setfill( '0' ) << setw( 4 ) << std::hex << pc << WHITE << " : ";
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

					s = strchr( s2, 'n' );
					cout << WHITE;
					if ( !s )
						cout << s2;
					else
					{
						switch ( *( s + 1 ) )
						{
							case 'n':
								cout.write( s2, s - s2 );
								cout << FOAM << setfill( '0' ) << setw( 4 ) << ( word ) core::mem[pc + 1] << WHITE;
								cout << s + 2;
								break;
							case 'z':
							case 'c':
								cout << s2;
								break;
							default:
								cout.write( s2, s - s2 );
								cout << FOAM << setfill( '0' ) << setw( 2 ) << ( int ) core::mem[pc + 1] << WHITE;
								cout << s + 1;
						}
					}
				}
				cout << HT << HT;
	cout << GREY << 'A' << WHITE << '=' << FOAM << setw( 2 ) << ( int ) core::geta() << WHITE << ", ";
	cout << GREY << 'B' << WHITE << '=' << FOAM << setw( 2 ) << ( int ) core::getb() << WHITE << ", ";
	cout << GREY << 'C' << WHITE << '=' << FOAM << setw( 2 ) << ( int ) core::getc() << WHITE << ", ";
	cout << GREY << 'D' << WHITE << '=' << FOAM << setw( 2 ) << ( int ) core::getd() << WHITE << ", ";
	cout << GREY << 'E' << WHITE << '=' << FOAM << setw( 2 ) << ( int ) core::gete() << WHITE << ", ";
	cout << GREY << 'H' << WHITE << '=' << FOAM << setw( 2 ) << ( int ) core::geth() << WHITE << ", ";
	cout << GREY << 'L' << WHITE << '=' << FOAM << setw( 2 ) << ( int ) core::getl() << WHITE << ", ";
	cout << GREY << "SP" << WHITE << '=' << FOAM << setw( 4 ) << ( int ) core::getsp() << WHITE << ", ";

			}
			cout << endl;
		}

		stime.tv_sec = 0;
		stime.tv_nsec = PERIODE; 
		nanosleep( &stime, NULL );
	}
}
