    org $a000
 
    ins "songs/in_velvet.bin"

    player_init=$a400
    player_play=$a403

    start_song=0
    max_song=1

; the full monty
;    .def need_mixforms
;    .def momhack
;    .def cn2hack
;    .def fastadsr

    org song_on_screen

    .sb " In Velvet by Mitch & Dane              "
    .sb " 1997 Crest                             "
    .sb " atarisid conversion at 2021-10-31      "
