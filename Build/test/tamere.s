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

section "Vblank IRQ", ROM0[$40]

	call bndtest
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
	db $59, $41, $59, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00

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

	; Zero registers zone
	ld c, $80
	xor a
ztop:	ld [c], a
	dec c
	jr nz, ztop
	ld [c], a

	; Set stack and some hardware registers
start:	ld sp, $fffe
	ld a, %11100100
	ldh [BGP], a
	ldh [OBP0], a
	ld a, %01010011
	ldh [OBP1], a
	ld a, %10010001
	ldh [LCDC], a
	ld a, $20
	ldh [JOYP], a
	xor a
	ldh [SCX], a
	ldh [SCY], a

	; Clear Memory
	ld hl, $9fff
gu:	ldd [hl], a
	bit 7, h
	jr nz, gu

	; Copy char to cbank
	xor a
	ldh [$80], a

	; Load src and dst pointers
	ld de, chars
	ld hl, CBK0

	; Save them, then call charcpy
chrinit:push hl
	push de
	call charcpy

	; Shift src to next char
mooga:	pop de
	ld a, 8
	add a, e
	ld e, a
	ld a, 0
	adc a, d
	ld d, a

	; Shift dst to next slot
	pop hl
	ld bc, 16
	add hl, bc

	; Test for end of loop
	ldh a, [$80]
	cp 255
	jr z, next

	; Inc counter
	inc a
	ldh [$80], a
	jr chrinit

	; Set chars on screen
next:	ld hl, CSTART
	ld b, 0
ltop2:	ld a, [STAT]
	bit 1, a
	jr nz, ltop2
	ld a, b
	ldi [hl], a
	inc b
	ld a, h
	cp $9C
	jr nz, ltop2

	; Wait for OAM
	ld hl, STAT
woam1:	bit 1, [hl]
	jr z, woam1
woam2:	bit 1, [hl]
	jr nz, woam2

	; Then set the sprite
	ld a, 80
	ld [$fe00], a
	ld [$fe01], a
	ld a, 2
	ld [$fe02], a
	ld a, %00010000
	ld [$fe03], a

	; Turn on sprites
	ld a, %10010011
	ld [LCDC], a

	; Mooga
	xor a
	ldh [$81], a

	; Enable VBlank IRQ
	ld a, %00000001
	ldh [IE], a
	ei

	; Main loop
main:	halt

	; Swap 
	ldh a, [$81]
	add a, 16
	ldh [$81], a
	cp 128
	jr nc, casenz

	ld a, %00010000
	ld [$fe03], a
	jr main
	
casenz:	ld a, %00000000
	ld [$fe03], a
	jr main

; ------ Test binds routine ------

	; Load JOYP state
bndtest:ldh a, [JOYP]

	; Test right
	bit 0, a
	jr z, right

	; Test left
ltest	bit 1, a
	jr z, left

	; Test up
utest:	bit 2, a
	jr z, up

	; Test down
dtest:	bit 3, a
	jr z, down

	; Leave
	ret

	; Sroll CAM Right
right:	ld hl, SCX
	inc [HL]
	jr ltest

	; Scroll CAM Left
left:	ld hl, SCX
	dec [HL]
	jr utest

	; Scroll CAM Up
up:	ld hl, SCY
	dec [HL]
	jr dtest

	; Scroll CAM Down
down:	ld hl, SCY
	inc [HL]

	; Leave
	ret

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
	jr nz, memcopy

	; Leave
	ret

; ------ Wait for V-Sync+ ------

vsyncp:	ldh a, [$44]
	cp $90
	jr nz, vsync
vsp2:	ldh a, [$44]
	cp $91
	jr nz, vsp2
	ret

; ------ Wait for V-Sync ------

vsync:	ldh a, [$44]
	cp $90
	jr nz, vsync
	ret

; ------ Include IBM style characters ------

include "ascii.s"
