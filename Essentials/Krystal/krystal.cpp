/************************************
**                                 **
**             Krystal             **
**	( development build )      **
**                                 **
**       Sweet Mare Software       **
**       15/01/18 - --/--/18       **
**                                 **
************************************/

#include <krystal.h>
#include <signal.h>
#include <chrono>
#include <unistd.h>
#include <cmath>

#include <iostream>

using namespace std;
using namespace chrono;

long krystal::basecount = 0;

void *krystal::clock( krystal &inst )
{
	register dword dec;

	for ( ; ; )
	{
		dec = inst.countdown;
		while ( --dec );
		inst.cycle++;
	}
}

dword offset( dword should, dword was )
{
	if ( should > was )
		return 100 - ( ( was * 100 ) / should );
	else if ( !was )
		return 0;
	else
		return 100 - ( ( should * 100 ) / was );
}

void *krystal::ajust( krystal &inst )
{
	high_resolution_clock::time_point t1, t2;
	dword cyc1, cyc2, shouldbecyc, wascyc;
	useconds_t tosleep = 500000;

	for ( ; ; )
	{
		cyc1 = inst.cycle;
		t1 = high_resolution_clock::now();
		usleep( tosleep );
		cyc2 = inst.cycle;
		t2 = high_resolution_clock::now();

		shouldbecyc = ( ( float ) duration_cast<nanoseconds>( t2 - t1 ).count() / ( float ) 1000000000 ) * ( float ) ( 1000000000 / inst.targetper );
		wascyc = cyc2 - cyc1;

		int mooga = offset( shouldbecyc, wascyc );
		//cout << "Should been : " << shouldbecyc << " Was : " << cyc2 - cyc1 << " Off by : " << mooga << '%' << endl;

		if ( mooga < 10 )
		{
			if ( wascyc < shouldbecyc )
				inst.countdown--;
			else
				inst.countdown++;
			tosleep = 50000;
		}
		else
		{
			inst.countdown = ( ( float ) ( cyc2 - cyc1 ) / ( float ) shouldbecyc ) * ( float ) inst.countdown;
			tosleep = 500000;
		}
		//cout << "Countdown : " << inst.countdown << endl;
	}
}

void krystal::calibrate( void )
{
	high_resolution_clock::time_point t1, t2;
	register dword dec;

	dec = KRYSTAL_CALIBRATION_CYCLES_TO_CONSUME;
	t1 = high_resolution_clock::now();
	while ( --dec );
	t2 = high_resolution_clock::now();
	basecount = duration_cast<nanoseconds>( t2 - t1 ).count();
	cout << "Basecount : " << basecount << endl;
}

krystal::krystal( void )
{
	pthread_attr_init( &attr );
	thread = -1;
	cycle = 0;
	state = false;

	if ( !basecount )
		calibrate();
}

krystal::krystal( dword freq )
{
	pthread_attr_init( &attr );
	cycle = 0;
	state = false;
	targetper = 1000000000 / freq;

	if ( !basecount )
		calibrate();

	countdown = ( ( float ) targetper / ( float ) basecount ) * ( float ) KRYSTAL_CALIBRATION_CYCLES_TO_CONSUME;
	cout << "Countdown : " << countdown << endl;
	pthread_create( &thread, &attr, ( void *(*)( void * ) ) &clock, this );
	pthread_create( &thread2, &attr, ( void *(*)( void * ) ) &ajust, this );
}

bool krystal::setfreq( dword freq )
{
	if ( freq && ( freq <= 1000000000 ) )
	{
		targetper = 1000000000 / freq;
		return true;
	}
	return false;	
}

bool krystal::setper( dword per )
{
	if ( per && ( per <= 1000000000 ) )
	{
		targetper = per;
		return true;
	}
	return false;
}

bool krystal::start( void )
{
	if ( thread == -1 )
	{
		if ( !basecount )
			calibrate();

		countdown = ( ( float ) targetper / ( float ) basecount ) * ( float ) KRYSTAL_CALIBRATION_CYCLES_TO_CONSUME;
		cout << "Countdown : " << countdown << endl;
		if ( !pthread_create( &thread, &attr, ( void *(*)( void * ) ) &clock, this ) )
			return true;
		return false;
	}
	return true;
}

void krystal::stop( void )
{
	if ( thread != -1 )
		pthread_kill( thread, SIGTERM );
}

krystal::~krystal( void )
{
	if ( thread != -1 )
		pthread_kill( thread, SIGTERM );
	if ( thread2 != -1 )
		pthread_kill( thread2, SIGTERM );
	pthread_attr_destroy( &attr );
}
