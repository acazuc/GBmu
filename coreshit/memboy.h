
#ifndef MEMBOY_H
#define MEMBOY_H

#include <asmtypes.h>
#include <fstream>

#define YAY cout << __FILE__ << ':' << __LINE__ << ": Breakpoint passed yay :3" << endl;

#define P1 0xFF00
#define JOYP 0xFF00
#define SB 0xFF01
#define SC 0xFF02
#define DIV 0xFF04
#define TIMA 0xFF05
#define TMA 0xFF06
#define TAC 0xFF07
#define IF 0xFF0F
#define NR10 0xFF10
#define NR11 0xFF11
#define NR12 0xFF12
#define NR13 0xFF13
#define NR14 0xFF14
#define NR21 0xFF16
#define NR22 0xFF17
#define NR23 0xFF18
#define NR24 0xFF19
#define NR30 0xFF1A
#define NR31 0xFF1B
#define NR32 0xFF1C
#define NR33 0xFF1D
#define NR34 0xFF1E
#define NR41 0xFF20
#define NR42 0xFF21
#define NR43 0xFF22
#define NR44 0xFF23
#define NR50 0xFF24
#define NR51 0xFF25
#define NR52 0xFF26
#define KEY1 0xFF4D
#define VBK 0xFF4F // Switch bank 1 from 0x8000 to 0x9FFF
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
#define KEY1 0xFF4D
#define RBK 0xFF50
#define HDMA1 0xFF51
#define HDMA2 0xFF52
#define HDMA3 0xFF53
#define HDMA4 0xFF54
#define HDMA5 0xFF55
#define RP 0xFF56
#define BCPS 0xFF68
#define BCPD 0xFF69
#define OCPS 0xFF6A
#define OCPD 0xFF6B
#define SVBK 0xFF70 // Switch bank 1 to 7 from 0xD000 to 0xDFFF
#define PCM12 0xFF76
#define PCM34 0xFF77
#define IE 0xFFFF

//#define OAM FE00~FE9F
//#define NR 0xFF10~FF26
//#define RAM 0xFF30~FF3F

#define MEMBOY_MAXSTACK 8
#define MEMREF_MAXSTACK 8

using namespace std;

union xword
{
	word w;
	struct
	{
		byte l;
		byte h;
	}
	b;
};

class memboy
{
	private:
		// Memory Maps
		byte *map;
		byte *bank1chardts;
		byte *svbk2to7;
		byte *rombank;
		byte *romxtend;

		// Hardware Registers
		byte joyparrows;
		byte joypbuttons;

		byte cgbbgpalette[64];
		byte cgbsppalette[64];

		// Locks
		bool dmalock;

		class memref
		{
			friend class memboy;

			private:
				memboy *ref;
				byte *addr;
				void ( memboy::*setfunc )( byte &addr, byte b );
				byte ( memboy::*getfunc )( byte &addr );
			public:
				void set( byte b );
				byte get( void );
		};

		memref rblock[MEMREF_MAXSTACK];
		int rblockid;

		class mempassthru
		{
			friend class memboy;

			private:
				memboy *ref;
				word ptchosen;
			public:
				operator byte( void );
				operator word( void );
				operator int( void );
				explicit operator char( void );
				explicit operator bool( void );
				mempassthru &operator =( byte b );
				mempassthru &operator =( word w );
				mempassthru &operator =( int n );
				mempassthru &operator =( mempassthru &m );
				mempassthru &operator |=( byte n );
				mempassthru &operator |=( int n );
				mempassthru &operator &=( byte n );
				mempassthru &operator &=( int n );
				mempassthru &operator ++( int n );
				mempassthru &operator --( int n );
		};

		mempassthru block[MEMBOY_MAXSTACK];
		int blockid;

		void classicset( byte &addr, byte b );
		byte classicget( byte &addr );

		void joypset( byte &addr, byte b );
		byte joypget( byte &addr );

		void bgpset( byte &addr, byte b );
		byte bgpget( byte &addr );
		void sppset( byte &addr, byte b );
		byte sppget( byte &addr );

		memref *deref( word addr );
	public:
		// Constructor
		memboy( void );

		// Accessers
		mempassthru &operator []( word addr );
		byte &cbank0( word addr );
		byte &cbank1( word addr );
		byte &sysregs( word addr );

		// Setters
		bool biosload( const char *path );
		bool romload( const char *path );
		void ramclear( void );

		void setarrowsstate( byte b );
		void setbuttonsstate( byte b );
		void dmaswitchon( void );
		void dmaswitchoff( void );

		// Getters
		byte getarrowsstate( void );
		byte getbuttonsstate( void );
		bool isdmalocked( void );

		// Destructor
		~memboy( void );
};

#endif
