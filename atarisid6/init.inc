
init_tables
    jsr decompress_tables
    jsr spread_and_double

    rts

; ----------------------------------------------------------------------------

decompress_tables
    mwa #compressed src
    mwa #decompressed dst

decompress_loop
    ldy #1
    lda (src),y
    tax:dey
    lda (src),y
    tay:txa

do_run
    sta (dst),y
    cpy #0
    beq run_done
    dey
    jmp do_run

run_done
    lda (src),y
    add dst
    adc #1
    sta dst
    lda dst+1
    adc #0
    sta dst+1

    adw src #2

    lda dst+1
    cmp #>compressed
    bne decompress_loop

    rts

; ----------------------------------------------------------------------------

spread_and_double
    mwa #decompressed src
    mwa #silence dst

    ldy #0
do_next_page
copy1
    mva (src),y (dst),y
    iny:bne copy1

    inc dst+1
copy2
    mva (src),y (dst),y
    iny:bne copy2

    inc src+1
    inc dst+1

    lda dst+1
    cmp #>compressed
    bne do_next_page

    rts

; ----------------------------------------------------------------------------

tri_vol_01 = silence + $0200
tri_vol_10 = silence + $0400
tri_vol_11 = silence + $0600

saw_vol_01 = silence + $0800
saw_vol_10 = silence + $0a00
saw_vol_11 = silence + $0c00

noise_vol_01 = silence + $0e00
noise_vol_10 = silence + $1000
noise_vol_11 = silence + $1200

p20_vol_01 = silence + $1400
p20_vol_10 = silence + $1600
p20_vol_11 = silence + $1800

p40_vol_01 = silence + $1a00
p40_vol_10 = silence + $1c00
p40_vol_11 = silence + $1e00

p60_vol_01 = silence + $2000
p60_vol_10 = silence + $2200
p60_vol_11 = silence + $2400

p80_vol_01 = silence + $2600
p80_vol_10 = silence + $2800
p80_vol_11 = silence + $2a00

sawtri_vol_01 = silence + $2c00
sawtri_vol_10 = silence + $2e00
sawtri_vol_11 = silence + $3000

pt25_vol_01 = silence + $3200
pt25_vol_10 = silence + $3400
pt25_vol_11 = silence + $3600

pt50_vol_01 = silence + $3800
pt50_vol_10 = silence + $3a00
pt50_vol_11 = silence + $3c00

pt75_vol_01 = silence + $3e00
pt75_vol_10 = silence + $4000
pt75_vol_11 = silence + $4200

ps25_vol_01 = silence + $4400
ps25_vol_10 = silence + $4600
ps25_vol_11 = silence + $4800

ps50_vol_01 = silence + $4a00
ps50_vol_10 = silence + $4c00
ps50_vol_11 = silence + $4e00

ps75_vol_01 = silence + $5000
ps75_vol_10 = silence + $5200
ps75_vol_11 = silence + $5400

pst25_vol_01 = silence + $5600
pst25_vol_10 = silence + $5800
pst25_vol_11 = silence + $5a00

pst50_vol_01 = silence + $5c00
pst50_vol_10 = silence + $5e00
pst50_vol_11 = silence + $6000

pst75_vol_01 = silence + $6200
pst75_vol_10 = silence + $6400
pst75_vol_11 = silence + $6600

noiseLUT
    .ifdef softernoise
        .by +(>silence) $00, $0e, $0e, $10
    .else
        .by +(>silence) $00, $0e, $10, $12
    .endif

; TABLE to lookup the highbyte of each wave form
; array[wavetriplet][pulsewidth][volume]     (  [8][4][4]  )

    .align $0080

LUT
; 0 0 0
    .by +(>silence) $00, $00, $00, $00
    .by +(>silence) $00, $00, $00, $00
    .by +(>silence) $00, $00, $00, $00
    .by +(>silence) $00, $00, $00, $00
; 0 0 1                     triangle
    .by +(>silence) $00, $02, $04, $06
    .by +(>silence) $00, $02, $04, $06
    .by +(>silence) $00, $02, $04, $06
    .by +(>silence) $00, $02, $04, $06
; 0 1 0         sawtooth
    .by +(>silence) $00, $08, $0a, $0c
    .by +(>silence) $00, $08, $0a, $0c
    .by +(>silence) $00, $08, $0a, $0c
    .by +(>silence) $00, $08, $0a, $0c

.ifndef need_mixforms
; 0 1 1         sawtooth    (triangle)
    .by +(>silence) $00, $08, $0a, $0c
    .by +(>silence) $00, $08, $0a, $0c
    .by +(>silence) $00, $08, $0a, $0c
    .by +(>silence) $00, $08, $0a, $0c
.else
    .by +(>silence) $00, $2c, $2e, $30
    .by +(>silence) $00, $2c, $2e, $30
    .by +(>silence) $00, $2c, $2e, $30
    .by +(>silence) $00, $2c, $2e, $30
.endif

; 1 0 0 pulse
    .by +(>silence) $00, $14, $16, $18      // 20
    .by +(>silence) $00, $1a, $1c, $1e      // 40
    .by +(>silence) $00, $20, $22, $24      // 60
    .by +(>silence) $00, $26, $28, $2a      // 80

.ifndef need_mixforms
; 1 0 1 pulse               (triangle)
    .by +(>silence) $00, $14, $16, $18      // 25
    .by +(>silence) $00, $1a, $1c, $1e      // 50
    .by +(>silence) $00, $20, $22, $24      // 75
    .by +(>silence) $00, $26, $28, $2a      // 100
; 1 1 0 pulse   (sawtooth)
    .by +(>silence) $00, $14, $16, $18
    .by +(>silence) $00, $1a, $1c, $1e
    .by +(>silence) $00, $20, $22, $24
    .by +(>silence) $00, $26, $28, $2a
; 1 1 1 pulse   (sawtooth)    (triangle)
    .by +(>silence) $00, $14, $16, $18
    .by +(>silence) $00, $1a, $1c, $1e
    .by +(>silence) $00, $20, $22, $24
    .by +(>silence) $00, $26, $28, $2a
.else
; 1 0 1 pulse               (triangle)
    .by +(>silence) $00, $32, $34, $36      // 25
    .by +(>silence) $00, $38, $3a, $3c      // 50
    .by +(>silence) $00, $3e, $40, $42      // 75
    .by +(>silence) $00, $02, $04, $06      // 100
; 1 1 0 pulse   (sawtooth)
    .by +(>silence) $00, $44, $46, $48
    .by +(>silence) $00, $4a, $4c, $4e
    .by +(>silence) $00, $50, $52, $54
    .by +(>silence) $00, $08, $0a, $0c
; 1 1 1 pulse   (sawtooth)    (triangle)
    .by +(>silence) $00, $56, $58, $5a
    .by +(>silence) $00, $5c, $5e, $60
    .by +(>silence) $00, $62, $64, $66
    .by +(>silence) $00, $2c, $2e, $30
.endif
