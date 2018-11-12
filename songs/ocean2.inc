    org $a000

    ins "songs/ocean2.bin"

    player_init=$a000
    player_play=$a04e

    start_song=0
    max_song=1

;    .def fastadsr

    org song_on_screen

    .sb "  Ocean Loader 2                        "
    .sb "  by Martin Galway                      "
    .sb "  (C) 1985 Ocean                        "
