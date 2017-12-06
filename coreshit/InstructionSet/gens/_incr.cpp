{
	"inc X",
	1,
	&incX,
},
//
byte core::incX( void )
{
	byte X;

	X = regs.b.X++;

	regs.b.f &= ~NFLAG;
	HUPDATE( X, regs.b.X );
	ZUPDATE( regs.b.X );

	regs.w.pc++;
	return 1;	
}
