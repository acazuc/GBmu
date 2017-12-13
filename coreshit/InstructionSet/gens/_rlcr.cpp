{
	"rlc X",
	1,
	&rlcrX
},
//
byte core::rlcrX( void )
{
	if ( regs.b.X & 128 )
	{
		regs.b.X = ( regs.b.X << 1 ) + 1;
		regs.b.f = CYFLAG;
	}
	else
	{
		regs.b.X <<= 1;
		regs.b.f = 0;
	}

	ZUPDATE( regs.b.X );

	regs.w.pc++;
	return 1;
}
