
#include <capsule.h>

bool caps::magtab::add( const char *key, const void *data )
{
	struct mtstage *stage;

	if ( !key || !data )
		return false;
	if ( !first )
	{
		if ( !( first = ( struct mtstage * ) malloc( sizeof ( struct mtstage ) ) ) )
			return false;
		*(*first).next = NULL;
		(*first).size = 0;
		memset( (*first).next, 0, sizeof ( struct mtstage *[256] ) );
		(*first).prev = NULL;
	}
	stage = first;
	while ( *key )
	{
		if ( !(*stage).next[*key] )
		{
			if ( !( (*stage).next[*key] = ( struct mtstage * ) malloc( sizeof ( struct mtstage ) ) ) )
				return false;
			*(*(*stage).next[*key]).next = NULL;
			(*(*stage).next[*key]).size = 0;
			memset( (*(*stage).next[*key]).next, 0, sizeof ( struct mtstage *[256] ) );
			(*(*stage).next[*key]).prev = stage;
			(*stage).size++;
		}
		stage = (*stage).next[*key++];
	}
	if ( *(*stage).next || !( *(*stage).next = ( struct mtstage * ) malloc( datalen ) ) )
		return false;
	memcpy( *(*stage).next, data, datalen );
	totalentries++;
	return true;
}
