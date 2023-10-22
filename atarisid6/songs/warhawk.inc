    org $90e8

    ins "songs/warhawk.bin"

    player_init=$90e8
    player_play=$9112

    start_song=0
    max_song=3

    .def softernoise
;    .def cn2hack



    org song_on_screen

    .sb "  Warhawk                               "
    .sb "  by Rob Hubbard                        "
    .sb "  (C) 1986 Firebird                     "
