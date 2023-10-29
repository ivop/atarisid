    org $7000
 
; sidreloc did not work with other locations, so no mixforms for you!

    ins "songs/zero.bin"

    player_init=$7000
    player_play=$7006

    start_song=0
    max_song=1

 ; the full monty ;)
;    .def need_mixforms
;    .def momhack
;    .def cn2hack

    org song_on_screen

    .sb "  Zero by Stellan Andersson (Dane)      "
    .sb "  2015 Booze Design                     "
    .sb "  atarisid conversion at 2021-10-26     "
