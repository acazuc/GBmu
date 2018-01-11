{
	"swap X",
	2,
	swapX
}
//
byte core::swapX( void )
{
	regs.b.X = ( regs.b.X << 4 ) | ( regs.b.X >> 4 );

	regs.b.f = 0;
	ZUPDATE( regs.b.X );
	
	regs.w.pc++;
	return 2;
}
