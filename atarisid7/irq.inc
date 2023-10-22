
irq1
    sta saveA1
    sty saveY1

;    clc

loval1=*+1
    lda lotab
hival1=*+1
    ldy hitab
    sta AUDC1
    sty AUDC3

count_lsb_v2=*+1
    lda #0
freq_lsb_v2=*+1
    adc #0
    sta count_lsb_v2
count_msb_v2=*+1
    lda #0
    tay
freq_msb_v2=*+1
    adc #0
    sta count_msb_v2

;    ldy count_msb_v2
table_lsb_v2_i3=*+1
table_msb_v2_i3=*+2
    lda $1000,y
;    sta AUDC3

    ldy count_msb_v3
table_lsb_v3_i2=*+1
table_msb_v3_i2=*+2
    adc $1000,y
;    lda $1000,y
;    sta AUDC4

    ldy count_msb_v1
table_lsb_v1_i1=*+1
table_msb_v1_i1=*+2
    adc $1000,y
;    lda $1000,y
;    sta AUDC2

    sta loval2
    sta hival2

    mva #irq2 $fffe

    inc IRQEN
saveA1=*+1
    lda #0
saveY1=*+1
    ldy #0
    rti

; -=-=-=-=-=-=-

irq2
    sta saveA2
    sty saveY2

;    clc

loval2=*+1
    lda lotab
hival2=*+1
    ldy hitab
    sta AUDC1
    sty AUDC3

count_lsb_v3=*+1
    lda #0
freq_lsb_v3=*+1
    adc #0
    sta count_lsb_v3
count_msb_v3=*+1
    lda #0
    tay
freq_msb_v3=*+1
    adc #0
    sta count_msb_v3

;    ldy count_msb_v3
table_lsb_v3_i3=*+1
table_msb_v3_i3=*+2
    lda $1000,y
;    sta AUDC4

    ldy count_msb_v1
table_lsb_v1_i2=*+1
table_msb_v1_i2=*+2
    adc $1000,y
;    lda $1000,y
;    sta AUDC2

    ldy count_msb_v2
table_lsb_v2_i1=*+1
table_msb_v2_i1=*+2
    adc $1000,y
;    lda $1000,y
;    sta AUDC3

    sta loval3
    sta hival3

    mva #irq3 $fffe

    inc IRQEN
saveA2=*+1
    lda #0
saveY2=*+1
    ldy #0
    rti

; -=-=-=-=-=-=-

irq3
    sta saveA3
    sty saveY3

;    clc

loval3=*+1
    lda lotab
hival3=*+1
    ldy hitab
    sta AUDC1
    sty AUDC3

count_lsb_v1=*+1
    lda #0
freq_lsb_v1=*+1
    adc #0
    sta count_lsb_v1
count_msb_v1=*+1
    lda #0
    tay
freq_msb_v1=*+1
    adc #0
    sta count_msb_v1

;    ldy count_msb_v1
table_lsb_v1_i3=*+1
table_msb_v1_i3=*+2
    lda $1000,y
;    sta AUDC2

    ldy count_msb_v2
table_lsb_v2_i2=*+1
table_msb_v2_i2=*+2
    adc $1000,y
;    lda $1000,y
;    sta AUDC3

    ldy count_msb_v3
table_lsb_v3_i1=*+1
table_msb_v3_i1=*+2
    adc $1000,y
;    lda $1000,y
;    sta AUDC4

    sta loval1
    sta hival1

    mva #irq1 $fffe

    inc IRQEN
saveA3=*+1
    lda #0
saveY3=*+1
    ldy #0
    rti

shadow_freq_v1
shadow_freq_lsb_v1          .byte 0
shadow_freq_msb_v1          .byte 0
shadow_freq_v1_triple
shadow_freq_lsb_v1_triple   .byte 0
shadow_freq_msb_v1_triple   .byte 0
shadow_table_msb_v1         .byte >silence

shadow_freq_v2
shadow_freq_lsb_v2          .byte 0
shadow_freq_msb_v2          .byte 0
shadow_freq_v2_triple
shadow_freq_lsb_v2_triple   .byte 0
shadow_freq_msb_v2_triple   .byte 0
shadow_table_msb_v2         .byte >silence

shadow_freq_v3
shadow_freq_lsb_v3          .byte 0
shadow_freq_msb_v3          .byte 0
shadow_freq_v3_triple
shadow_freq_lsb_v3_triple   .byte 0
shadow_freq_msb_v3_triple   .byte 0
shadow_table_msb_v3         .byte >silence

volume_v1   .byte 0
volume_v2   .byte 0
volume_v3   .byte 0

temp1       .byte 0
temp2       .byte 0

