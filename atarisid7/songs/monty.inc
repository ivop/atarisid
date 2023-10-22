    org $9000

    ins "songs/monty.bin"

    player_init=$9000
    player_play=$9003

    start_song=0
    max_song=3

    .def softernoise



    org song_on_screen

    .sb "  Monty On The Run                      "
    .sb "  by Rob Hubbard                        "
    .sb "  (C) 1985 Gremlin Graphics             "
