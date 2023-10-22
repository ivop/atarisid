    org $a000

    ins "songs/ninjac.bin"

    player_init=$a9fa
    player_play=$a000

    start_song=0
    max_song=5

    .def ninjac_patches
    .def fastadsr

    org song_on_screen

    .sb "  Ninja Commando                        "
    .sb "  by Adam Gilmore                       "
    .sb "  (C) 1989 Zeppelin Games               "
