    org $a000

    ins "songs/ocean1.bin"

    player_init=$b428
    player_play=$a003

    start_song=0
    max_song=1

;    .def fastadsr

    org song_on_screen

    .sb "  Ocean Loader 1                        "
    .sb "  by Martin Galway                      "
    .sb "  (C) 1985 Ocean                        "
