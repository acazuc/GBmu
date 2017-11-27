/*************************************
**                                  **
**      Capsule : Magic Table       **
**         ( unfinished )           **
**                                  **
**       Sweet Mare Software        **
**                                  **
*************************************/

#include <capsule.h>

bool caps::magtab::get( const char *key, void *data )
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
	memcpy( data, *(*stage).next, datalen );
	return true;
}
