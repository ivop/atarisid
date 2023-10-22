    org $9000

    ins "songs/metal.bin"

    player_init=$9000
    player_play=$9003

    start_song=0
    max_song=4

    .def softernoise


    org song_on_screen

    .sb "  Nintedo Metal                         "
    .sb "  by Lasse Oorni (Cadaver)              "
    .sb "  (C) 2004 Covert Bitops                "

