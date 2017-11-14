
#ifndef JACKSHIT_H
#define JACKSHIT_H

#include <memboy.h>
#include <asmtypes.h>
#include <iostream>
#include <colors.h>
#include <cstring>

#include <ctime>

#define ZFLAG 0b10000000
#define NFLAG 0b01000000
#define HFLAG 0b00100000
#define CYFLAG 0b00010000

#define PERIODE 250000000

using namespace std;

class core
{
	private:
		union registers
		{
			struct
			{
				byte pch;
				byte pcl;
				byte sph;
				byte spl;
				byte a;
				byte f;
				byte b;
				byte c;
				byte d;
				byte e;
				byte h;
				byte l;
			}
			b;
			struct
			{
				word pc;
				word sp;
				word af;
				word bc;
				word de;
				word hl;
			}
			w;
			//byte id[sizeof name];
		};

		static union registers regs;

		struct instruction
		{
			const char *mnemonic;
			byte cycles;
			byte (*function)( void );
		};

		static byte cycle;
		static struct instruction *next;

		#include <InstructionSet/instructionset.h>
	public:
		static memboy mem;
		static struct instruction decode[256];

		// Initialiser
		static void init( void );

		// Control
		static const char *cue( void );

		// Getters
		static word getpc( void );
};

#endif
