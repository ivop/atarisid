
.ifdef speedball_patches
    org $87d0

patch1
    pha
    txa
    and #1
    bne gate_on_1

    lda #3
    sta s1_envphase

gate_on_1
    pla
    stx SIDV1CTRL
    rts

    org $87e0

patch2
    pha
    txa
    and #1
    bne gate_on_2

    lda #3
    sta s2_envphase

gate_on_2
    pla
    stx SIDV2CTRL
    rts

    org $87f0

patch3
    pha
    txa
    and #1
    bne gate_on_3

    lda #3
    sta s3_envphase

gate_on_3
    pla
    stx SIDV3CTRL
    rts
.endif

.ifdef zybex_patches

    org $87d0
patch1
    sta SIDV1CTRL
    lda #3
    sta s1_envphase
    rts

    org $87e0
patch2
    sta SIDV2CTRL
    lda #3
    sta s2_envphase
    rts

    org $87f0
patch3
    sta SIDV3CTRL
    lda #3
    sta s3_envphase
    rts

.endif

.ifdef ninjac_patches

    org $87d0
patch
    sta SIDV1CTRL,y
    lda #3
    cpy #0
    bne nots1
    sta s1_envphase
    rts
nots1
    cpy #7
    bne nots2
    sta s2_envphase
    rts
nots2
    sta s3_envphase
    rts
.endif
