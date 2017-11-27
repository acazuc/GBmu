/*************************************
**                                  **
**         Capsule : Ring           **
**                                  **
**       Sweet Mare Software        **
**                                  **
*************************************/

#include <capsule.h>

bool caps::ring::put( rway way, const void *data )
{
	if ( curlink == NULL )
		return false;
	if ( way != FRONT )
		curlink = ( way == RIGHT ? (*curlink).right : (*curlink).left );
	memcpy( (*curlink).data, data, datalen );
	return true;
}
