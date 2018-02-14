
#include <jackshit.h>

byte core::daa( void )
{
	if ( regs.b.f & NFLAG )
	{

	}
	else
	{
		if ( regs.b.f & CYFLAG )
		{

		}
		else
		{
			if ( regs.b.f & HFLAG )
			{
				
			}
			else // N == 0, CY == 0, H == 0
			{
				if ( ( regs.b.a & 0x0f ) > 0x09 )
					regs.b.a += 0x06;
				if ( ( regs.b.a & 0xf0 ) > 0x90 )
				{
					regs.b.a += 0x60;
					regs.b.f |= CYFLAG;
				}
			}
		}
	
	}
}
