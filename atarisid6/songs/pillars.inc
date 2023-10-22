    org $a000

    ins "songs/pillars.bin"

    player_init=$bf00
    player_play=$bf18

    start_song=2
    max_song=3

    org song_on_screen

    .sb "  Noisy Pillars                         "
    .sb "  by Jeroen Tel                         "
    .sb "  (C) 1987 Manicas of Noise             "


