
#include <jackshit.h>

struct core::instruction core::decode[256] =
{
	// 0
	{
		"nop",
		1,
		&nop
	},
	{
		"ld bc, nn",
		3,
		&ldbcnn
	},
	{
		"ld (bc), a",
		2,
		&ldbca
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"inc b",
		1,
		&incb,
	},
	{
		"dec b",
		1,
		&decb,
	},
	{
		"ld b, n",
		2,
		&ldbn
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"ld (nn), sp",
		5,
		&ldnnsp
	},
	{
		"add hl, bc",
		2,
		&addhlbc
	},

	// 10
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
		"inc c",
		1,
		&incc,
	},
	{
		"dec c",
		1,
		&decc,
	},
	{
		"ld c, n",
		2,
		&ldcn
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
		"ld de, nn",
		3,
		&lddenn
	},
	{
		"ld (de), a",
		2,
		&lddea
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},

	// 20
	{
		"inc d",
		1,
		&incd,
	},
	{
		"dec d",
		1,
		&decd,
	},
	{
		"ld d, n",
		2,
		&lddn
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"jr ne",
		3,
		&jr
	},
	{
		"add hl, de",
		2,
		&addhlde
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
		"inc e",
		1,
		&ince,
	},
	{
		"dec e",
		1,
		&dece,
	},

	// 30
	{
		"ld e, n",
		2,
		&lden
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"jr nz, ne",
		3,
		&jrnz
	},
	{
		"ld hl, nn",
		3,
		&ldhlnn
	},
	{
		"ld (hli), a",
		2,
		&ldhlia
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"inc h",
		1,
		&inch,
	},
	{
		"dec h",
		1,
		&dech,
	},
	{
		"ld h, n",
		2,
		&ldhn
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},

	// 40
	{
		"jr z, ne",
		3,
		&jrz
	},
	{
		"add hl, hl",
		2,
		&addhlhl
	},
	{
		"ld a, (hli)",
		4,
		&ldahli
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"inc l",
		1,
		&incl,
	},
	{
		"dec l",
		1,
		&decl,
	},
	{
		"ld l, n",
		2,
		&ldln
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"jr nc, ne",
		3,
		&jrnc
	},
	{
		"ld sp, nn",
		3,
		&ldspnn
	},

	// 50
	{
		"ld (hld), a",
		4,
		&ldhlda
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"inc (hl)",
		1,
		&inchl,
	},
	{
		"dec (hl)",
		1,
		&dechl,
	},
	{
		"ld (hl), n",
		3,
		&ldhln
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"jr c, ne",
		3,
		&jrc
	},
	{
		"add hl, sp",
		2,
		&addhlsp
	},
	{
		"ld a, (hld)",
		4,
		&ldahld
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},

	// 60
	{
		"inc a",
		1,
		&inca,
	},
	{
		"dec a",
		1,
		&deca,
	},
	{
		"ld a, n",
		2,
		&ldan
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"ld b, b",
		1,
		&ldbb
	},
	{
		"ld b, c",
		1,
		&ldbc
	},
	{
		"ld b, d",
		1,
		&ldbd
	},
	{
		"ld b, e",
		1,
		&ldbe
	},
	{
		"ld b, h",
		1,
		&ldbh
	},
	{
		"ld b, l",
		1,
		&ldbl
	},

	// 70
	{
		"ld b, (hl)",
		2,
		&ldbhl
	},
	{
		"ld b, a",
		1,
		&ldba
	},
	{
		"ld c, b",
		1,
		&ldcb
	},
	{
		"ld c, c",
		1,
		&ldcc
	},
	{
		"ld c, d",
		1,
		&ldcd
	},
	{
		"ld c, e",
		1,
		&ldce
	},
	{
		"ld c, h",
		1,
		&ldch
	},
	{
		"ld c, l",
		1,
		&ldcl
	},
	{
		"ld c, (hl)",
		2,
		&ldchl
	},
	{
		"ld c, a",
		1,
		&ldca
	},

	// 80
	{
		"ld d, b",
		1,
		&lddb
	},
	{
		"ld d, c",
		1,
		&lddc
	},
	{
		"ld d, d",
		1,
		&lddd
	},
	{
		"ld d, e",
		1,
		&ldde
	},
	{
		"ld d, h",
		1,
		&lddh
	},
	{
		"ld d, l",
		1,
		&lddl
	},
	{
		"ld d, (hl)",
		2,
		&lddhl
	},
	{
		"ld d, a",
		1,
		&ldda
	},
	{
		"ld e, b",
		1,
		&ldeb
	},
	{
		"ld e, c",
		1,
		&ldec
	},

	// 90
	{
		"ld e, d",
		1,
		&lded
	},
	{
		"ld e, e",
		1,
		&ldee
	},
	{
		"ld e, h",
		1,
		&ldeh
	},
	{
		"ld e, l",
		1,
		&ldel
	},
	{
		"ld e, (hl)",
		2,
		&ldehl
	},
	{
		"ld e, a",
		1,
		&ldea
	},
	{
		"ld h, b",
		1,
		&ldhb
	},
	{
		"ld h, c",
		1,
		&ldhc
	},
	{
		"ld h, d",
		1,
		&ldhd
	},
	{
		"ld h, e",
		1,
		&ldhe
	},

	// 100
	{
		"ld h, h",
		1,
		&ldhh
	},
	{
		"ld h, l",
		1,
		&ldhl
	},
	{
		"ld h, (hl)",
		2,
		&ldhhl
	},
	{
		"ld h, a",
		1,
		&ldha
	},
	{
		"ld l, b",
		1,
		&ldlb
	},
	{
		"ld l, c",
		1,
		&ldlc
	},
	{
		"ld l, d",
		1,
		&ldld
	},
	{
		"ld l, e",
		1,
		&ldle
	},
	{
		"ld l, h",
		1,
		&ldlh
	},
	{
		"ld l, l",
		1,
		&ldll
	},

	// 110
	{
		"ld l, (hl)",
		2,
		&ldlhl
	},
	{
		"ld l, a",
		1,
		&ldla
	},
	{
		"ld (hl), b",
		2,
		&ldhlb
	},
	{
		"ld (hl), c",
		2,
		&ldhlc
	},
	{
		"ld (hl), d",
		2,
		&ldhld
	},
	{
		"ld (hl), e",
		2,
		&ldhle
	},
	{
		"ld (hl), h",
		2,
		&ldhlh
	},
	{
		"ld (hl), l",
		2,
		&ldhll
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"ld (hl), a",
		2,
		&ldhla
	},

	// 120
	{
		"ld a, b",
		1,
		&ldab
	},
	{
		"ld a, c",
		1,
		&ldac
	},
	{
		"ld a, d",
		1,
		&ldad
	},
	{
		"ld a, e",
		1,
		&ldae
	},
	{
		"ld a, h",
		1,
		&ldah
	},
	{
		"ld a, l",
		1,
		&ldal
	},
	{
		"ld a, (hl)",
		2,
		&ldahl
	},
	{
		"ld a, a",
		1,
		&ldaa
	},
	{
		"add a, b",
		1,
		&addab
	},
	{
		"add a, c",
		1,
		&addac
	},

	// 130
	{
		"add a, d",
		1,
		&addad
	},
	{
		"add a, e",
		1,
		&addae
	},
	{
		"add a, h",
		1,
		&addah
	},
	{
		"add a, l",
		1,
		&addal
	},
	{
		"add a, (hl)",
		1,
		&addahl
	},
	{
		"add a, a",
		1,
		&addaa
	},
	{
		"adc a, b",
		1,
		&adcab,
	},
	{
		"adc a, c",
		1,
		&adcac,
	},
	{
		"adc a, d",
		1,
		&adcad,
	},
	{
		"adc a, e",
		1,
		&adcae,
	},

	// 140
	{
		"adc a, h",
		1,
		&adcah,
	},
	{
		"adc a, l",
		1,
		&adcal,
	},
	{
		"adc a, (hl)",
		1,
		&adcahl,
	},
	{
		"adc a, a",
		1,
		&adcaa,
	},
	{
		"sub b",
		1,
		&subab,
	},
	{
		"sub c",
		1,
		&subac,
	},
	{
		"sub d",
		1,
		&subad,
	},
	{
		"sub e",
		1,
		&subae,
	},
	{
		"sub h",
		1,
		&subah,
	},
	{
		"sub l",
		1,
		&subal,
	},

	// 150
	{
		"sub (hl)",
		1,
		&subahl,
	},
	{
		"sub a",
		1,
		&subaa,
	},
	{
		"sbc a, b",
		1,
		&sbcab,
	},
	{
		"sbc a, c",
		1,
		&sbcac,
	},
	{
		"sbc a, d",
		1,
		&sbcad,
	},
	{
		"sbc a, e",
		1,
		&sbcae,
	},
	{
		"sbc a, h",
		1,
		&sbcah,
	},
	{
		"sbc a, l",
		1,
		&sbcal,
	},
	{
		"sbc a, (hl)",
		1,
		&sbcahl,
	},
	{
		"sbc a, a",
		1,
		&sbcaa,
	},

	// 160
	{
		"and b",
		1,
		&andb,
	},
	{
		"and c",
		1,
		&andc,
	},
	{
		"and d",
		1,
		&andd,
	},
	{
		"and e",
		1,
		&ande,
	},
	{
		"and h",
		1,
		&andh,
	},
	{
		"and l",
		1,
		&andl,
	},
	{
		"and (hl)",
		1,
		&andhl,
	},
	{
		"and a",
		1,
		&anda,
	},
	{
		"xor b",
		1,
		&xorb,
	},
	{
		"xor c",
		1,
		&xorc,
	},

	// 170
	{
		"xor d",
		1,
		&xord,
	},
	{
		"xor e",
		1,
		&xore,
	},
	{
		"xor h",
		1,
		&xorh,
	},
	{
		"xor l",
		1,
		&xorl,
	},
	{
		"xor (hl)",
		1,
		&xorhl,
	},
	{
		"xor a",
		1,
		&xora,
	},
	{
		"or b",
		1,
		&orb,
	},
	{
		"or c",
		1,
		&orc,
	},
	{
		"or d",
		1,
		&ord,
	},
	{
		"or e",
		1,
		&ore,
	},

	// 180
	{
		"or h",
		1,
		&orh,
	},
	{
		"or l",
		1,
		&orl,
	},
	{
		"or (hl)",
		1,
		&orhl,
	},
	{
		"or a",
		1,
		&ora,
	},
	{
		"cp b",
		1,
		&cpb,
	},
	{
		"cp c",
		1,
		&cpc,
	},
	{
		"cp d",
		1,
		&cpd,
	},
	{
		"cp e",
		1,
		&cpe,
	},
	{
		"cp h",
		1,
		&cph,
	},
	{
		"cp l",
		1,
		&cpl,
	},

	// 190
	{
		"cp (hl)",
		1,
		&cphl,
	},
	{
		"cp a",
		1,
		&cpa,
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"pop bc",
		3,
		&popbc
	},
	{
		"jp nz, nn",
		4,
		&jpnz
	},
	{
		"jp nn",
		4,
		&jp
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"push bc",
		4,
		&pushbc
	},
	{
		"add a, n",
		2,
		&addan
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
		"jp z, nn",
		4,
		&jpz
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
		"adc a, n",
		2,
		&adcan
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
		"pop de",
		3,
		&popde
	},

	// 210
	{
		"jp nc, nn",
		4,
		&jpnc
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
		"push de",
		4,
		&pushde
	},
	{
		"sub n",
		2,
		&suban
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
		"jp c, nn",
		4,
		&jpc
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
		"sbc a, n",
		2,
		&sbcan
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"ld (n), a",
		3,
		&ldrna
	},
	{
		"pop hl",
		3,
		&pophl
	},
	{
		"ld (c), a",
		2,
		&ldrca
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
		"push hl",
		4,
		&pushhl
	},

	// 230
	{
		"and n",
		2,
		&andn
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"add sp, ne",
		1,
		&_blank
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"ld (nn), a",
		4,
		&ldnna
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
		"xor n",
		2,
		&xorn
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},

	// 240
	{
		"ld a, (n)",
		3,
		&ldarn
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"pop af",
		3,
		&popaf
	},
	{
		"ld a, (c)",
		2,
		&ldarc
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"push af",
		4,
		&pushaf
	},
	{
		"or n",
		2,
		&orn
	},
	{
		"__ NO INSTRUCTION __",
		1,
		&_blank
	},
	{
		"ldhl sp, e",
		3,
		&ldhlspe
	},
	{
		"ld sp, hl",
		2,
		&ldsphl
	},

	// 250
	{
		"ld a, (nn)",
		4,
		&ldann
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
	}
};
