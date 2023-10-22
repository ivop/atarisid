    org $9000

    ins "songs/jt42.bin"

    player_init=$9000
    player_play=$9003

    start_song=0
    max_song=3

    .def softernoise


    org song_on_screen

    .sb "  JT42                                  "
    .sb "  by Jeroen Tel                         "
    .sb "  (C) 1990 Maniacs of Noise             "

