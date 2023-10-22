    org $a000

    ins "songs/groove.bin"

    player_init=$a000
    player_play=$a003

    start_song=0
    max_song=1

    org song_on_screen

    .sb "  Groove                                "
    .sb "  by Tomas Danko                        "
    .sb "  (C) 1993 Tomas Danko                  "
