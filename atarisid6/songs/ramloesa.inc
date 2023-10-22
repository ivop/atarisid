    org $a000

    ins "songs/ramloesa.bin"

    player_init=$a000
    player_play=$a003

    start_song=0
    max_song=1

    org song_on_screen

    .sb "  Ramloesa                              "
    .sb "  by Torben Hansen (Metal)              "
    .sb "  (C) 1992 Flash Inc.                   "
