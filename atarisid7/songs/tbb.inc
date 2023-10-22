    org $a000

    ins "songs/tbb.bin"

    player_init=$a000
    player_play=$a003

    start_song=0
    max_song=32

    .def fastadsr

    org song_on_screen

    .sb "  Thing Bounces Back                    "
    .sb "  by Ben Daglish                        "
    .sb "  (C) 1987 Gremlin Graphics             "
