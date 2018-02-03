
#include <iostream>
#include "../krystal.h"
#include <chrono>

using namespace std;
using namespace chrono;

int main( )
{
	dword cycle;

	cout << "Calibrating clock ..." << endl;
	krystal clock( 8000000 );
	cout << "Ok !" << endl;

	high_resolution_clock::time_point t1, t2;

	t1 = high_resolution_clock::now();
	for ( ; ; )
	{
		if ( !( ( cycle = clock.cycle ) % 8000000 ) )
		{
			t2 = high_resolution_clock::now();
			cout << cycle << " : " << duration_cast<nanoseconds>( t2 - t1 ).count() << endl;
			t1 = high_resolution_clock::now();
		}
		while ( cycle == clock.cycle );
	}
}
