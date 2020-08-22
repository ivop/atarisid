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

    .sb "  Chordian by Jens-Christian Huus       "
    .sb "  (c)1991 Vibrants                      "
    .sb "  atarisid conversion 2020-08-22        "


