
#include <jackshit.h>

byte core::stop( void )
{
	if ( !mem[regs.w.pc + 1] )
	{
		if ( mem[KEY1] & 1 )
		{
			if ( x2speed )
			{
				x2speed = false;
				mem[KEY1] = 0;
			}
			else
			{
				x2speed = true;
				mem[KEY1] = 128;
			}
		}
		else
			state = CPU_STOP;
	}

	regs.w.pc += 2;
	return 1;
}
