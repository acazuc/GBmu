#ifndef CAPSULE_H
#define CAPSULE_H

#include <stdlib.h>
#include <string.h>

#define FRONT 0
#define RIGHT 1
#define LEFT 2

namespace caps
{
	// Ring

	typedef char rway;

	class ring
	{
		private:
			struct rlink
			{
				void *data;
				struct rlink *right;
				struct rlink *left;
			};

			size_t datalen;
			size_t perimeter;
			struct rlink *mark_a;
			struct rlink *mark_b;
			struct rlink *mark_x;
			struct rlink *curlink;
			unsigned char status;
		public:
			ring( size_t len );
			bool add( rway way, const void *data );
			bool get( rway way, void *data );
			bool spin( rway way, size_t nb );
			bool rem( rway way );
			bool put( rway way, const void *data );
			bool lay( rway way, void *data );
			size_t per();
			void *lock();
			bool jump( const void *addr );
			bool reset();
			bool clear();
			~ring( void );
	};

	// Magic Table

	class magtab
	{
		private:
			struct mtstage
			{
				struct mtstage *next[256];
				struct mtstage *prev;
				unsigned char size;
			};

			struct mtlaystack
			{
				unsigned char key;
				struct mtlaystack *prev;
			};

			size_t datalen;
			size_t totalentries;
			size_t laylevel;
			struct mtlaystack *laystack;
			struct mtstage *mark_x;
			struct mtstage *first;
			char *allstarlastkey;
			unsigned char status;
		public:
			magtab( size_t size );
			bool add( const char *key, const void *data );
			//bool rem( const char *key );
			bool get( const char *key, void *data );
			bool put( const char *key, const void *data );
			char *allstar( void *data );
			//~magtab( void );
	};
}

#endif
