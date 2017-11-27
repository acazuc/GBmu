/*************************************
**                                  **
**      Capsule : Magic Table       **
**         ( unfinished )           **
**                                  **
**       Sweet Mare Software        **
**                                  **
*************************************/

#include <capsule.h>

char *caps::magtab::allstar( void *data )
{
	struct mtstage *stage;
	struct mtlaystack *tmp;

	if ( !data || !first )
		return NULL;
	if ( !status )
	{
		status = 1;
		mark_x = first;
		laylevel = 0;
		if ( !( laystack = ( struct mtlaystack * ) malloc( sizeof ( struct mtlaystack ) ) ) )
			return NULL;
		(*laystack).prev = NULL;
		(*laystack).key = 0;
	}
	stage = mark_x;
	if ( !(*laystack).key )
	{
		(*laystack).key++;
goup:		if ( *(*stage).next )
		{
			
			mark_x = stage;
			if ( allstarlastkey )
				free( allstarlastkey );
			if ( !( allstarlastkey = ( char * ) malloc( laylevel + 1 ) ) )
				return NULL;
			memcpy( data, *(*stage).next, datalen );
			allstarlastkey += laylevel;
			*allstarlastkey = 0;
			tmp = (*laystack).prev;
			while ( tmp )
			{
				*--allstarlastkey = (*tmp).key;
				tmp = (*tmp).prev;
			}
			return ( allstarlastkey );
		}
	}
godown:	while ( ++(*laystack).key )
		if ( (*stage).next[(*laystack).key] )
		{
			if ( !( tmp = ( struct mtlaystack * ) malloc( sizeof ( struct mtlaystack ) ) ) )
				return NULL;
			stage = (*stage).next[(*laystack).key];
			(*tmp).key = 1;
			(*tmp).prev = laystack;
			laystack = tmp;
			laylevel++;
			goto goup;
		}
	if ( (*stage).prev )
	{
		stage = (*stage).prev;
		tmp = laystack;
		laystack = (*laystack).prev;
		laylevel--;
		free( tmp );
		goto godown;
	}
	free( allstarlastkey );
	free( laystack );
	allstarlastkey = NULL;
	laystack = NULL;
	mark_x = NULL;
	status = 0;
	return NULL;
}
