; ----------------------------------------------------------------------------

; Atari Sid VI - MOS 6581/8580 (SID) Emulator for the Atari 8-Bit
;
; Copyright (C) 2012-2016 by Ivo van Poorten
; General Public License Version 3.0
;
; Thanks to:
;   Phaeron - 3 IRQ idea
;   Wrathchild - simplified envelope handling

; ----------------------------------------------------------------------------

    opt r+

    org $0600

disable_basic
    lda PORTB
    ora #$02
    sta PORTB
    mva #0 NMIEN
    mva #0 DMACTL
    rts

    org $02e2
    .word disable_basic

; ----------------------------------------------------------------------------

    icl "songs/zybex.inc"

; ----------------------------------------------------------------------------

    .zpvar src dst  .word = $f0

    icl "defines.inc"

; ----------------------------------------------------------------------------

silence = $1000

.ifdef need_mixforms
decompressed = $4400
    org $7800
compressed
    icl "compressed-mixforms.inc"
.else
    .ifdef experimental
decompressed = $2600
        org $3c00
compressed
        icl "compressed-experimental-nomixforms.inc"
    .else
decompressed = $2600
        org $3c00
compressed
        icl "compressed-nomixforms.inc"
    .endif
.endif

    icl "init.inc"
    icl "adsr.inc"
    icl "titlescreen.inc"

; ----------------------------------------------------------------------------

main
    jsr init_tables

    sei
    mva #0 IRQEN
    mva #0 DMACTL
    mva #0 NMIEN

    mva #$fe PORTB

; copy irq routines to page zero

    ldy #$ef
copypz
    mva tempzp,y $0000,y-
    cpy #$ff
    bne copypz

; PMG's

    mva #1 SIZEP0
    sta SIZEP1
    sta SIZEP2
    sta SIZEP3
    sta SIZEM

    mva #$ff GRAFP0
    sta GRAFP1
    sta GRAFP2
    sta GRAFP3
    sta GRAFM

;    mva #$c4 HPOSP0
    mva #$40 HPOSP1
    mva #$70 HPOSP2
    mva #$a0 HPOSP3

;    mva #3 SIZEP0
    mva #3 SIZEP1
    mva #3 SIZEP2
    mva #3 SIZEP3

;    mva #$ba COLPM0
;    mva #$34 COLPM1
;    mva #$0f COLPM2
;    mva #$86 COLPM3

; timer

    mva #1 AUDCTL
    mva #1 IRQEN

    mva #$00 AUDF1

    mva #$00 AUDF2
    mva #$00 AUDF3
    mva #$00 AUDF4

    sta STIMER

    mwa #irq1 $fffe
    cli

; ------------------------- START OF SOFTSYNTH -------------------------------

new_song
song_nr=*+1
    lda #start_song
    jsr player_init

loop                        ;;;; MAIN LOOP ;;;;
;    mva #0 COLBK

    lda CONSOL
    cmp #7
    beq no_key

    lda #7
    cmp:rne CONSOL

    inc:lda song_nr
    cmp #max_song
    bne new_song

    mva #0 song_nr
    beq new_song

no_key
    lda:rne VCOUNT

;    mva #255 COLBK

    copy_shadow_to_engine 1
    copy_shadow_to_engine 2
    copy_shadow_to_engine 3

    jsr player_play
    jsr extract_all_adsr_values
    jsr do_all_envelopes

    copy_shadow_sid_to_shadow_voice 1
    copy_shadow_sid_to_shadow_voice 2
    copy_shadow_sid_to_shadow_voice 3

    adjust_noise 1
    adjust_noise 2
    adjust_noise 3

    vertbar 1
    vertbar 2
    vertbar 3

    jsr check_all_test_bits
    jsr do_all_envelopes

    jmp loop

; ----------------------------------------------------------------------------

    icl "macros.inc"

bars
    dta $18, $3c, $7e, $ff
cols1
    dta $30, $32, $34, $36
cols2
    dta $02, $06, $0a, $0f
cols3
    dta $80, $82, $84, $86

; ----------------------------------------------------------------------------

extract_all_adsr_values
    extract_adsr_values 1
    extract_adsr_values 2
    extract_adsr_values 3

    rts

do_all_envelopes
    do_envelope 1
    do_envelope 2
    do_envelope 3

    rts

check_all_test_bits
    check_test_bit 1
    check_test_bit 2
    check_test_bit 3

    rts

; ----------------------------------------------------------------------------

; better pulse width handling 0-12 increases to 50% duty, mirror after that
; we do not invert the waveform as it is on a real sid

pwtab
    dta 0, 4, 8, 12, 12, 8, 4, 0

; ----------------------------------------------------------------------------

    .align $0100
tempzp

    org $0000, tempzp

    icl "irq.inc"

; ----------------------------------------------------------------------------

    icl "patches.inc"

; ----------------------------------------------------------------------------

    org $02e0
    .word titlescreen
