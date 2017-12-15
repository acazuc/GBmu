{
	"sra X",
	2,
	&sraX
},
//
byte core::sraX( void )
{
	if ( regs.b.X & 1 )
		regs.b.f = CYFLAG;
	else
		regs.b.f = 0;

	regs.b.X >>= 1;
	if ( regs.b.X & 64 )
		regs.b.X |= 128;

	ZUPDATE( regs.b.X );

	regs.w.pc++;
	return 2;
}
