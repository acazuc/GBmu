
#ifndef JACKSHIT_H
#define JACKSHIT_H

class core
{
	private:
		static union
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
		}
		regs;

		struct instruction
		{
			char *mnemonic;
			byte cycles;
			void (*function)( void );
		};

		static struct instruction *next;

	public:
		static memboy mem;
		static struct instruction decode[256];
}

#endif
