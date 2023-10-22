/*
 * SID/NSF/SAP Disassembler
 *
 * v1.0 -- Copyright (C) 2003 by Gufino <bugsman@libero.it>
 * v2.0 -- Copyright (C) 2009 by Ivo van Poorten <ivop@free.fr>
 * v2.1 -- Copyright (C) 2012 by Ivo van Poorten <ivop@free.fr>
 * v2.2 -- Copyright (C) 2015 by Ivo van Poorten <ivop@free.fr>
 *
 * Compile with:        gcc -O3 -o siddasm2 siddasm2.c
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define MEMSIZ 65536
#define TABSIZ 1024
#define TMPSIZ 64

#define GET8(f)     (fgetc(f))
#define GET16LE(f)  (GET8(f)+(GET8(f)<<8))
#define GET16BE(f)  ((GET8(f)<<8)+GET8(f))
#define GET32LE(f)  (GET16LE(f)+(GET16LE(f)<<16))
#define GET32BE(f)  ((GET16BE(f)<<16)+GET16BE(f))
#define fskip(f,x)  fseek(f,x,SEEK_CUR)

#define TAGLE(a,b,c,d)  (a|(b<<8)|(c<<16)|(d<<24))
#define TAGBE(a,b,c,d)  (d|(c<<8)|(b<<16)|(a<<24))

#define DECODE_MODE_ON  1
#define DECODE_MODE_OFF 0
#define LLABEL          ((char*)-1)

uint16_t load_address, init_address, play_address, length;

static int j_to_do, block_end;
static uint16_t pos, starts[TABSIZ], ends[TABSIZ];
static uint8_t mem[MEMSIZ], memmark[MEMSIZ];
static char *memlabel[MEMSIZ];

static void exit_error(char *message) {
    fprintf(stderr, "%s", message);
    exit(1);
}

static inline unsigned char read_opcode(int decode_mode) {
    if (decode_mode) memmark[pos] = 1;
    return mem[pos++];
}

static const char params[256] = {
    0,1,0,0,0,1,1,0,0,1,0,0,0,2,2,0,1,1,0,0,0,1,1,0,0,2,0,0,0,2,2,0,
    2,1,0,0,1,1,1,0,0,1,0,0,2,2,2,0,1,1,0,0,0,1,1,0,0,2,0,0,0,2,2,0,
    0,1,0,0,0,1,1,0,0,1,0,0,2,2,2,0,1,1,0,0,0,1,1,0,0,2,0,0,0,2,2,0,
    0,1,0,0,0,1,1,0,0,1,0,0,2,2,2,0,1,1,0,0,0,1,1,0,0,2,0,0,0,2,2,0,
    0,1,0,0,1,1,1,0,0,0,0,0,2,2,2,0,1,1,0,0,1,1,1,0,0,2,0,0,0,2,0,0,
    1,1,1,0,1,1,1,0,0,1,0,0,2,2,2,0,1,1,0,0,1,1,1,0,0,2,0,0,2,2,2,0,
    1,1,0,0,1,1,1,0,0,1,0,0,2,2,2,0,1,1,0,0,0,1,1,0,0,2,0,0,0,2,2,0,
    1,1,0,0,1,1,1,0,0,1,0,0,2,2,2,0,1,1,0,0,0,1,1,0,0,2,0,0,0,2,2,0
};

static const char * const strings[256] = {
    "brk","ora ($%2.2x,x)","ill","ill","ill","ora $%2.2x","asl $%2.2x","ill",
    "php","ora #$%2.2x","asl","ill","ill","ora $%4.4x","asl $%4.4x","ill",
    "bpl $%2.2x","ora ($%2.2x),y","ill","ill","ill","ora $%2.2x,x",
    "asl $%2.2x,x","ill","clc","ora $%4.4x,y","ill","ill","ill","ora $%4.4x,x",
    "asl $%4.4x,x","ill","jsr $%4.4x","and ($%2.2x,x)","ill","ill",
    "bit $%2.2x","and $%2.2x","rol $%2.2x","ill","plp","and #$%2.2x","rol",
    "ill","bit $%4.4x","and $%4.4x","rol $%4.4x","ill","bmi $%2.2x",
    "and ($%2.2x),y","ill","ill","ill","and $%2.2x,x","rol $%2.2x,x","ill",
    "sec","and $%4.4x,y","ill","ill","ill","and $%4.4x,x","rol $%4.4x,x","ill",
    "rti","eor ($%2.2x,x)","ill","ill","ill","eor $%2.2x","lsr $%2.2x","ill",
    "pha","eor #$%2.2x","lsr","ill","jmp $%4.4x","eor $%4.4x","lsr $%4.4x",
    "ill","bvc $%2.2x","eor ($%2.2x),y","ill","ill","ill","eor $%2.2x,x",
    "lsr $%2.2x,x","ill","cli","eor $%4.4x,y","ill","ill","ill","eor $%4.4x,x",
    "lsr $%4.4x,x","ill","rts","adc ($%2.2x,x)","ill","ill","ill","adc $%2.2x",
    "ror $%2.2x","ill","pla","adc #$%2.2x","ror","ill","jmp ($%4.4x)",
    "adc $%4.4x","ror $%4.4x","ill", "bvs $%2.2x","adc ($%2.2x),y","ill",
    "ill", "ill","adc $%2.2x,x","ror $%2.2x,x","ill", "sei","adc $%4.4x,y",
    "ill","ill", "ill","adc $%4.4x,x","ror $%4.4x,x","ill", "ill",
    "sta ($%2.2x,x)","ill","ill", "sty $%2.2x","sta $%2.2x","stx $%2.2x",
    "ill", "dey","ill","txa","ill", "sty $%4.4x","sta $%4.4x","stx $%4.4x",
    "ill", "bcc $%2.2x","sta ($%2.2x),y","ill","ill", "sty $%2.2x,x",
    "sta $%2.2x,x","stx $%2.2x,y","ill", "tya","sta $%4.4x,y","txs","ill",
    "ill","sta $%4.4x,x","ill","ill", "ldy #$%2.2x","lda ($%2.2x,x)",
    "ldx #$%2.2x","ill", "ldy $%2.2x","lda $%2.2x","ldx $%2.2x","ill","tay",
    "lda #$%2.2x","tax","ill", "ldy $%4.4x","lda $%4.4x","ldx $%4.4x","ill",
    "bcs $%2.2x","lda ($%2.2x),y","ill","ill", "ldy $%2.2x,x","lda $%2.2x,x",
    "ldx $%2.2x,y","ill", "clv","lda $%4.4x,y","tsx","ill", "ldy $%4.4x,x",
    "lda $%4.4x,x","ldx $%4.4x,y","ill", "cpy #$%2.2x","cmp ($%2.2x,x)","ill",
    "ill", "cpy $%2.2x","cmp $%2.2x","dec $%2.2x","ill", "iny","cmp #$%2.2x",
    "dex","ill", "cpy $%4.4x","cmp $%4.4x","dec $%4.4x","ill", "bne $%2.2x",
    "cmp ($%2.2x),y","ill","ill", "ill","cmp $%2.2x,x","dec $%2.2x,x","ill",
    "cld","cmp $%4.4x,y","ill","ill", "ill","cmp $%4.4x,x","dec $%4.4x,x",
    "ill", "cpx #$%2.2x","sbc ($%2.2x,x)","ill","ill", "cpx $%2.2x",
    "sbc $%2.2x","inc $%2.2x","ill", "inx","sbc #$%2.2x","nop","ill",
    "cpx $%4.4x","sbc $%4.4x","inc $%4.4x","ill", "beq $%2.2x",
    "sbc ($%2.2x),y","ill","ill", "ill","sbc $%2.2x,x","inc $%2.2x,x","ill",
    "sed","sbc $%4.4x,y","ill","ill","ill","sbc $%4.4x,x","inc $%4.4x,x","ill"
};

// L_xxxx labels
static inline void set_Llabel(int addr) {
    if (!memlabel[addr]) memlabel[addr] = LLABEL;
}

// Text labels
static inline void set_Tlabel(int addr, char * const label) {
    memlabel[addr] = label;
}

static char *get_label(int addr) {
    static char temps[TMPSIZ];
    if (!memlabel[addr])
        snprintf(temps, TMPSIZ-1, "$%4.4x", addr);
    else if (memlabel[addr] == LLABEL)
        snprintf(temps, TMPSIZ-1, "L_%4.4X", addr);
    else
        snprintf(temps, TMPSIZ-1, "%s", memlabel[addr]);
    return temps;
}

static void add_start_addr(int addr) {
    static int s_ins = 0;
    if (s_ins >= TABSIZ)
        exit_error("error: too many jumps, dump aborted\n");
    starts[s_ins++] = addr;
    j_to_do++;
    set_Llabel(addr);
}

static void add_end_addr(int addr) {
    static int e_ins = 0;
    if (e_ins >= TABSIZ)
        exit_error("error: too many jumps, dump aborted\n");
    ends[e_ins++] = addr;
}

static void decode_opcode(unsigned char opcode, int decode_mode, FILE *fp) {
    int byte_param = 0, word_param = 0, xtra = 0, app_pos, op_pos = pos-1;

    switch (params[opcode]) {
    case 1: {
        char temps[TMPSIZ] = "";
        byte_param = mem[pos++];
        if (decode_mode) memmark[pos] = 1;

        switch (opcode) {
        case 0x10:      // BPL
        case 0x30:      // BMI
        case 0x50:      // BVC
        case 0x70:      // BVS
        case 0x90:      // BCC
        case 0xb0:      // BCS
        case 0xd0:      // BNE
        case 0xf0:      // BEQ
            app_pos = pos + byte_param - (byte_param > 0x7f ? 0x100 : 0);
            snprintf(temps, TMPSIZ-1, "%3.3s %s", strings[opcode], get_label(app_pos));
            xtra++;
            break;
        default:
            snprintf(temps, TMPSIZ-1, strings[opcode], byte_param);
            break;
        }
        fprintf(fp, "    %-32.32s ; %4.4x: .byte $%2.2x,$%2.2x\n", temps, op_pos, opcode, byte_param);
        if (xtra) fprintf(fp, "\n");
        break; }

    case 2: {
        char temps[TMPSIZ], temps2[TMPSIZ] = "";

        if (decode_mode) memmark[pos] = memmark[pos+1] = 1;
        byte_param = mem[pos+1];
        word_param = mem[pos] + ((unsigned int)byte_param<<8);
        pos += 2;
        snprintf(temps, TMPSIZ-1, strings[opcode], word_param);

        if (memlabel[word_param]) {
            char *x = strchr(temps, '$'), *y = x + 5;
            assert(x);
            *x = 0;
            snprintf(temps2, TMPSIZ-1, "%s%s%s", temps, get_label(word_param), y);
        } else {
            snprintf(temps2, TMPSIZ-1, "%s", temps);
        }
        fprintf(fp, "    %-32.32s ; %4.4x: .byte $%2.2x,$%2.2x,$%2.2x\n", temps2, op_pos, opcode, word_param&0xff, byte_param);

        if (opcode == 0x20 || opcode == 0x4c || opcode == 0x6c)
            fprintf(fp, "\n");
        set_Llabel(word_param);
        break; }

    default:
        fprintf(fp, "    %-32.32s ; %4.4x: .byte $%2.2x\n", strings[opcode], op_pos, opcode);

        if (opcode == 0x60) fprintf(fp, "\n");
        break;
    }

    if (decode_mode) {
        switch (opcode) {
        case 0x10:      // BPL
        case 0x30:      // BMI
        case 0x50:      // BVC
        case 0x70:      // BVS
        case 0x90:      // BCC
        case 0xb0:      // BCS
        case 0xd0:      // BNE
        case 0xf0:      // BEQ
            app_pos = pos + byte_param - (byte_param > 0x7f ? 0x100 : 0);
            set_Llabel(app_pos);
            if (!memmark[app_pos]) {
                add_start_addr(app_pos);
                memmark[app_pos] = 1;
            }
            break;
        case 0x4c:      // JMP aaaa
            set_Llabel(word_param);
            if (!memmark[word_param]) {
                add_start_addr(word_param);
                add_end_addr(pos);
                block_end = 1;
            }
        break;
        case 0x6c:      // JMP (aaaa)
            fprintf(fp, "; JMP defined at run-time: possibly incorrect code dumping!\n");
            break;
        case 0x20:      // JSR aaaa
            set_Llabel(word_param);
            if (!memmark[word_param]) {
                add_start_addr(word_param);
                memmark[word_param] = 1;
            }
            break;
        case 0x60:      // RTS
            add_end_addr(pos);
            block_end = 1;
            break;
        default:
            break;
        }
    }
}

static void output(int start_addr, int len, FILE *fp) {
    int written = 0;

    fprintf(fp, "\n    * = $%4x\n\n", load_address);

    len += (pos = start_addr);

    while(pos<len && pos) {
        if (memlabel[pos]) {
            if (written) {
                fprintf(fp, "\n\n");
                written = 0;
            }
            if (memlabel[pos] == LLABEL) fprintf(fp, "L_%4.4X\n", pos);
            else                         fprintf(fp, "%s\n", memlabel[pos]);
        }
        if (memmark[pos]) {
            if (written) {
                fprintf(fp, "\n\n");
                written = 0;
            }
            decode_opcode(read_opcode(DECODE_MODE_OFF),DECODE_MODE_OFF,fp);
        } else {
            if (written == 16) {
                fprintf(fp, "\n");
                written = 0;
            }
            if (!written)
                fprintf(fp, "    .byte $%2.2x", read_opcode(DECODE_MODE_OFF));
            else
                fprintf(fp, ",$%2.2x", read_opcode(DECODE_MODE_OFF));
            written++;
        }
    }
}

static void dump_code(FILE *fp) {
    int cur_section, j = 0;

    block_end = 0;

    set_Tlabel(init_address, "init");
    set_Tlabel(play_address, "play");

    add_start_addr(init_address);
    if (init_address != play_address) add_start_addr(play_address);

    while(j_to_do) {
        pos = starts[j];
        block_end = 0;
        cur_section = pos;
        while (!block_end)
            decode_opcode(read_opcode(DECODE_MODE_ON),DECODE_MODE_ON,fp);
        j++;
        j_to_do--;
    };
}

static long get_file_length(FILE *f) {
    long l = 0, s = 0;

    s = ftell(f);
    fseek(f, 0, SEEK_END);
    l = ftell(f);
    fseek(f, s, SEEK_SET);
    return l;
}

static void read_psid(FILE *f) {
    int version, songs, startsong;
    long len = get_file_length(f);
                                    // "PSID" already checked by caller
    version      = GET16BE(f);
    len         -= GET16BE(f);      // data_offset
    load_address = GET16BE(f);
    init_address = GET16BE(f);
    play_address = GET16BE(f);
    if ((songs = GET16BE(f)) < 1)
        exit_error("Invalid number of songs!!!\n");
    startsong  = GET16BE(f);
    if (startsong < 1 || startsong > songs)
        exit_error("Invalid starting song\n");
    fskip(f,4);                     // speed
    fskip(f,32*3);                  // name, author, copyright
    if (version == 2) fskip(f,6);   // flags(16be), reserved

    if (!load_address) load_address = GET16LE(f);

    fread(mem + load_address, 1, len, f);

    len -= 2;
    if (len >= MEMSIZ) exit_error("file too big\n");

    length = len;
}

static void read_nsf(FILE *f) {
    fskip(f,4);                 // 01Ah, version, songs, starting song
    load_address = GET16LE(f);
    init_address = GET16LE(f);
    play_address = GET16LE(f);
    fskip(f,32*3);              // name, artist, copyright
    fskip(f,2);                 // NTSC speed in microseconds
    fskip(f,8);                 // Initial Bank Switch values
    fskip(f,2);                 // PAL speed in microseconds
    fskip(f,2);                 // PAL/NTSC flags, Extra Sound Chip flags
    fskip(f,4);                 // reserved

    length = fread(mem+load_address, 1, 65536-load_address, f);
}

static void read_sap(FILE *f) {
    int x;
    unsigned int init = 0, play = 0;
    char type = -1;

    fskip(f,1);                 // lf

    while ( (x=GET8(f)) != 0xff) {
        ungetc(x,f);
        fscanf(f, "INIT %x", &init);
        fscanf(f, "PLAYER %x", &play);
        fscanf(f, "TYPE %c", &type);
        while (GET8(f) != '\n');
    }
    
    if (!init) exit_error("no init address found\n");
    if (!play) exit_error("no play address found\n");
    if (type != 'B' && type != 'C')
        exit_error("unsupported SAP type\n");
    init_address = init;
    play_address = play;

    fskip(f,1);                 // 0xff
    load_address = GET16LE(f);
    length       = GET16LE(f) - load_address + 1;
    fread(mem+load_address, 1, length, f);
}

static const struct label {
    uint16_t addr;
    char *label;
} sid_labels[] = {
    { 0xd400, "SIDV1FREQLO" },  { 0xd401, "SIDV1FREQHI" },
    { 0xd402, "SIDV1PWLO" },    { 0xd403, "SIDV1PWHI" },
    { 0xd404, "SIDV1CTRL" },    { 0xd405, "SIDV1AD" },
    { 0xd406, "SIDV1SR" },
    { 0xd407, "SIDV2FREQLO" },  { 0xd408, "SIDV2FREQHI" },
    { 0xd409, "SIDV2PWLO" },    { 0xd40a, "SIDV2PWHI" },
    { 0xd40b, "SIDV2CTRL" },    { 0xd40c, "SIDV2AD" },
    { 0xd40d, "SIDV2SR" },
    { 0xd40e, "SIDV3FREQLO" },  { 0xd40f, "SIDV3FREQHI" },
    { 0xd410, "SIDV3PWLO" },    { 0xd411, "SIDV3PWHI" },
    { 0xd412, "SIDV3CTRL" },    { 0xd413, "SIDV3AD" },
    { 0xd414, "SIDV3SR" },
    { 0xd415, "SIDFCLO" },      { 0xd416, "SIDFCHI" },
    { 0xd417, "SIDRESFILT" },   { 0xd418, "SIDMODEVOL" },
    { 0xd419, "SIDPOTX" },      { 0xd41a, "SIDPOTY" },
    { 0xd41b, "SIDOSC3" },      { 0xd41c, "SIDENV3" },
    { 0, NULL }
};

static const struct label nes_labels[] = {
    { 0x4000, "NESSW1REG1" },   { 0x4001, "NESSW1REG2" },
    { 0x4002, "NESSW1REG3" },   { 0x4003, "NESSW1REG4" },
    { 0x4004, "NESSW2REG1" },   { 0x4005, "NESSW2REG2" },
    { 0x4006, "NESSW2REG3" },   { 0x4007, "NESSW2REG4" },
    { 0x4008, "NESTRIREG1" },   { 0x400a, "NESTRIREG3" },
    { 0x400b, "NESTRUREG4" },   { 0x400c, "NESNOISEREG1" },
    { 0x400e, "NESNOISEREG3" }, { 0x400f, "NESNOISEREG4" },
    { 0x4015, "NESCHNENABLE" },
    { 0, NULL }
};

static const struct label sap_labels[] = {
    { 0xd200, "AUDF1" },        { 0xd201, "AUDC1" },
    { 0xd202, "AUDF2" },        { 0xd203, "AUDC2" },
    { 0xd204, "AUDF3" },        { 0xd205, "AUDC3" },
    { 0xd206, "AUDF4" },        { 0xd207, "AUDC4" },
    { 0xd208, "AUDCTL" },       { 0xd20a, "RANDOM" },
    { 0, NULL }
};

static void init_labels(const struct label *lp) {
    while (lp->label) {
        set_Tlabel(lp->addr, lp->label);
        lp++;
    }
}

int main(int argc, char **argv) {
    FILE *fp;
    const struct label *lp = NULL;

    setvbuf(stdout, NULL, _IONBF, 0);

    argc--;
    if (!argc) {
        printf("Usage: siddasm2 fubar.sid > output.asm\n");
        exit(1);
    }
    fprintf(stderr,"SID/NSF/SAP Disassembler, Version 2.2\n");
    fprintf(stderr,"Copyright (C) 2003, Gufino/GufoSoft\n");
    fprintf(stderr,"Copyright (C) 2009, 2012, 2015 Ivo van Poorten\n");

    if (!(fp = fopen(argv[1], "rb"))) {
        fprintf(stderr,"Unable to open input file %s!!!\n", argv[1]);
        exit(1);
    }

    switch (GET32BE(fp)) {
    case TAGBE('P','S','I','D'):
        read_psid(fp);
        lp = sid_labels;
        break;
    case TAGBE('S','A','P','\r'):
        read_sap(fp);
        lp = sap_labels;
        break;
    case TAGBE('N','E','S','M'):
        read_nsf(fp);
        lp = nes_labels;
        break;
    default:
        exit_error("unknown file type\n");
        break;
    }
    fclose(fp);
    init_labels(lp);

    if (!(fp = fopen("/dev/null", "wb")))
        if (!(fp = fopen("nul", "wb")))
            exit_error("unable to open /dev/null!\n");

    dump_code(fp);
    fclose(fp);

    printf("; Generated by SID/NSF/SAP Disassembler, Version 2.1\n;\n");
    printf("; filename: %s\n\n", argv[1]);

    for (;lp->label; lp++)
        printf("%s = $%04x\n", lp->label, lp->addr);

    output(load_address, length, stdout);

    printf("\n");
    return (0);
}
