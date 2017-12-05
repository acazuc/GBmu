{
	"adc a, X",
	1,
	&adcaX,
},
//
byte core::adcaX( void )
{
	byte a;

	a = regs.b.a;
	regs.b.a += regs.b.X;
	if ( regs.b.f & CYFLAG )
		regs.b.a++;

	regs.b.f = 0;
	CARRYUPDATE( a, regs.b.a );
	ZUPDATE( regs.b.a );

	regs.w.pc++;
	return 1;	
}
