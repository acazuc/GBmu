/*************************************
**                                  **
**     Sweet Configuration File     **
**	     ( 1st try )            **
**                                  **
**       Sweet Mare Software        **
**       05/09/17 - --/--/17        **
**                                  **
*************************************/

#ifndef SCF_H
#define SCF_H

#include <capsule.h>
#include <fstream>
#include <string>
#include <ascii.h>
#include <cstring>
#include <cstdlib>
#include <cctype>

using namespace std;
using namespace caps;

#define SCF_NONE 0
#define SCF_INT 1
#define SCF_BOOL 2
#define SCF_STRING 4
#define SCF_CHAIN 8

#define SCFERR ( unsigned char ) 0

class scf
{
	private:
		struct entry
		{
			int type;
			union
			{
				long nb;
				bool bo;
				char *str;
				void *chain;
			}
			data;
		};

		ifstream src;
		ofstream dst;
		magtab table;
		string ckey;
		string centry;

		char getnextchar( void );
		void createvar( void );
	public:
		// Constructors
		scf( void );

		// I/O Operations
		bool load( const char *path );
		bool save( const char *path );

		// Checkers
		int test( const char *key );
		bool test( const char *key, int type );
		bool test( const char *key, const char *chain );

		// Raw Getters
		void *operator []( const char *key );
		void *get( const char *key );
		void *get( const char *key, int type );
		void *get( const char *key, const char *chain );

		// Spec Getters
		long &getint( const char *key );
		bool &getbool( const char *key );
		char *&getstring( const char *key );

		// Setters
		bool set( const char *key, int val );
		bool set( const char *key, bool val );
		bool set( const char *key, char *val );

		void clear( void );

		// Destructor
		~scf( void );
};

#endif
