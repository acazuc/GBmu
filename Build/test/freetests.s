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
        db 0

	; Rom Size
        db 0

	; Ram Size
        db 0

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

	ld a, 0
choy:	inc a
	daa
	jr nz, choy

	scf
	ccf
	scf

	ld sp, $fffe
	ld a, 1
	ld b, 2
	ld c, 3
	ld d, 4
	ld e, 5
	ld h, 6
	ld l, 7

	push af
	push bc
	push de
	push hl

	xor a
	ld b, a
	ld c, a
	ld d, a
	ld e, a
	ld h, a
	ld l, a

	pop hl
	pop de
	pop bc
	pop af

	ld b, 0

	ld sp, $0ff0
miitop:	ld hl, sp - 1
	dec sp
	jr miitop

ltop:	ld sp, $0ff0
	ld hl, there + 1
	ld [hl], b
there:	add sp, 0
	inc b
	jr nz, ltop

	call next

	ld a, %10000000
	ldh [BCPS], a

	xor a
yay:	ldh [BCPD], a
	inc a
	cp $3f
	jr nz, yay

	xor a
	ld b, a
	ldh [BCPS], a
aja:	ldh a, [BCPD]
	inc b
	ld a, b
	ldh [BCPS], a
	bit 6, b
	jr z, aja

	stop

next	call c, mii
	ret

mii:	call poda
	ret c

poda:	ret


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
