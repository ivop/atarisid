
; test, ringmod and assorted problems removal

    .ifdef momhack
        cmp #$15
        beq momhack
        cmp #$14
        bne nomomhack
momhack
        lda #$80
nomomhack
    .endif

    .ifdef cn2hack
        cmp #$16
        beq cn2hack
        cmp #$17
        bne nocn2hack
cn2hack
        lda #0
nocn2hack
    .endif

