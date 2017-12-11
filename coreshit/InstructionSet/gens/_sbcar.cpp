{
	"sbc a, X",
	1,
	&sbcaX,
},
//
byte core::subaX( void )
{
	byte a;

	a = regs.b.a;
	regs.b.a -= regs.b.X;
	if ( regs.b.f & CYFLAG )
		regs.b.f--;

	regs.b.f = NFLAG;
	CARRYREVUPDATE( a, regs.b.a );
	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 1;	
}
