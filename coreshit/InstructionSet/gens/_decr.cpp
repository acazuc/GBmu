{
	"dec X",
	1,
	&decX,
},
//
byte core::decX( void )
{
	byte X;

	X = regs.b.X--;

	regs.b.f |= NFLAG;
	HREVUPDATE( X, regs.b.X );
	ZUPDATE( regs.b.X );

	regs.w.pc++;
	return 1;
}
