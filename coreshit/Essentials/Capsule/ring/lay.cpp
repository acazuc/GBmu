/*************************************
**                                  **
**         Capsule : Ring           **
**                                  **
**       Sweet Mare Software        **
**                                  **
*************************************/

#include <capsule.h>

bool caps::ring::lay( rway way, void *data )
{
	if ( curlink == NULL )
		return false;
	if ( status != 1 )
	{
		if ( status == -1 )
		{
			status = 0;
			return false;
		}
		status = 1;
		mark_x = curlink;
	}
	curlink = ( way == RIGHT ? (*curlink).right : (*curlink).left );
	if ( curlink == mark_x )
		status = -1;
	memcpy( data, (*curlink).data, datalen );
	return true;
}
