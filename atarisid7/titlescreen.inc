
titlescreen
    mwa #dlist DLISTL
    mva #34 DMACTL
    mva #15 COLPF0
    mva #15 COLPF1
    mva #0  COLPF2
    tay

wait_for_vb
    lda:rne VCOUNT

    dey:sty WSYNC
    bne wait_for_vb

    jmp main

dlist
    :6 dta 112
    dta 64+7, a(screendata), 112, 2, 112, 2
    :3 dta 112
    :2 dta 2
    :3 dta 112
    dta 2, 112, 2, 112, 2
    dta 65, a(dlist)

screendata
    .sb "       ATARI SID 7.1"
    .sb "                      by Ivo van Poorten"
.ifdef NTSC
    .sb "  (NTSC)"
.else
    .sb "  (PAL) "
.endif
    .sb "          (C) 2012-2016,2023 TGK"

    .sb "    Use CONSOLE keys to select songs    "
    .sb "  when more than one song is available  "

song_on_screen = *
    .ds 120

