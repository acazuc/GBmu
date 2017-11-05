
#include <capsule.h>

bool caps::ring::add( rway way, const void *data )
{
	struct rlink *link;

	if ( ( way != RIGHT ) && ( way != LEFT ) )
		return false;
	if ( !( link = ( struct rlink * ) malloc( sizeof ( struct rlink ) ) ) )
		return false;
	if ( !( (*link).data = malloc( datalen ) ) )
		return false;
	memcpy( (*link).data, data, datalen );
	perimeter++;
	if ( curlink == NULL )
	{
		(*link).left = link;
		(*link).right = link;
		curlink = link;
		return true;
	}
	if ( way == RIGHT )
	{
		(*link).left = curlink;
		(*link).right = (*curlink).right;
		(*(*curlink).right).left = link;
		(*curlink).right = link;
		curlink = (*curlink).right;
	}
	else
	{
		(*link).right = curlink;
		(*link).left = (*curlink).left;
		(*(*curlink).left).right = link;
		(*curlink).left = link;
		curlink = (*curlink).left;
	}
	return true;
}
