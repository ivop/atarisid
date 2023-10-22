    org $9000

    ins "songs/alloy.bin"

    player_init=$9000
    player_play=$9006

    start_song=0
    max_song=3

    org song_on_screen

    .sb "  Alloyrun                              "
    .sb "  by Jeroen Tel / Maniacs of Noise      "
    .sb "  (C) 1988 Starlight                    "

