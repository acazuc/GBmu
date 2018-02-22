CBK0 equ $8000

CSTART equ $9800
CEND equ $9BFF

SCY equ $FF42
SCX equ $FF43
LCDC equ $FF40
BGP equ $FF47
OBP0 equ $FF48
OBP1 equ $FF49
JOYP equ $FF00
IE equ $FFFF
STAT equ $FF41
DMA equ $FF46
SVBK equ $FF70

BCPS equ $FF68
BCPD equ $FF69

section "Vblank IRQ", ROM0[$40]

	reti

section "LCD Stat IRQ", ROM0[$48]

	reti

section "Timer IRQ", ROM0[$50]

	reti

section "Serial IRQ", ROM0[$58]

	reti

section "Joyint IRQ", ROM0[$60]

	reti

section "header", ROM0[$100]

	; Entry point
	nop
	jp start

	; Nintendo Logo
	db $CE, $ED, $66, $66, $CC, $0D, $00, $0B, $03, $73, $00, $83, $00, $0C, $00, $0D 
	db $00, $08, $11, $1F, $88, $89, $00, $0E, $DC, $CC, $6E, $E6, $DD, $DD, $D9, $99 
	db $BB, $BB, $67, $63, $6E, $0E, $EC, $CC, $DD, $DC, $99, $9F, $BB, $B9, $33, $3E

	; Name ( YAY )
	db $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00

	; CGB Flag
	db 0

	; Licensee Code
	db 0, 0

	; SGB Flag
	db 0

	; Cartridge type
        db 2

	; Rom Size
        db $8

	; Ram Size
        db $5

	; Is not Japan ?
	db 1

	; Licensee Code
	db 0

	; Version Number
        db 0

	; Complement Checksum
        db 0

	; Checksum
        dw 0

section "", ROM0[$150]

start:	
	ld a, $01
	ld [$6000], a

	ld a, $0a
	ld [$0000], a

	ld b, $10
grill:	ld hl, $a000
mii:	ld a, b
	ld [hli], a
	ld a, h
	cp $c0
	jr nz, mii
	inc b
	ld a, b
	ld [$4000], a
	cp $14
	jr nz, grill

	ld b, 0
grill2:	ld hl, $a000
mii2:	ld a, [hli]
	ld c, a
	ld a, h
	cp $c0
	jr nz, mii2
	inc b
	ld a, b
	ld [$4000], a
	cp $04
	jr nz, grill2

	stop

	ld a, $4
	ld [$2000], a
	ld a, $01
	ld [$4000], a

	ld a, $01
	ld [$6000], a
	ld a, $00
	ld [$6000], a
	ld a, $01
	ld [$6000], a
	ld a, $00
	ld [$6000], a

	stop

	xor a
	ld b, a
mooga:	ld [$2000], a
	inc a
	cp $20
	jr nz, mooga
	inc b
	ld a, b
	;ld [$6000], a
	ld [$4000], a
	xor a
	jr mooga
	stop

; ------ Charcopy ------

	; Set up 8 counter (doubled 8 lines)
charcpy:ld b, 8

	; Load byte from source
cctop:	ld a, [de]
	inc de

	; Wait for display mode 0 or 1
	ld c, a
ccstat:	ldh a, [STAT]
	bit 1, a
	jr nz, ccstat
	ld a, c

	; Store byte to dest, twice
	ld [hli], a
	ld [hli], a

	; Decrement counter and loop if zero not reached
	dec b
	jr nz, cctop

	; Leave
	ret

; ------ Memcopy ------

	; Load byte from source
memcpy:	ld a, [de]
	inc de

	; Store byte to dest
	ld [hli], a

	; Decrement counter and loop if zero not reached
	dec b
	jr nz, memcpy

	; Leave
	ret

; ------ Include IBM style characters ------

include "ascii.s"
