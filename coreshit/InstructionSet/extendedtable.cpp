
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
		"sla b",
		2,
		&slab
	},
	{
		"sla c",
		2,
		&slac
	},
	{
		"sla d",
		2,
		&slad
	},
	{
		"sla e",
		2,
		&slae
	},
	{
		"sla h",
		2,
		&slah
	},
	{
		"sla l",
		2,
		&slal
	},
	{
		"sla (hl)",
		4,
		&slahl
	},
	{
		"sla a",
		2,
		&slaa
	},

	// 40
	{
		"sra b",
		2,
		&srab
	},
	{
		"sra c",
		2,
		&srac
	},
	{
		"sra d",
		2,
		&srad
	},
	{
		"sra e",
		2,
		&srae
	},
	{
		"sra h",
		2,
		&srah
	},
	{
		"sra l",
		2,
		&sral
	},
	{
		"sra (hl)",
		4,
		&srahl
	},
	{
		"sra a",
		2,
		&sraa
	},
	{
		"swap b",
		2,
		swapb
	},
	{
		"swap c",
		2,
		swapc
	},

	// 50
	{
		"swap d",
		2,
		swapd
	},
	{
		"swap e",
		2,
		swape
	},
	{
		"swap h",
		2,
		swaph
	},
	{
		"swap l",
		2,
		swapl
	},
	{
		"swap (hl)",
		4,
		swaphl
	},
	{
		"swap a",
		2,
		swapa
	},
	{
		"srl b",
		2,
		&srlb
	},
	{
		"srl c",
		2,
		&srlc
	},
	{
		"srl d",
		2,
		&srld
	},
	{
		"srl e",
		2,
		&srle
	},

	// 60
	{
		"srl h",
		2,
		&srlh
	},
	{
		"srl l",
		2,
		&srll
	},
	{
		"srl (hl)",
		4,
		&srlhl
	},
	{
		"srl a",
		2,
		&srla
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
		"set 0, b",
		2,
		&set0b
	},
	{
		"set 0, c",
		2,
		&set0c
	},
	{
		"set 0, d",
		2,
		&set0d
	},
	{
		"set 0, e",
		2,
		&set0e
	},
	{
		"set 0, h",
		2,
		&set0h
	},
	{
		"set 0, l",
		2,
		&set0l
	},
	{
		"set 0, (hl)",
		4,
		&set0hl
	},
	{
		"set 0, a",
		2,
		&set0a
	},

	// 200
	{
		"set 1, b",
		2,
		&set1b
	},
	{
		"set 1, c",
		2,
		&set1c
	},
	{
		"set 1, d",
		2,
		&set1d
	},
	{
		"set 1, e",
		2,
		&set1e
	},
	{
		"set 1, h",
		2,
		&set1h
	},
	{
		"set 1, l",
		2,
		&set1l
	},
	{
		"set 1, (hl)",
		4,
		&set1hl
	},
	{
		"set 1, a",
		2,
		&set1a
	},
	{
		"set 2, b",
		2,
		&set2b
	},
	{
		"set 2, c",
		2,
		&set2c
	},

	// 210
	{
		"set 2, d",
		2,
		&set2d
	},
	{
		"set 2, e",
		2,
		&set2e
	},
	{
		"set 2, h",
		2,
		&set2h
	},
	{
		"set 2, l",
		2,
		&set2l
	},
	{
		"set 2, (hl)",
		4,
		&set2hl
	},
	{
		"set 2, a",
		2,
		&set2a
	},
	{
		"set 3, b",
		2,
		&set3b
	},
	{
		"set 3, c",
		2,
		&set3c
	},
	{
		"set 3, d",
		2,
		&set3d
	},
	{
		"set 3, e",
		2,
		&set3e
	},

	// 220
	{
		"set 3, h",
		2,
		&set3h
	},
	{
		"set 3, l",
		2,
		&set3l
	},
	{
		"set 3, (hl)",
		4,
		&set3hl
	},
	{
		"set 3, a",
		2,
		&set3a
	},
	{
		"set 4, b",
		2,
		&set4b
	},
	{
		"set 4, c",
		2,
		&set4c
	},
	{
		"set 4, d",
		2,
		&set4d
	},
	{
		"set 4, e",
		2,
		&set4e
	},
	{
		"set 4, h",
		2,
		&set4h
	},
	{
		"set 4, l",
		2,
		&set4l
	},

	// 230
	{
		"set 4, (hl)",
		4,
		&set4hl
	},
	{
		"set 4, a",
		2,
		&set4a
	},
	{
		"set 5, b",
		2,
		&set5b
	},
	{
		"set 5, c",
		2,
		&set5c
	},
	{
		"set 5, d",
		2,
		&set5d
	},
	{
		"set 5, e",
		2,
		&set5e
	},
	{
		"set 5, h",
		2,
		&set5h
	},
	{
		"set 5, l",
		2,
		&set5l
	},
	{
		"set 5, (hl)",
		4,
		&set5hl
	},
	{
		"set 5, a",
		2,
		&set5a
	},

	// 240
	{
		"set 6, b",
		2,
		&set6b
	},
	{
		"set 6, c",
		2,
		&set6c
	},
	{
		"set 6, d",
		2,
		&set6d
	},
	{
		"set 6, e",
		2,
		&set6e
	},
	{
		"set 6, h",
		2,
		&set6h
	},
	{
		"set 6, l",
		2,
		&set6l
	},
	{
		"set 6, (hl)",
		4,
		&set6hl
	},
	{
		"set 6, a",
		2,
		&set6a
	},
	{
		"set 7, b",
		2,
		&set7b
	},
	{
		"set 7, c",
		2,
		&set7c
	},

	// 250
	{
		"set 7, d",
		2,
		&set7d
	},
	{
		"set 7, e",
		2,
		&set7e
	},
	{
		"set 7, h",
		2,
		&set7h
	},
	{
		"set 7, l",
		2,
		&set7l
	},
	{
		"set 7, (hl)",
		4,
		&set7hl
	},
	{
		"set 7, a",
		2,
		&set7a
	},
};
