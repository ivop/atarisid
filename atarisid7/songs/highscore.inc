    org $a000

    ins "songs/highscore.bin"

    player_init=$a000
    player_play=$a006

    start_song=0
    max_song=1

    .def fastadsr

    org song_on_screen

    .sb "  Highscore                             "
    .sb "  by Thomas E. Petersen (Laxity)        "
    .sb "  (C) 1993-94 Vibrants                  "
