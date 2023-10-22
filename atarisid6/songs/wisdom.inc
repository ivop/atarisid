    org $9000

    ins "songs/wisdom.bin"

    player_init=$9000
    player_play=$9003

    start_song=0
    max_song=1

    .def softernoise
;    .def cn2hack



    org song_on_screen

    .sb "  Wisdom                                "
    .sb "  by Thomas E. Petersen (Laxity)        "
    .sb "  (C) 1993 Vibrants                     "
