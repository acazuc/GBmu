
#ifndef JACKSHIT_H
#define JACKSHIT_H

#include <memboy.h>
#include <asmtypes.h>
#include <iostream>
#include <colors.h>
#include <cstring>

using namespace std;

class core
{
	private:
		union registers
		{
			struct
			{
				word pc;
				word sp;
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
			void (*function)( void );
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
