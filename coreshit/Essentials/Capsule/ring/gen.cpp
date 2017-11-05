
#include <capsule.h>

caps::ring::ring( size_t len )
{
	perimeter = 0;
	datalen = len;
	mark_a = NULL;
	mark_b = NULL;
	mark_x = NULL;
	curlink = NULL;
	status = 0;
}
