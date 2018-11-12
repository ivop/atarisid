    org $a000

    ins "songs/metro.bin"

    player_init=$a003
    player_play=$a000

    start_song=0
    max_song=1

;    .def fastadsr

    org song_on_screen

    .sb "  Metro Dance                           "
    .sb "  by Chris Huelsbeck                    "
    .sb "  (C) 1988 Chris Huelsbeck              "
