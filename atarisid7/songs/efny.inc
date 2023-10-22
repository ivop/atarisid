    org $9000

    ins "songs/efny.bin"

    player_init=$9000
    player_play=$9003

    start_song=0
    max_song=1



    org song_on_screen

    .sb "  Escape From New York                  "
    .sb "  by Lasse Oorni (Cadaver)              "
    .sb "  (C) 1999 Cadaver                      "

