    org $aa00

    ins "songs/xenon.bin"

    player_init=$aab2
    player_play=$aa98

    start_song=0
    max_song=3

 ; the full monty ;)
;    .def need_mixforms
;    .def momhack
;    .def cn2hack

    org song_on_screen

    .sb " Xenon by David Whittaker, 1988         "
    .sb " C64 SID version by Paul Tonge, 1989    "
    .sb " atarisid conversion at 2021-06-08      "


