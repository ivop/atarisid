    org $a000

    ins "songs/sports.bin"

    player_init=$bf80
    player_play=$a000

    start_song=25
    max_song=35

    .def zybex_patches
;    .def fastadsr

    org song_on_screen

    .sb "  Hyper Sports                          "
    .sb "  by Martin Galway                      "
    .sb "  (C) 1985 Imagine/Konami               "
