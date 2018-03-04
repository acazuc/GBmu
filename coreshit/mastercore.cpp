
#include <jackshit.h>

//long ref::defperiode = PERIODE;
//long ref::defstart = 0x100;
scf ref::file;

long ref::periode = PERIODE;
long ref::start = 0x100;
long ref::debugstart = 0x0000;
long ref::debugend = 0xffff;
const char *ref::dmgbiospath = "./dmgbios.gb";
const char *ref::cgbbiospath = "./cgbbios.gbc";
long ref::gbtype = 0;

void ref::init( void )
{
	if ( !file.load( "./config.scf" ) )
		return;

	if ( file.test( "periode", SCF_INT ) )
		periode = file.getint( "periode" );

	if ( file.test( "startat", SCF_INT ) )
		start = file.getint( "startat" );

	if ( file.test( "debugstart", SCF_INT ) )
		debugstart = file.getint( "debugstart" );

	if ( file.test( "debugend", SCF_INT ) )
		debugend = file.getint( "debugend" );

	if ( file.test( "gbtype", SCF_INT ) )
	{
		gbtype = file.getint( "gbtype" );
		if ( ( gbtype > 2 ) || ( gbtype < 0 ) )
			gbtype = 0;
	}

	if ( file.test( "dmgbiospath", SCF_STRING ) )
		dmgbiospath = file.getstring( "dmgbiospath" );

	if ( file.test( "cgbbiospath", SCF_STRING ) )
		cgbbiospath = file.getstring( "cgbbiospath" );
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
	//cout << ' ' << PEACHY << core::getime() << ' ' << ( int ) core::mem[IF] << WHITE;
	cout << endl;
}

void stackdraw( void )
{
	word sp = core::getsp();

	while ( sp != 0xcfff )
	{
		cout << WHITE << '[' << PEACHY << ( word ) core::mem[sp] << WHITE << ']' << endl;
		sp += 2;
	}
}

void timer( void )
{
	static xword timer = { 0 };
	const word clockselect[4] = { 0b0000001000000000, 0b0000000000001000, 0b0000000000100000, 0b0000000010000000 };
	static bool delayedmux = false;
	static bool carry = false;
	bool mux;

	if ( carry )
	{
		core::mem.sysregs( TIMA ) = core::mem.sysregs( TMA );
		core::mem.sysregs( IF ) |= 0b00000100;
		carry = false;
	}

	if ( core::mem.divwritehappend() )
		timer.w = 0;
	timer.w++;
	core::mem.sysregs( DIV ) = timer.b.h;

	mux = ( core::mem.sysregs( TAC ) & 0b00000100 ? timer.w & clockselect[core::mem.sysregs( TAC ) & 3] : false );

	if ( !mux && delayedmux )
	{
		if ( core::mem.sysregs( TIMA ) == 0xff )
			carry = true;
		core::mem.sysregs( TIMA )++;
		/*cout << dec << "Time : " << timer.w << " Timer : " << ( core::mem.sysregs( TAC ) & 0b00000100 );
		  cout << " Chosen time : " << clockselect[core::mem.sysregs( TAC ) & 3];
		  cout << " Mux : " << mux << " NOT Mux : " << !mux << " Delayed Mux : " << delayedmux;
		  cout << " TIMA : " << ( int ) core::mem.sysregs( TIMA );
		  cout << " TMA : " << ( int ) core::mem.sysregs( TMA ) << endl;*/

	}

	/*if ( core::mem.sysregs( TAC ) & 0b00000100 )
	{*/
	//	cout << dec << "Time : " << timer.w << " Timer : " << ( core::mem.sysregs( TAC ) & 0b00000100 );
	//	cout << " Chosen time : " << clockselect[core::mem.sysregs( TAC ) & 3];
	//	cout << " Mux : " << mux << " NOT Mux : " << !mux << " Delayed Mux : " << delayedmux;
	//	cout << " TIMA : " << ( int ) core::mem.sysregs( TIMA ) << endl;
	//}

	delayedmux = mux;
}

void dmaoamtransfert( void )
{
	static word counter = 0;
	static xword addr;

	if ( counter )
	{
		if ( !--counter )
		{
			core::mem[DMA] = 0;
			core::mem.dmaswitchoff();
		}

		core::mem[0xfe00 | addr.b.l] = core::mem[addr.w];
		//cout << WHITE << '[' << PEACHY << hex << setw( 4 ) << addr.w << WHITE << "] >> [";
		//cout << CYAN << setw( 4 ) << ( 0xfe00 | addr.b.l ) << WHITE << "] : ";
		//cout << RED << setw( 2 ) << ( int ) core::mem[addr.w] << WHITE << endl;
		addr.b.l++;

		return;
	}

	if ( core::mem[DMA] )
	{
		core::mem.dmaswitchon();
		counter = 160;
		addr.b.h = core::mem[DMA];
		addr.b.l = 0;
	}
}

#define VDMA_OFF 0
#define VDMA_GENERAL 1
#define VDMA_HBLANK 2
#define VDMA_HBLANKWAIT 3

