/*************************************
**                                  **
**      Capsule : Magic Table       **
**         ( unfinished )           **
**                                  **
**       Sweet Mare Software        **
**                                  **
*************************************/

#include <capsule.h>

caps::magtab::magtab( size_t size )
{
	datalen = size;
	totalentries = 0;
	laylevel = 0;
	laystack = NULL;
	mark_x = NULL;
	first = NULL;
	allstarlastkey = NULL;
	status = 0;
}
