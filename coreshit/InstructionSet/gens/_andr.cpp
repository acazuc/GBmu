{
	"and X",
	1,
	&andX,
},
//
byte core::andX( void )
{
	regs.b.a &= regs.b.X;

	regs.b.f = 0;
	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 1;
}
