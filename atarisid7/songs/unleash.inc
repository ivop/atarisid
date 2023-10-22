    org $9000

    ins "songs/unleash.bin"

    player_init=$9000
    player_play=$9003

    start_song=0
    max_song=1

    .def softernoise


    org song_on_screen

    .sb "  Unleash The Fucking Fury              "
    .sb "  by Lasse Oorni (Cadaver)              "
    .sb "  (C) 2004 Cadaver                      "

