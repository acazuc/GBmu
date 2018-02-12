{
	"cp X",
	1,
	&cpX,
},
//
byte core::cpX( void )
{
	byte a;

	a = regs.b.a - regs.b.X;

	regs.b.f = NFLAG;
	CARRYREVUPDATE( regs.b.a, a );
	ZUPDATE( a );

	regs.w.pc++;
	return 1;	
}
