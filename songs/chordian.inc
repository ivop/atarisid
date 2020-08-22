    org $a000

    ins "songs/chordian.bin"

    player_init=$a000
    player_play=$a003

    start_song=0
    max_song=0

 ; the full monty ;)
    .def need_mixforms
    .def momhack
    .def cn2hack

    org song_on_screen

    .sb "  Chordian                              "
    .sb "  by Jens-Christian Huus                "
    .sb "  1991 Vibrants                         "


