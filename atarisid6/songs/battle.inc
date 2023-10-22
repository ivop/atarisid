    org $90e7

    ins "songs/battle.bin"

    player_init=$b610
    player_play=$b613

    start_song=0
    max_song=5

    .def fastadsr

    org song_on_screen

    .sb "  Battle Ships                          "
    .sb "  by Mark Cooksey                       "
    .sb "  (C) 1987 Elite                        "
