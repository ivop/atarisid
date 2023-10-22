    org $a000

    ins "songs/ninja.bin"

    player_init=$a000
    player_play=$a006

    start_song=0
    max_song=1

    .def softernoise


    org song_on_screen

    .sb "  Ninja                                 "
    .sb "  by Rob Hubbard                        "
    .sb "  (C) 1986 Entertainment USA            "

