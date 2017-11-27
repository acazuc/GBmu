/*************************************
**                                  **
**         Capsule : Ring           **
**                                  **
**       Sweet Mare Software        **
**                                  **
*************************************/

#include <capsule.h>

bool caps::ring::jump( const void *addr )
{
	if ( curlink == NULL )
		return false;
	curlink = ( struct rlink * ) addr;
	return true;
}
