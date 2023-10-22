    org $a000

    ins "songs/nofilter.bin"

    player_init=$a000
    player_play=$a003

    start_song=0
    max_song=1

    .def fastadsr

    org song_on_screen

    .sb "  No Filter                             "
    .sb "  by Jens-Christian Huus                "
    .sb "  (C) 1988-89 Vibrants                  "
