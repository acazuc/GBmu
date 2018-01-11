
#include <jackshit.h>

//long ref::defperiode = PERIODE;
//long ref::defstart = 0x100;
scf ref::file;

long ref::periode = PERIODE;
long ref::start = 0x100;

void ref::init( void )
{
	if ( !file.load( "./config.scf" ) )
		return;

	if ( file.test( "periode", SCF_INT ) )
		periode = file.getint( "periode" );

	if ( file.test( "startat", SCF_INT ) )
		start = file.getint( "startat" );
}

void statedisplay( const char *s, word pc )
{
	const char *s2;
	size_t len;
	int tmp;

	cout << GREY << "0x" << setfill( '0' ) << setw( 4 ) << hex << pc << WHITE << " : ";
	if ( *s == '_' )
		cout << DARK << s;
	else
	{
		len = strlen( s );
		s2 = strchr( s, ' ' );
		cout << BLUE;
		if ( !s2 )
			cout << s;
		else
		{
			cout.write( s, s2 - s );

oncemore:		s = strchr( s2, 'n' );
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
						len += 2;
						break;
					case 'e':
						tmp = ( char ) core::mem[pc + 1] + 2;
						cout.write( s2, s - s2 );
						if ( tmp < 0 )
						{
							cout << '-' << FOAM << setfill( '0' ) << setw( 2 ) << -tmp << WHITE;
							len++;
						}
						else
							cout << FOAM << setfill( '0' ) << setw( 2 ) << tmp << WHITE;
						cout << s + 2;
						break;
					case 'z':
					case 'c':
						cout.write( s2, s - s2 + 2 );
						s2 = s + 2;
						goto oncemore;
					default:
						cout.write( s2, s - s2 );
						cout << FOAM << setfill( '0' ) << setw( 2 ) << ( int ) core::mem[pc + 1] << WHITE;
						cout << s + 1;
						len++;
				}
			}
		}
		for ( int i = 20 - len ; i != 0 ; i-- )
			cout << ' ';
		cout << GREY << 'A' << WHITE << '=' << FOAM << setw( 2 ) << ( int ) core::geta() << WHITE << ", ";
		cout << GREY << 'B' << WHITE << '=' << FOAM << setw( 2 ) << ( int ) core::getb() << WHITE << ", ";
		cout << GREY << 'C' << WHITE << '=' << FOAM << setw( 2 ) << ( int ) core::getc() << WHITE << ", ";
		cout << GREY << 'D' << WHITE << '=' << FOAM << setw( 2 ) << ( int ) core::getd() << WHITE << ", ";
		cout << GREY << 'E' << WHITE << '=' << FOAM << setw( 2 ) << ( int ) core::gete() << WHITE << ", ";
		cout << GREY << 'H' << WHITE << '=' << FOAM << setw( 2 ) << ( int ) core::geth() << WHITE << ", ";
		cout << GREY << 'L' << WHITE << '=' << FOAM << setw( 2 ) << ( int ) core::getl() << WHITE << ", ";
		cout << GREY << "SP" << WHITE << '=' << FOAM << setw( 4 ) << ( int ) core::getsp() << WHITE << ' ';

		cout << GREY << "FLAGS" << WHITE << ":[";
		cout << ( core::getflags() & ZFLAG ? FOAM : DARK ) << 'Z' << WHITE << '/';
		cout << ( core::getflags() & NFLAG ? FOAM : DARK ) << 'N' << WHITE << '/';
		cout << ( core::getflags() & HFLAG ? FOAM : DARK ) << 'H' << WHITE << '/';
		cout << ( core::getflags() & CYFLAG ? FOAM : DARK ) << "CY" << WHITE << ']';

	}
	cout << endl;
}

int main( int ac, char **av )
{
	if ( ac < 2 )
	{
		cout << RED << "Give me a rom, you shit !" << DEFAULT << endl;
		return EXIT_FAILURE;
	}

	ref::init();
	core::init();
	core::mem.romload( av[1] );

	for ( ; ; )
	{
		const char *s;
		struct timespec stime;
		word pc;

		pc = core::getpc();
		if ( s = core::cue() )
		{
			statedisplay( s, pc );
		}

		stime.tv_sec = 0;
		stime.tv_nsec = ref::periode; 
		nanosleep( &stime, NULL );
	}
}
