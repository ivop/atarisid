    org $a000

    ins "songs/pool.bin"

    player_init=$a000
    player_play=$a003

    start_song=0
    max_song=1

    org song_on_screen

    .sb "  Pool Party                            "
    .sb "  by Volker Meitz (PRI)                 "
    .sb "  (C) 1993 Oxyron                       "


