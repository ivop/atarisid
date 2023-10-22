    org $a000

    ins "songs/cobra.bin"

    player_init=$a800
    player_play=$a810

    start_song=0
    max_song=9

;    .def fastadsr

    org song_on_screen

    .sb "  Cobra                                 "
    .sb "  by Ben Daglish                        "
    .sb "  (C) 1986 Ocean                        "
