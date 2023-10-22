    org $a000

    ins "songs/ocean3.bin"

    player_init=$baa4
    player_play=$baad

    start_song=0
    max_song=1

;    .def fastadsr

    org song_on_screen

    .sb "  Ocean Loader 3                        "
    .sb "  by Peter Clarke                       "
    .sb "  (C) 1985 Ocean                        "
