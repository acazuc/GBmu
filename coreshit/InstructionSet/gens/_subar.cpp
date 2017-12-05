{
	"sub X",
	1,
	&subaX,
},
//
byte core::subaX( void )
{
	byte a;

	a = regs.b.a;
	regs.b.a -= regs.b.X;

	regs.b.f = 1;
	CARRYNEGUPDATE( a, regs.b.a );
	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 1;	
}
