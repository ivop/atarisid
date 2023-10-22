    org $a000

    ins "songs/syncopated.bin"

    player_init=$a000
    player_play=$a006

    start_song=0
    max_song=1

    .def fastadsr

    org song_on_screen

    .sb "  Syncopated                            "
    .sb "  by Thomas E. Petersen (Laxity)        "
    .sb "  (C) 1993-94 Vibrants                  "
