    org $a000

    ins "songs/spellbound.bin"

    player_init=$a000
    player_play=$a012

    start_song=0
    max_song=3

    org song_on_screen

    .sb "  Spellbound                            "
    .sb "  by Rob Hubbard                        "
    .sb "  (C) 1986 MAD/Mastertronic             "
