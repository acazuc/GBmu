{
	"and X",
	1,
	&andX,
},
//
byte core::andX( void )
{
	regs.b.a &= regs.b.X;

	regs.b.f = HFLAG;
	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 1;
}
