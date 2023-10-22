    org $a038

    ins "songs/loopz.bin"

    player_init=$a038
    player_play=$a1a6

    start_song=0
    max_song=9

    .def speedball_patches
    .def fastadsr

    org song_on_screen

    .sb "  Loopz                                 "
    .sb "  by David Whittaker                    "
    .sb "  (C) 1991 Audiogenic                   "
