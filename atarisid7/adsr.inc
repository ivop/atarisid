
; ----------------------------------------------------------------------------

; ADSR Tables

    .align $0100

    .ifndef fastadsr

attacks
    dta a(0x0f00, 0x0f00, 0x0960, 0x0640, 0x03f3, 0x02ae, 0x0235, 0x01e0)
    dta a(0x0180, 0x009a, 0x004d, 0x0030, 0x0026, 0x000d, 0x0008, 0x0005)

decays
releases
    dta a(0x0f00, 0x0640, 0x0320, 0x0215, 0x0151, 0x00e5, 0x00bc, 0x00a0)
    dta a(0x0080, 0x0033, 0x001a, 0x0010, 0x000d, 0x0004, 0x0003, 0x0002)

    .else

;(twice as fast)
attacks
    dta a(0x0f00, 0x0f00, 0x0f00, 0x0c80, 0x07e5, 0x055b, 0x0469, 0x03c0)
    dta a(0x0300, 0x0133, 0x009a, 0x0060, 0x004d, 0x001a, 0x000f, 0x000a)
decays
releases
    dta a(0x0f00, 0x0c80, 0x0640, 0x042b, 0x02a2, 0x01c9, 0x0178, 0x0140)
    dta a(0x0100, 0x0066, 0x0033, 0x0020, 0x001a, 0x0009, 0x0005, 0x0003)

    .endif

; ----------------------------------------------------------------------------

; ADSR

    .macro extract_adsr_values(num)
    lda:tay SIDV:1AD
    :+4 lsr
    asl:tax

    mwa attacks,x s:1_attack

    tya:and #$0f
    asl:tax
    mwa decays,x s:1_decay

    lda:tax SIDV:1SR
    :+4 lsr
    sta s:1_sustain
    txa:and #$0f
    asl:tax
    mwa releases,x s:1_release

    lda:tax SIDV:1CTRL
    and #1
    sta s:1_gate
    txa:and #8
    sta s:1_test
    .endm

; ----------------------------------------------------------------------------

    .macro do_envelope(num)
    lda s:1_gate
    bne gate_is_on
 
    mva #3 s:1_envphase
    bne do_phases

gate_is_on
    lda s:1_envphase
    cmp #3
    bne do_phases

    mva #0 s:1_envphase
    mwa #0 s:1_enval

do_phases               ; "switch" statement
    lda s:1_envphase
    cmp #3
    beq case3

    cmp #2
    beq copy_to_volume  ; sustain: do nothing until gate bit clears

    cmp #1
    beq case1

case0
    adw s:1_enval s:1_attack
    cmp #0x10
    bcc copy_to_volume

    mwa #$0ff0 s:1_enval
    mva #1 s:1_envphase
    bne copy_to_volume      ; branch always

case1
    sbw s:1_enval s:1_decay
    bmi reached_sustain
    cmp s:1_sustain
    bcs copy_to_volume

reached_sustain
    mva #0 s:1_enval
    mva s:1_sustain s:1_enval+1

    mva #2 s:1_envphase
    bne copy_to_volume      ; branch always

case3
    sbw s:1_enval s:1_release
    bpl copy_to_volume

    mwa #$40 s:1_enval

copy_to_volume

    lda s:1_enval+1
    :+2 lsr
    bne not_zero

    adc #0

not_zero
    sta volume_v:1
    .endm

; ----------------------------------------------------------------------------

    .macro check_test_bit(num)
    lda s:1_test
    beq no_reset

    mwa #0 shadow_freq_v:1

no_reset
    .endm

; ----------------------------------------------------------------------------

; ADSR Variables

    .var s1_attack, s1_decay .word
    .var s1_sustain .byte
    .var s1_release .word
    .var s1_envphase .byte
    .var s1_enval = $0040 .word
    .var s1_gate, s1_test .byte

    .var s2_attack, s2_decay .word
    .var s2_sustain .byte
    .var s2_release .word
    .var s2_envphase .byte
    .var s2_enval = $0040 .word
    .var s2_gate, s2_test .byte

    .var s3_attack, s3_decay .word
    .var s3_sustain .byte
    .var s3_release .word
    .var s3_envphase .byte
    .var s3_enval = $0040 .word
    .var s3_gate, s3_test .byte

; ----------------------------------------------------------------------------

