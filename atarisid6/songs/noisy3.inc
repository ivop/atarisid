    org $9400

    ins "songs/noisy3.bin"

    player_init=$9400
    player_play=$9406

    start_song=0
    max_song=0

;    .def need_mixforms
;    .def momhack
;    .def cn2hack

    org song_on_screen

    .sb "  Noisy Pillars (tune 3) by Jeroen Tel  "
    .sb "  1987 Maniacs of Noise                 "
    .sb "  atarisid conversion 2020-11-12        "
