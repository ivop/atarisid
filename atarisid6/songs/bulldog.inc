    org $a000

    ins "songs/bulldog.bin"

    player_init=$a5f0
    player_play=$a601

    start_song=0
    max_song=1

;    .def fastadsr

    org song_on_screen

    .sb "  Bulldog                               "
    .sb "  by Ben Daglish                        "
    .sb "  (C) 1986 Gremlin Graphics             "
