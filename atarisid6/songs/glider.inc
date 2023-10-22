    org $a000

    ins "songs/glider.bin"

    player_init=$b700
    player_play=$a003

    start_song=0
    max_song=3

    .def speedball_patches
    .def fastadsr

    org song_on_screen

    .sb "  Glider Rider                          "
    .sb "  by David Whittaker                    "
    .sb "  (C) 1986 Quicksilva                   "
