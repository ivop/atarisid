    org $a000

    ins "songs/lf.bin"

    player_init=$a0b9
    player_play=$a0bf

    start_song=0
    max_song=1



    org song_on_screen

    .sb "  Lightforce                            "
    .sb "  by Rob Hubbard                        "
    .sb "  (C) 1986 FTL                          "
