    org $ae00
 
    ins "songs/end.bin"

    player_init=$ae00
    player_play=$ae03

    start_song=0
    max_song=1

;    .def need_mixforms
;    .def momhack
;    .def cn2hack
;    .def fastadsr

    org song_on_screen

    .sb "  End by Mitch & Dane                   "
    .sb "  2002 Crest                            "
    .sb "  atarisid conversion at 2021-10-30     "
