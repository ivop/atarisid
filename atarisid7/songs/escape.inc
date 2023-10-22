    org $a0d0

    ins "songs/escape.bin"

    player_init=$a0d0
    player_play=$a0d3

    start_song=0
    max_song=1

    .def softernoise

    org song_on_screen

    .sb "  Escape From Reality                   "
    .sb "  by Stellan Andersson (Dane)           "
    .sb "  (C) 1997 Crest                        "

