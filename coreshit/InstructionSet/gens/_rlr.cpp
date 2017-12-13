{
	"rl X",
	1,
	&rlrX
},
//
byte core::rlrX( void )
{
	byte cy;

	if ( regs.b.X & 128 )
		cy = CYFLAG;
	else
		cy = 0;

	if ( regs.b.f & CYFLAG )
		regs.b.X = ( regs.b.X << 1 ) + 1;
	else
		regs.b.X <<= 1;

	regs.b.f = cy;
	ZUPDATE( regs.b.X );

	regs.w.pc++;
	return 1;
}
