    org $9000

    ins "songs/commando.bin"

    player_init=$9f80
    player_play=$9012

    start_song=0
    max_song=2

    .def softernoise
;    .def cn2hack



    org song_on_screen

    .sb "  Commando                              "
    .sb "  by Rob Hubbard                        "
    .sb "  (C) 1985 Elite                        "
