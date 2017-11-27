/*************************************
**                                  **
**         Capsule : Ring           **
**                                  **
**       Sweet Mare Software        **
**                                  **
*************************************/

#include <capsule.h>

bool caps::ring::clear( void )
{
	struct rlink *start;

	if ( curlink == NULL )
		return false;
	start = (*curlink).left;
	while ( curlink != start )
	{
		curlink = (*curlink).right;
		free( (*(*curlink).left).data );
		free( (*curlink).left );
	}
	free( (*curlink).data );
	free( curlink );
	perimeter = 0;
	status = 0;
	mark_x = NULL;
	curlink = NULL;
	return true;
}
