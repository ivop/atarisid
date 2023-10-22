    org $90f8

    ins "songs/mom.bin"

    player_init=$9100
    player_play=$9106

    start_song=0
    max_song=3

    .def softernoise
;    .def cn2hack
    .def momhack



    org song_on_screen

    .sb "  The Master Of Magic                   "
    .sb "  by Rob Hubbard                        "
    .sb "  (C) 1985 MAD/Mastertronic             "
