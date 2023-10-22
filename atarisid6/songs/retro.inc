    org $9000

    ins "songs/retro.bin"

    player_init=$9000
    player_play=$9003

    start_song=0
    max_song=1

    org song_on_screen

    .sb "  Retrograd                             "
    .sb "  by Ari-Pekka Paljakka (Zardax)        "
    .sb "  (C) 1996 Relax Magazine               "

