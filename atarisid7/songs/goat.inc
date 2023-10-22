    org $90fa

    ins "songs/goat.bin"

    player_init=$90fa
    player_play=$9100

    start_song=0
    max_song=1

    .def softernoise


    org song_on_screen

    .sb "  GoatTracker Example (MW1 Title)       "
    .sb "  by Lasse Oorni (Cadaver)              "
    .sb "  (C) 2001 Electric Harem               "

