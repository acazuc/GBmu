
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

// ldac
static byte ldarc( void );

// ldca
static byte ldrca( void );

// jp
static byte jp( void );

// jpcc
static byte jpnz( void );
static byte jpz( void );
static byte jpnc( void );
static byte jpc( void );

// nop
static byte ins_nop( void );

#endif
