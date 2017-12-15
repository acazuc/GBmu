{
	"sla X",
	2,
	&slaX
},
//
byte core::slaX( void )
{
	if ( regs.b.X & 128 )
		regs.b.f = CYFLAG;
	else
		regs.b.f = 0;

	regs.b.X <<= 1;

	ZUPDATE( regs.b.X );

	regs.w.pc++;
	return 2;
}
