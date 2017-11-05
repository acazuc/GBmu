
#include <capsule.h>

bool caps::ring::rem( rway way )
{
	struct rlink *swap;

	if ( curlink == NULL )
		return false;
	perimeter--;
	if ( (*curlink).left == curlink && (*curlink).right == curlink )
	{
		free( (*curlink).data );
		free( curlink );
		curlink = NULL;
		return true;
	}
	(*(*curlink).right).left = (*curlink).left;
	(*(*curlink).left).right = (*curlink).right;
	swap = ( way == RIGHT ? (*curlink).right : (*curlink).left );
	free( (*curlink).data );
	free( curlink );
	curlink = swap;
	return true;
}