void dmavramtransfert( void )
{
	static byte state = VDMA_OFF;
	static byte count = 0x10;
	static byte laststat;
	static xword src;
	static xword dst;

	switch ( state )
	{
		case VDMA_OFF:
			if ( core::mem.hdma5writehappend() )
			{
				src.b.h = core::mem.sysregs( HDMA1 );
				src.b.l = core::mem.sysregs( HDMA2 ) & 0b11110000;

				dst.b.h = ( core::mem.sysregs( HDMA3 ) & 0b00011111 ) | 0x80;
				dst.b.l = core::mem.sysregs( HDMA4 ) & 0b11110000;

				if ( core::mem.sysregs( HDMA5 ) & 0b10000000 )
				{
					laststat = core::mem.sysregs( STAT ) & 0b00000011;
					state = VDMA_HBLANKWAIT;
				}
				else
				{
					state = VDMA_GENERAL;
					core::switchoff();
					goto vdmagen;
				}
			}
			break;

		case VDMA_GENERAL:
			/*cout << WHITE << '[' << PURPLE << hex << setw( 4 ) << src.w << WHITE << "] >> [";
			  cout << SPRING << setw( 4 ) << dst.w << WHITE << "] : ";
			  cout << YELLOW << setw( 2 ) << ( int ) core::mem[src.w] << WHITE << endl;*/

vdmagen:		if ( core::is2xspeed() )
			{
				core::mem[dst.w++] = core::mem[src.w++];
				count--;
			}
			else
			{
				core::mem[dst.w++] = core::mem[src.w++];
				core::mem[dst.w++] = core::mem[src.w++];
				count -= 2;
			}

			if ( !count )
			{
				count = 0x10;

				core::mem.sysregs( HDMA1 ) = src.b.h;
				core::mem.sysregs( HDMA2 ) = src.b.l;
				core::mem.sysregs( HDMA3 ) = dst.b.h;
				core::mem.sysregs( HDMA4 ) = dst.b.l;

				if ( !core::mem.sysregs( HDMA5 ) )
				{
					state = VDMA_OFF;
					core::switchon();
					break;
				}

				core::mem.sysregs( HDMA5 )--;
			}
			break;

		case VDMA_HBLANK:
			/*cout << WHITE << '[' << CYAN << hex << setw( 4 ) << src.w << WHITE << "] >> [";
			  cout << GREY << setw( 4 ) << dst.w << WHITE << "] : ";
			  cout << PEACHY << setw( 2 ) << ( int ) core::mem[src.w] << WHITE << endl;*/

			if ( core::is2xspeed() )
			{
				core::mem[dst.w++] = core::mem[src.w++];
				count--;
			}
			else
			{
				core::mem[dst.w++] = core::mem[src.w++];
				count--;
				if ( count )
				{
					core::mem[dst.w++] = core::mem[src.w++];
					count--;
				}
			}

			if ( !count )
			{
				count = 0x10;

				core::mem.sysregs( HDMA1 ) = src.b.h;
				core::mem.sysregs( HDMA2 ) = src.b.l;
				core::mem.sysregs( HDMA3 ) = dst.b.h;
				core::mem.sysregs( HDMA4 ) = dst.b.l;

				if ( !( core::mem.sysregs( HDMA5 ) & 0b01111111 ) )
				{
					core::mem.sysregs( HDMA5 ) = 0;
					state = VDMA_OFF;
					core::switchon();
					break;
				}

				core::mem.sysregs( HDMA5 )--;
				laststat = core::mem.sysregs( STAT ) & 0b00000011;
				state = VDMA_HBLANKWAIT;
				core::switchon();
			}
			break;

		case VDMA_HBLANKWAIT:
			if ( core::mem.hdma5writehappend() )
			{
				core::mem.sysregs( HDMA5 ) &= 0b01111111;
				state = VDMA_OFF;
				core::switchon();
			}

			if ( !( core::mem.sysregs( STAT ) & 0b00000011 ) && laststat )
			{
				state = VDMA_HBLANK;
				core::switchoff();
			}

			laststat = core::mem.sysregs( STAT ) & 0b00000011;
	}
}

void corerun( dword cycle )
{
	static bool display = false;

	//cycle *= 4; 

	while ( cycle-- )
	{
		const char *s;
		struct timespec stime;
		word pc;

		timer();
		pc = core::getpc();
		if ( s = core::cue() )
		{
			if ( display )
			{
				statedisplay( s, pc );
				//stackdraw();
				stime.tv_sec = 0;
				stime.tv_nsec = ref::periode; 
				nanosleep( &stime, NULL );
				if ( pc == ref::debugend )
					display = false;
			}
			else if ( pc == ref::debugstart )
			{
				display = true;
				statedisplay( s, pc );
			}
		}

		dmaoamtransfert();
		dmavramtransfert();

		//stime.tv_sec = 0;
		//stime.tv_nsec = ref::periode; 
		//nanosleep( &stime, NULL );
	}
}

void corereset( void )
{
	core::init();
	core::mem.ramclear();
}

void corereset( char *rom )
{
	core::init();
	core::mem.ramclear();
	core::mem.romload( rom );
	switch ( ref::gbtype )
	{
		case 0:
			core::mem.biosload( core::mem.iscgb() ? ref::cgbbiospath : ref::dmgbiospath );
			break;
		case 1:
			core::mem.biosload( ref::dmgbiospath );
			break;
		case 2:
			core::mem.biosload( ref::cgbbiospath );
			break;
	}
}

void coremaster( void )
{
	ref::init();
	core::init();
}

void coremaster( char *rom )
{
	ref::init();
	core::init();
	core::mem.romload( rom );
	switch ( ref::gbtype )
	{
		case 0:
			core::mem.biosload( core::mem.iscgb() ? ref::cgbbiospath : ref::dmgbiospath );
			break;
		case 1:
			core::mem.biosload( ref::dmgbiospath );
			break;
		case 2:
			core::mem.biosload( ref::cgbbiospath );
			break;
	}
}
