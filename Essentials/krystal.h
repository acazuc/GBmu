/*************************************
**                                  **
**             Krystal              **
**      ( development build )       **
**                                  **
**       Sweet Mare Software        **
**       15/01/18 - --/--/18        **
**                                  **
*************************************/

#ifndef KRYSTAL_H
#define KRYSTAL_H

#include <asmtypes.h>
#include <pthread.h>

#define KRYSTAL_CALIBRATION_CYCLES_TO_CONSUME 1000000000

class krystal
{
	private:
		pthread_t thread;
		pthread_t thread2;
		pthread_attr_t attr;
		volatile long targetper;
		static long basecount;
		volatile dword countdown;

		static void *clock( krystal &inst );
		static void *ajust( krystal &inst );
		static void calibrate( void );
	public:
		volatile dword cycle;
		volatile bool state;

		// Constructor
		krystal( void );
		krystal( dword freq );

		// Setters
		bool setfreq( dword freq );
		bool setper( dword per );

		// Controls
		bool start( void );
		void stop( void );

		// Destructor
		~krystal( void );
};

#endif
