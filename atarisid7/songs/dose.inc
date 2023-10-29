    org $a000
 
    ins "songs/dose.bin"

    player_init=$a000
    player_play=$a003

    start_song=0
    max_song=1

; the full monty ;)
;    .def need_mixforms
;    .def momhack
;    .def cn2hack
;    .def fastadsr

    org song_on_screen

    .sb "  Dose of D by Mitch & Dane             "
    .sb "  1995 Crest                            "
    .sb "  atarisid conversion at 2021-10-30     "
