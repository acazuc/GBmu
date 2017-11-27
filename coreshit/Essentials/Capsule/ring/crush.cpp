/*************************************
**                                  **
**         Capsule : Ring           **
**                                  **
**       Sweet Mare Software        **
**                                  **
*************************************/

#include <capsule.h>

caps::ring::~ring( void )
{
	struct rlink *start;

	if ( curlink == NULL )
		return;
	start = (*curlink).left;
	while ( curlink != start )
	{
		curlink = (*curlink).right;
		free( (*(*curlink).left).data );
		free( (*curlink).left );
	}
	free( (*curlink).data );
	free( curlink );
}
