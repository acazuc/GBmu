/*************************************
**                                  **
**         Capsule : Ring           **
**                                  **
**       Sweet Mare Software        **
**                                  **
*************************************/

#include <capsule.h>

bool caps::ring::spin( rway way, size_t nb )
{
	if ( curlink == NULL )
		return false;
	if ( way == RIGHT )
	{
		while ( nb-- )
			curlink = (*curlink).right;
		return true;
	}
	else if ( way == LEFT )
	{
		while ( nb-- )
			curlink = (*curlink).left;
		return true;
	}
	return false;
}
