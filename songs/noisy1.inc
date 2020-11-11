    org $9000

    ins "songs/noisy1.bin"

    player_init=$9000
    player_play=$9006

    start_song=0
    max_song=0

;    .def need_mixforms
;    .def momhack
;    .def cn2hack

    org song_on_screen

    .sb "  Noisy Pillars (tune 1) by Jeroen Tel  "
    .sb "  1987 Maniacs of Noise                 "
    .sb "  atarisid conversion 2020-11-11        "
