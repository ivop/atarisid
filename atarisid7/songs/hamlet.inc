    org $a000

    ins "songs/hamlet.bin"

    player_init=$a000
    player_play=$a003

    start_song=0
    max_song=1

    .def fastadsr

    org song_on_screen

    .sb "  Hamlet                                "
    .sb "  by Timo Taipalus (Abaddon)            "
    .sb "  (C) 2002 Damage                       "

