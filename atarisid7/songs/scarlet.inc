    org $a000

    ins "songs/scarlet.bin"

    player_init=$a000
    player_play=$a003

    start_song=0
    max_song=1

    org song_on_screen

    .sb "  Scarlet                               "
    .sb "  by Thomas Mogensen (DRAX)             "
    .sb "  (C) 1990 Vibrants                     "
