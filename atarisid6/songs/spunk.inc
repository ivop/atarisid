    org $a000

    ins "songs/spunk.bin"

    player_init=$a000
    player_play=$a003

    start_song=0
    max_song=1

    org song_on_screen

    .sb "  Spunk                                 "
    .sb "  by Thomas Mogensen (DRAX)             "
    .sb "  (C) 2006 Maniacs of Noise             "
