    org $a000

    ins "songs/ik+.bin"

    player_init=$b150
    player_play=$b17c

    start_song=0
    max_song=3

    .def softernoise


    org song_on_screen

    .sb "  IK+                                   "
    .sb "  by Rob Hubbard                        "
    .sb "  (C) 1987 System 3                     "

