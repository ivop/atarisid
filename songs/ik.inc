    org $a000

    ins "songs/ik.bin"

    player_init=$a000
    player_play=$a00c

    start_song=0
    max_song=2

    .def softernoise


    org song_on_screen

    .sb "  International Karate                  "
    .sb "  by Rob Hubbard                        "
    .sb "  (C) 1986 System 3                     "

