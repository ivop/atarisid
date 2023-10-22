    org $9000

    ins "songs/comets.bin"

    player_init=$9000
    player_play=$900c

    start_song=0
    max_song=2

    .def softernoise
;    .def cn2hack



    org song_on_screen

    .sb "  Crazy Comets                          "
    .sb "  by Rob Hubbard                        "
    .sb "  (C) 1985 Martech                      "
