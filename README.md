# atarisid

Software SID emulation for the Atari 8-bit (6502 @ 1.8MHz + POKEY) 

atarisid6 contains the slightly less than 4-bit per channel, three channels at 15.7kHz player.

atarisid7 contains the newer three channels mixed to one 8-bit channel at 15.7kHz player.

Both utilize the original C64 player routines that have been modified to write to shadow SID registers. After that the emulation core converts the values suitable for wave synthesis and ADSR emulation.

v7 sounds better, but might miss some noise here and there. v6 switches between wave synthesis and Pokey's own noise generator on each channel. v7 uses only a single spare channel to play noise. The other three are taken. Two for the 8-bit PCM4+4 channel, and one for the 50Hz timer to sync the replay routine. So if more than one player uses noise, only one is played. In practice this has not been a real problem so far.

Note on emulation: the only Atari 8-bit emulator that runs both players correctly is Altirra. atari800 has an incomplete Pokey emulation. v6 sort of works, even though the interrupts fire at the wrong time. Best enjoyed on real hardware ;)

# credits

All code is Copyright (C) 2012-2016,2023 by Ivo van Poorten. Licensed under the terms of the General Public License version 3. Not any later.
