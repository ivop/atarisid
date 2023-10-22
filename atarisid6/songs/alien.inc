    org $a000

    ins "songs/alien.bin"

    player_init=$a000
    player_play=$a003

    start_song=0
    max_song=1

    org song_on_screen

    .sb "  Alien Seahorses Invading Heaven       "
    .sb "  by Hein Holt (Hein)                   "
    .sb "  (C) 2005 Vision                       "

