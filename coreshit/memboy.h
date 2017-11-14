
#ifndef MEMBOY_H
#define MEMBOY_H

#include <asmtypes.h>
#include <fstream>

#define P1 0xFF00
#define SB 0xFF01
#define SC 0xFF02
#define DIV 0xFF04
#define TIMA 0xFF05
#define TMA 0xFF06
#define TAC 0xFF07
#define KEY1 0xFF4D
#define RP 0xFF56
#define VBK 0xFF4F // Switch bank 1 from 0x8000 to 0x9FFF
#define SVBK 0xFF70 // Switch bank 1 to 7 from 0xD000 to 0xDFFF
#define IF 0xFF0F
#define IE 0xFFFF
#define LCDC 0xFF40
#define STAT 0xFF41
#define SCY 0xFF42
#define SCX 0xFF43
#define LY 0xFF44
#define LYC 0xFF45
#define DMA 0xFF46
#define BGP 0xFF47
#define OBP0 0xFF48
#define OBP1 0xFF49
#define WY 0xFF4A
#define WX 0xFF4B
#define HDMA1 0xFF51
#define HDMA2 0xFF52
#define HDMA3 0xFF53
#define HDMA4 0xFF54
#define HDMA5 0xFF55
#define BCPS 0xFF68
#define BCPD 0xFF69
#define OCPS 0xFF6A
#define OCPD 0xFF6B

//#define OAM FE00~FE9F
//#define NR 0xFF10~FF26
//#define RAM 0xFF30~FF3F 

#define MEMBOY_MAXSTACK 8

using namespace std;

class memboy
{
	private:
		byte *map;
		byte *bank1chardts;
		byte *svbk2to7;

		class mempassthru
		{
			friend class memboy;

			private:
				byte *ptchosen;
				byte ptmode;
			public:
				operator byte( void );
				operator word( void );
				mempassthru &operator =( byte b );
				mempassthru &operator =( mempassthru &m );
				mempassthru &operator ++( int n );
				mempassthru &operator --( int n );
		};

		mempassthru block[MEMBOY_MAXSTACK];
		int blockid;
	public:
		// Constructor
		memboy( void );

		// Accessers
		mempassthru &operator []( word addr );
		byte &cbank0( word addr );
		byte &cbank1( word addr );

		// Setters
		bool romload( const char *path );

		// Destructor
		~memboy( void );
};

#endif
