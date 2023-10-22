    org $a000

    ins "songs/cn.bin"

    player_init=$a000
    player_play=$a006

    start_song=0
    max_song=2

;    .def fastadsr

    org song_on_screen

    .sb "  Cybernoid                             "
    .sb "  by Jeroen Tel / Maniacs of Noise      "
    .sb "  (C) 1988 Hewson                       "

