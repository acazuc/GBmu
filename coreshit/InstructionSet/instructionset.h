
#ifndef INSTRUCTIONSET_H
#define INSTRUCTIONSET_H

// __NO INSTRUCTION__
static byte _blank( void );

// ldrr
static byte ldaa( void );
static byte ldab( void );
static byte ldac( void );
static byte ldad( void );
static byte ldae( void );
static byte ldah( void );
static byte ldal( void );
static byte ldba( void );
static byte ldbb( void );
static byte ldbc( void );
static byte ldbd( void );
static byte ldbe( void );
static byte ldbh( void );
static byte ldbl( void );
static byte ldca( void );
static byte ldcb( void );
static byte ldcc( void );
static byte ldcd( void );
static byte ldce( void );
static byte ldch( void );
static byte ldcl( void );
static byte ldda( void );
static byte lddb( void );
static byte lddc( void );
static byte lddd( void );
static byte ldde( void );
static byte lddh( void );
static byte lddl( void );
static byte ldea( void );
static byte ldeb( void );
static byte ldec( void );
static byte lded( void );
static byte ldee( void );
static byte ldeh( void );
static byte ldel( void );
static byte ldha( void );
static byte ldhb( void );
static byte ldhc( void );
static byte ldhd( void );
static byte ldhe( void );
static byte ldhh( void );
static byte ldhl( void );
static byte ldla( void );
static byte ldlb( void );
static byte ldlc( void );
static byte ldld( void );
static byte ldle( void );
static byte ldlh( void );
static byte ldll( void );

// ldrn
static byte ldan( void );
static byte ldbn( void );
static byte ldcn( void );
static byte lddn( void );
static byte lden( void );
static byte ldhn( void );
static byte ldln( void );

// ldrhl
static byte ldahl( void );
static byte ldbhl( void );
static byte ldchl( void );
static byte lddhl( void );
static byte ldehl( void );
static byte ldhhl( void );
static byte ldlhl( void );

// ldhlr
static byte ldhla( void );
static byte ldhlb( void );
static byte ldhlc( void );
static byte ldhld( void );
static byte ldhle( void );
static byte ldhlh( void );
static byte ldhll( void );

// ldhln
static byte ldhln( void );

// ldabc
static byte ldabc( void );

// ldade
static byte ldade( void );

// ldarc
static byte ldarc( void );

// ldrca
static byte ldrca( void );

// ldarn
static byte ldarn( void );

// ldrna
static byte ldrna( void );

// ldann
static byte ldann( void );

// ldnna
static byte ldnna( void );

// ldahli
static byte ldahli( void );

// ldahld
static byte ldahld( void );

// ldbca
static byte ldbca( void );

// lddea
static byte lddea( void );

// ldhlia
static byte ldhlia( void );

// ldhlda
static byte ldhlda( void );

// ldddnn
static byte ldbcnn( void );
static byte lddenn( void );
static byte ldhlnn( void );
static byte ldspnn( void );

// ldsphl
static byte ldsphl( void );

// push
static byte pushbc( void );
static byte pushde( void );
static byte pushhl( void );
static byte pushaf( void );

// pop
static byte popbc( void );
static byte popde( void );
static byte pophl( void );
static byte popaf( void );

// ldhl
static byte ldhlspe( void );

// ldnnsp
static byte ldnnsp( void );

// addar
static byte addaa( void );
static byte addab( void );
static byte addac( void );
static byte addad( void );
static byte addae( void );
static byte addah( void );
static byte addal( void );

// addan
static byte addan( void );

// addahl
static byte addahl( void );

// adcar
static byte adcaa( void );
static byte adcab( void );
static byte adcac( void );
static byte adcad( void );
static byte adcae( void );
static byte adcah( void );
static byte adcal( void );

// adcan
static byte adcan( void );

// adcahl
static byte adcahl( void );

// subar
static byte subaa( void );
static byte subab( void );
static byte subac( void );
static byte subad( void );
static byte subae( void );
static byte subah( void );
static byte subal( void );

// suban
static byte suban( void );

// subahl
static byte subahl( void );

// sbcar
static byte sbcaa( void );
static byte sbcab( void );
static byte sbcac( void );
static byte sbcad( void );
static byte sbcae( void );
static byte sbcah( void );
static byte sbcal( void );

// sbcan
static byte sbcan( void );

// sbcahl
static byte sbcahl( void );

// andr
static byte anda( void );
static byte andb( void );
static byte andc( void );
static byte andd( void );
static byte ande( void );
static byte andh( void );
static byte andl( void );

// andn
static byte andn( void );

// andhl
static byte andhl( void );

// orr
static byte ora( void );
static byte orb( void );
static byte orc( void );
static byte ord( void );
static byte ore( void );
static byte orh( void );
static byte orl( void );

// orn
static byte orn( void );

// orhl
static byte orhl( void );

// xorr
static byte xora( void );
static byte xorb( void );
static byte xorc( void );
static byte xord( void );
static byte xore( void );
static byte xorh( void );
static byte xorl( void );

// xorn
static byte xorn( void );

// xorhl
static byte xorhl( void );

// cpr
static byte cpa( void );
static byte cpb( void );
static byte cpc( void );
static byte cpd( void );
static byte cpe( void );
static byte cph( void );
static byte cpl( void );

// cpn
static byte cpn( void );

// cphl
static byte cphl( void );

// incr
static byte inca( void );
static byte incb( void );
static byte incc( void );
static byte incd( void );
static byte ince( void );
static byte inch( void );
static byte incl( void );

// inchl
static byte inchl( void );

// decr
static byte deca( void );
static byte decb( void );
static byte decc( void );
static byte decd( void );
static byte dece( void );
static byte dech( void );
static byte decl( void );

// dechl
static byte dechl( void );

// addhlss
static byte addhlbc( void );
static byte addhlde( void );
static byte addhlhl( void );
static byte addhlsp( void );

// addspe
static byte addspe( void );

////

// jp
static byte jp( void );

// jpcc
static byte jpnz( void );
static byte jpz( void );
static byte jpnc( void );
static byte jpc( void );

// jr
static byte jr( void );

// jrcc
static byte jrnz( void );
static byte jrz( void );
static byte jrnc( void );
static byte jrc( void );

////

// nop
static byte nop( void );

#endif
