    org $a000

    ins "songs/vikings.bin"

    player_init=$ae00
    player_play=$af62

    start_song=3
    max_song=6

;    .def fastadsr

    org song_on_screen

    .sb "  The Vikings                           "
    .sb "  by Ben Daglish                        "
    .sb "  (C) 1987 Kele Line                    "
