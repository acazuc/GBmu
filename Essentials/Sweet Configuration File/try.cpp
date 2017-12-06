
#include <scf.h>
#include <iostream>

using namespace std;

#define YAY cout << __FILE__ << ':' << __LINE__ << " > Breakpoint passed yay :3" << endl

int main( int ac, char **av )
{
	scf yay;

	yay.load( "yay.scf" );

	long &aja = yay.getint( "aja" );
	bool &mii = yay.getbool( "mii" );
	char *&mooga = yay.getstring( "mooga" );

	cout << aja << endl << mii << endl << mooga << endl;

	aja = 61;
	mii = true;
	mooga = "La bite a mamie";

	yay.save( "aja.scf" );

	return 0;
}
