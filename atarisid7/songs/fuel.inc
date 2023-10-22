    org $a0f0

    ins "songs/fuel.bin"

    player_init=$a179
    player_play=$a1b5

    start_song=0
    max_song=1

;    .def fastadsr

    org song_on_screen

    .sb "  Alternative Fuel                      "
    .sb "  by Jeroen Tel                         "
    .sb "  (C) 2004 Maniacs of Noise             "

