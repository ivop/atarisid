    org $9000

    ins "songs/omahd.bin"

    player_init=$9000
    player_play=$9012

    start_song=0
    max_song=1

    .def softernoise
;    .def cn2hack



    org song_on_screen

    .sb "  One Man And His Droid                 "
    .sb "  by Rob Hubbard                        "
    .sb "  (C) 1985 Mastertronic                 "
