/*************************************
**                                  **
**         Capsule : Ring           **
**                                  **
**       Sweet Mare Software        **
**                                  **
*************************************/

#include <capsule.h>

bool caps::ring::get( rway way, void *data )
{
	if ( curlink == NULL )
		return false;
	if ( way != FRONT )
		curlink = ( way == RIGHT ? (*curlink).right : (*curlink).left );
	memcpy( data, (*curlink).data, datalen );
	return true;
}
