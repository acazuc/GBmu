/*************************************
**                                  **
**         Capsule : Ring           **
**                                  **
**       Sweet Mare Software        **
**                                  **
*************************************/

#include <capsule.h>

void *caps::ring::lock( void )
{
	return curlink;
}
