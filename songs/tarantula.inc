    org $a000

    ins "songs/tarantula.bin"

    player_init=$a000
    player_play=$a003

    start_song=0
    max_song=1

    org song_on_screen

    .sb "  Tarantula                             "
    .sb "  by Lasse Oorni (Cadaver)              "
    .sb "  (C) 2003 Cadaver                      "

