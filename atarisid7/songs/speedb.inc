    org $a010

    ins "songs/speedb.bin"

    player_init=$a010
    player_play=$a147

    start_song=0
    max_song=7

    .def speedball_patches
    .def fastadsr

    org song_on_screen

    .sb "  Speedball                             "
    .sb "  by David Whittaker                    "
    .sb "  (C) 1989 Imageworks                   "
