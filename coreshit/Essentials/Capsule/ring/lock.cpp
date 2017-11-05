
#include <capsule.h>

void *caps::ring::lock( void )
{
	return curlink;
}
