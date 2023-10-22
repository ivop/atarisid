    org $9000

    ins "songs/mythm.bin"

    player_init=$9000
    player_play=$9006

    start_song=0
    max_song=1



    org song_on_screen

    .sb "  Myth Mix                              "
    .sb "  by Jeroen Tel                         "
    .sb "  (C) 1989 Maniacs of Noise             "

