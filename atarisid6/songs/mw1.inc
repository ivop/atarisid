    org $9000

    ins "songs/mw1.bin"

    player_init=$aa10
    player_play=$9000

    start_song=0
    max_song=12

    .def softernoise


    org song_on_screen

    .sb "  Metal Warrior                         "
    .sb "  by Lasse Oorni (Cadaver)              "
    .sb "  (C) 1999 Electric Harem               "

