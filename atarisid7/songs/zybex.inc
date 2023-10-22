    org $a0f0

    ins "songs/zybex.bin"

    player_init=$a0f0
    player_play=$a100

    start_song=0
    max_song=5

    .def zybex_patches
    .def fastadsr

    org song_on_screen

    .sb "  Zybex                                 "
    .sb "  by Adam Gilmore                       "
    .sb "  (C) 1988 Zeppelin Games               "
