
#include <capsule.h>

bool caps::magtab::put( const char *key, const void *data )
{
	struct mtstage *stage;

	if ( !key || !data || !first )
		return false;
	stage = first;
	while ( *key )
	{
		if ( !(*stage).next[*key] )
			return false;
		stage = (*stage).next[*key++];
	}
	if ( !*(*stage).next )
		return false;
	memcpy( *(*stage).next, data, datalen );
	return true;
}
