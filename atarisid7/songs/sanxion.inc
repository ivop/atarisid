    org $a000

    ins "songs/sanxion.bin"

    player_init=$ae00
    player_play=$ae20

    start_song=0
    max_song=2

    org song_on_screen

    .sb "  Sanxion                               "
    .sb "  by Rob Hubbard                        "
    .sb "  (C) 1987 Thalamus                     "
