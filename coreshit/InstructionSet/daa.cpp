
#include <jackshit.h>

byte core::daa( void )
{
	/*cout << GREY << "FLAGS" << WHITE << ":[";
	cout << ( core::getflags() & ZFLAG ? FOAM : DARK ) << 'Z' << WHITE << '/';
	cout << ( core::getflags() & NFLAG ? FOAM : DARK ) << 'N' << WHITE << '/';
	cout << ( core::getflags() & HFLAG ? FOAM : DARK ) << 'H' << WHITE << '/';
	cout << ( core::getflags() & CYFLAG ? FOAM : DARK ) << "CY" << WHITE << ']';

	cout << ' ' << hex << ( word ) regs.b.a << " >> ";
*/
	if ( regs.b.f & NFLAG )
	{
		if ( regs.b.f & CYFLAG )
			regs.b.a -= 0x60;
		if ( regs.b.f & HFLAG )
			regs.b.a -= 0x06;
	}
	else
	{
		if ( ( regs.b.f & HFLAG ) || ( ( regs.b.a & 0x0f ) > 0x09 ) )
			regs.b.a += 0x06;

		if ( ( regs.b.f & CYFLAG ) || ( ( regs.b.a & 0xf0 ) > 0x90 ) )
		{
			regs.b.a += 0x60;
			regs.b.f |= CYFLAG;
		}
	}
	/*{
		// Lower Digit
		if ( ( regs.b.f & HFLAG ) && ( ( regs.b.a & 0x0f ) <= 0x03 ) )
			regs.b.a += 0x06;
		else if ( ( regs.b.a & 0x0f ) > 0x09 )
			regs.b.a += 0x06;

		// Higher Digit
		if ( ( regs.b.f & CYFLAG ) && ( ( regs.b.a & 0xf0 ) <= 0x03 ) )
		{
			regs.b.a += 0x60;
			regs.b.f |= CYFLAG;
		}
		else if ( ( regs.b.a & 0xf0 ) > 0x90 )
		{
			regs.b.a += 0x60;
			regs.b.f |= CYFLAG;
		}
	}
*/

	/*cout << hex << ( word ) regs.b.a << ' ';

	cout << GREY << "FLAGS" << WHITE << ":[";
	cout << ( core::getflags() & ZFLAG ? FOAM : DARK ) << 'Z' << WHITE << '/';
	cout << ( core::getflags() & NFLAG ? FOAM : DARK ) << 'N' << WHITE << '/';
	cout << ( core::getflags() & HFLAG ? FOAM : DARK ) << 'H' << WHITE << '/';
	cout << ( core::getflags() & CYFLAG ? FOAM : DARK ) << "CY" << WHITE << ']';
	cout << endl;
*/
	regs.b.f &= ~NFLAG;
	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 1;
}
