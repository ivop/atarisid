    org $a000

    ins "songs/slapmix.bin"

    player_init=$a000
    player_play=$a003

    start_song=0
    max_song=1

    org song_on_screen

    .sb "  The Slap Mix                          "
    .sb "  by Stellan Andersson (Dane)           "
    .sb "  (C) 2002 Crest                        "

