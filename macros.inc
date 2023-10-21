
    .macro copy_shadow_to_engine(num)
    mva shadow_table_msb_v:1 table_msb_v:1_i1
    sta table_msb_v:1_i2
    sta table_msb_v:1_i3

    mva shadow_freq_lsb_v:1_triple freq_lsb_v:1
    mva shadow_freq_msb_v:1_triple freq_msb_v:1

    adb table_lsb_v:1_i1 shadow_freq_msb_v:1 table_lsb_v:1_i2
    adc shadow_freq_msb_v:1
    sta table_lsb_v:1_i3
    .endm

    .macro copy_shadow_sid_to_shadow_voice(num)
    lda SIDV:1CTRL

    icl "hacks.inc"

    and #$70
    sta temp1
    lda SIDV:1PWHI
    and #$0c
    ora temp1
    ora volume_v:1
    tax
    mva LUT,x shadow_table_msb_v:1

    lda SIDV:1FREQHI
    lsr
    sta shadow_freq_msb_v:1_triple
    lda SIDV:1FREQLO
    ror
    sta shadow_freq_lsb_v:1_triple

    lda shadow_freq_msb_v:1_triple
    lsr
    sta shadow_freq_msb_v:1
    lda shadow_freq_lsb_v:1_triple
    ror
    adc #0                                              ; round
    sta shadow_freq_lsb_v:1

    adw shadow_freq_v:1_triple shadow_freq_v:1
    .endm

    .macro adjust_noise(num)
    lda SIDV:1CTRL
    and #$80
    beq nonoise

    ldx volume_v:1
    mva noiseLUT,x shadow_table_msb_v:1
    mva noiseLUT2,x AUDC2

    lda SIDV:1FREQHI
    cmp #$30
    bcs setfzero

; approximate:

    lda #$2f
    sec
    sbc SIDV:1FREQHI
    lsr
    lsr
;    lsr
    bne setf

setfzero
    lda #0

setf
;;    sta AUDF:1
    sta AUDF2

nonoise
    .endm

    .macro vertbar(num)
    ldx volume_v:1
    mva bars,x GRAFP:1
    mva cols:1,x COLPM:1
    .endm

