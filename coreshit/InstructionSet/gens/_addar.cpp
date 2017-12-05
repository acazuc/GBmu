{
	"add a, X",
	1,
	&addaX,
},
//
byte core::addaX( void )
{
	byte a;

	a = regs.b.a;
	regs.b.a += regs.b.X;

	regs.b.f = 0;
	CARRYUPDATE( a, regs.b.a );
	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 1;	
}
