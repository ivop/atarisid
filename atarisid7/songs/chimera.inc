    org $9000

    ins "songs/chimera.bin"

    player_init=$9000
    player_play=$9060

    start_song=0
    max_song=2

    .def softernoise



    org song_on_screen

    .sb "  Chimera                               "
    .sb "  by Rob Hubbard                        "
    .sb "  (C) 1986 Firebird                     "
