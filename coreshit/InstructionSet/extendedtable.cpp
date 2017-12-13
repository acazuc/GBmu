
#include <jackshit.h>

struct core::instruction core::extdec[256] =
{
	// 0
	{
		"rlc b",
		1,
		&rlcrb
	},
	{
		"rlc c",
		1,
		&rlcrc
	},
	{
		"rlc d",
		1,
		&rlcrd
	},
	{
		"rlc e",
		1,
		&rlcre
	},
	{
		"rlc h",
		1,
		&rlcrh
	},
	{
		"rlc l",
		1,
		&rlcrl
	},
	{
		"rlc (hl)",
		1,
		&rlchl
	},
	{
		"rlc a",
		1,
		&rlcra
	},
	{
		"rrc b",
		1,
		&rrcrb
	},
	{
		"rrc c",
		1,
		&rrcrc
	},

	// 10
	{
		"rrc d",
		1,
		&rrcrd
	},
	{
		"rrc e",
		1,
		&rrcre
	},
	{
		"rrc h",
		1,
		&rrcrh
	},
	{
		"rrc l",
		1,
		&rrcrl
	},
	{
		"rrc (hl)",
		1,
		&rrchl
	},
	{
		"rrc a",
		1,
		&rrcra
	},
	{
		"rl b",
		1,
		&rlrb
	},
	{
		"rl c",
		1,
		&rlrc
	},
	{
		"rl d",
		1,
		&rlrd
	},
	{
		"rl e",
		1,
		&rlre
	},

	// 20
	{
		"rl h",
		1,
		&rlrh
	},
	{
		"rl l",
		1,
		&rlrl
	},
	{
		"rl (hl)",
		1,
		&rlhl
	},
	{
		"rl a",
		1,
		&rlra
	},
	{
		"rr b",
		1,
		&rrrb
	},
	{
		"rr c",
		1,
		&rrrc
	},
	{
		"rr d",
		1,
		&rrrd
	},
	{
		"rr e",
		1,
		&rrre
	},
	{
		"rr h",
		1,
		&rrrh
	},
	{
		"rr l",
		1,
		&rrrl
	},

	// 30
	{
		"rr (hl)",
		1,
		&rrhl
	},
	{
		"rr a",
		1,
		&rrra
	},

	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},

	// 40
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},

	// 50
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},

	// 60
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"bit 0, b",
		2,
		&bit0b
	},
	{
		"bit 0, c",
		2,
		&bit0c
	},
	{
		"bit 0, d",
		2,
		&bit0d
	},
	{
		"bit 0, e",
		2,
		&bit0e
	},
	{
		"bit 0, h",
		2,
		&bit0h
	},
	{
		"bit 0, l",
		2,
		&bit0l
	},

	// 70
	{
		"bit 0, (hl)",
		3,
		&bit0hl
	},
	{
		"bit 0, a",
		2,
		&bit0a
	},
	{
		"bit 1, b",
		2,
		&bit1b
	},
	{
		"bit 1, c",
		2,
		&bit1c
	},
	{
		"bit 1, d",
		2,
		&bit1d
	},
	{
		"bit 1, e",
		2,
		&bit1e
	},
	{
		"bit 1, h",
		2,
		&bit1h
	},
	{
		"bit 1, l",
		2,
		&bit1l
	},
	{
		"bit 1, (hl)",
		3,
		&bit1hl
	},
	{
		"bit 1, a",
		2,
		&bit1a
	},

	// 80
	{
		"bit 2, b",
		2,
		&bit2b
	},
	{
		"bit 2, c",
		2,
		&bit2c
	},
	{
		"bit 2, d",
		2,
		&bit2d
	},
	{
		"bit 2, e",
		2,
		&bit2e
	},
	{
		"bit 2, h",
		2,
		&bit2h
	},
	{
		"bit 2, l",
		2,
		&bit2l
	},
	{
		"bit 2, (hl)",
		3,
		&bit2hl
	},
	{
		"bit 2, a",
		2,
		&bit2a
	},
	{
		"bit 3, b",
		2,
		&bit3b
	},
	{
		"bit 3, c",
		2,
		&bit3c
	},

	// 90
	{
		"bit 3, d",
		2,
		&bit3d
	},
	{
		"bit 3, e",
		2,
		&bit3e
	},
	{
		"bit 3, h",
		2,
		&bit3h
	},
	{
		"bit 3, l",
		2,
		&bit3l
	},
	{
		"bit 3, (hl)",
		3,
		&bit3hl
	},
	{
		"bit 3, a",
		2,
		&bit3a
	},
	{
		"bit 4, b",
		2,
		&bit4b
	},
	{
		"bit 4, c",
		2,
		&bit4c
	},
	{
		"bit 4, d",
		2,
		&bit4d
	},
	{
		"bit 4, e",
		2,
		&bit4e
	},

	// 100
	{
		"bit 4, h",
		2,
		&bit4h
	},
	{
		"bit 4, l",
		2,
		&bit4l
	},
	{
		"bit 4, (hl)",
		3,
		&bit4hl
	},
	{
		"bit 4, a",
		2,
		&bit4a
	},
	{
		"bit 5, b",
		2,
		&bit5b
	},
	{
		"bit 5, c",
		2,
		&bit5c
	},
	{
		"bit 5, d",
		2,
		&bit5d
	},
	{
		"bit 5, e",
		2,
		&bit5e
	},
	{
		"bit 5, h",
		2,
		&bit5h
	},
	{
		"bit 5, l",
		2,
		&bit5l
	},

	// 110
	{
		"bit 5, (hl)",
		3,
		&bit5hl
	},
	{
		"bit 5, a",
		2,
		&bit5a
	},
	{
		"bit 6, b",
		2,
		&bit6b
	},
	{
		"bit 6, c",
		2,
		&bit6c
	},
	{
		"bit 6, d",
		2,
		&bit6d
	},
	{
		"bit 6, e",
		2,
		&bit6e
	},
	{
		"bit 6, h",
		2,
		&bit6h
	},
	{
		"bit 6, l",
		2,
		&bit6l
	},
	{
		"bit 6, (hl)",
		3,
		&bit6hl
	},
	{
		"bit 6, a",
		2,
		&bit6a
	},

	// 120
	{
		"bit 7, b",
		2,
		&bit7b
	},
	{
		"bit 7, c",
		2,
		&bit7c
	},
	{
		"bit 7, d",
		2,
		&bit7d
	},
	{
		"bit 7, e",
		2,
		&bit7e
	},
	{
		"bit 7, h",
		2,
		&bit7h
	},
	{
		"bit 7, l",
		2,
		&bit7l
	},
	{
		"bit 7, (hl)",
		3,
		&bit7hl
	},
	{
		"bit 7, a",
		2,
		&bit7a
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},

	// 130
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},

	// 140
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},

	// 150
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},

	// 160
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},

	// 170
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},

	// 180
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},

	// 190
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},

	// 200
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},

	// 210
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},

	// 220
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},

	// 230
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},

	// 240
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},

	// 250
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
};
