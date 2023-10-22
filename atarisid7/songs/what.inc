    org $9000

    ins "songs/what.bin"

    player_init=$9000
    player_play=$9003

    start_song=0
    max_song=1

    .def softernoise


    org song_on_screen

    .sb "  What Have I Done To...                "
    .sb "  by Reyn Ouwehand                      "
    .sb "  (C) 1990 Reyn Ouwehand                "

