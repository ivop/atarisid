    org $a0d3

    ins "songs/kinetix.bin"

    player_init=$b800
    player_play=$a0d9

    start_song=1
    max_song=3

    .def fastadsr

    org song_on_screen

    .sb "  Kinetix                               "
    .sb "  by Jeroen Tel / Maniacs of Noise      "
    .sb "  (C) 1988 Digital Design               "

