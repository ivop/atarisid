#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#if 1
// 0 1 2 3 4 5 [6] 7 8 9 10 11 12       distorts? max. 36
#define SILENCE     6
#define AMPLITUDE1  2
#define AMPLITUDE2  4
#define AMPLITUDE3  6
#else
// 0 1 2 3 4 [5] 6 7 8 9 10                       max. 30
#define SILENCE     5
#define AMPLITUDE1  1
#define AMPLITUDE2  3
#define AMPLITUDE3  5
#endif

static const int BASE[3] = { (SILENCE-AMPLITUDE1),
                             (SILENCE-AMPLITUDE2),
                             (SILENCE-AMPLITUDE3)                           };
static const int VOL[3]  = { (SILENCE+AMPLITUDE1) - (SILENCE-AMPLITUDE1),
                             (SILENCE+AMPLITUDE2) - (SILENCE-AMPLITUDE2),
                             (SILENCE+AMPLITUDE3) - (SILENCE-AMPLITUDE3)    };

static int tri[3][512], saw[3][512], sawtri[3][512], noise[3][256];
static int pulse[4][3][256], silence[256], mixforms, experimental;

static void print(int *a, char *s) {
    int i, j;

    // output compressed: count-1, byte
    // printf("%s\n", s);
    printf("    dta ");
    j = 1;
    for (i=0; i<255; i++, j++) {
        if (a[i] != a[i+1]) {
            printf("0x%02x, 0x%02x, ", j-1, a[i]+0x10);
            j = 0;
        }
    }
    printf("0x%02x, 0x%02x\n", j-1, a[i]+0x10);
}

int main(int argc, char **argv) {
    int i, j, k;

    if (argc!=2) {
usage:
        fprintf(stderr, "specify 0 (small) or 1 (mixforms)\n");
        fprintf(stderr, "specify 2 for experimental waveforms\n");
        exit(1);
    }

    if (atol(argv[1]) == 1)         mixforms = 1;
    else if (atol(argv[1]) == 2)    experimental = 1;
    else if (atol(argv[1]) >  2)    goto usage;

  if (!experimental) {              // NORMAL SID
    for(i=0; i<256; i++) {
        silence[i]= SILENCE;

        for (k=0; k<3; k++) {
            saw[k][i]= BASE[k] + round((i/255.0f)*VOL[k]);
            tri[k][i]= BASE[k] + round(i<128? (i/127.0f)*VOL[k]
                                            :((255-i)/127.0f)*VOL[k]);
            sawtri[k][i]=(saw[k][i]+tri[k][i])/2;
            tri[k][256+i]= saw[k][256+i]= sawtri[k][256+i]= BASE[k];
            noise[k][i] = 0x82 + k*2 - 0x10; // compensate for vol only bit
        }
    }
  } else {                          // EXPERIMENTAL WAVEFORMS
    for(i=0; i<256; i++) {
        silence[i]= SILENCE;

        for (k=0; k<3; k++) {
            tri[k][i]= BASE[k] + round((i/255.0f)*VOL[k]);
            saw[k][i]= BASE[k] + round(i<128? (i/127.0f)*VOL[k]
                                            :((255-i)/127.0f)*VOL[k]);
            sawtri[k][i]=(saw[k][i]+tri[k][i])/2;
            tri[k][256+i]= saw[k][256+i]= sawtri[k][256+i]= BASE[k];
            noise[k][i] = 0x82 + k*2 - 0x10; // compensate for vol only bit
        }
    }
  }

    for(j=0; j<4; j++) {
        for(i=0; i<256; i++) {
            if (i<(j+1)*32) {
                pulse[j][0][i] = SILENCE + AMPLITUDE1;
                pulse[j][1][i] = SILENCE + AMPLITUDE2;
                pulse[j][2][i] = SILENCE + AMPLITUDE3;
            } else {
                pulse[j][0][i] = SILENCE - AMPLITUDE1;
                pulse[j][1][i] = SILENCE - AMPLITUDE2;
                pulse[j][2][i] = SILENCE - AMPLITUDE3;
            }
        }
    }

    print(silence, "silence");

    print(tri[0], "tri_vol_01");
    print(tri[1], "tri_vol_10");
    print(tri[2], "tri_vol_11");

    print(saw[0], "saw_vol_01");
    print(saw[1], "saw_vol_10");
    print(saw[2], "saw_vol_11");

    print(noise[0], "noise_vol_01");
    print(noise[1], "noise_vol_10");
    print(noise[2], "noise_vol_11");

    print(pulse[0][0], "p20_vol_01");
    print(pulse[0][1], "p20_vol_10");
    print(pulse[0][2], "p20_vol_11");

    print(pulse[1][0], "p40_vol_01");
    print(pulse[1][1], "p40_vol_10");
    print(pulse[1][2], "p40_vol_11");

    print(pulse[2][0], "p60_vol_01");
    print(pulse[2][1], "p60_vol_10");
    print(pulse[2][2], "p60_vol_11");

    print(pulse[3][0], "p80_vol_01");
    print(pulse[3][1], "p80_vol_10");
    print(pulse[3][2], "p80_vol_11");

    if (mixforms) {
        print(sawtri[0], "sawtri_vol_01");
        print(sawtri[1], "sawtri_vol_10");
        print(sawtri[2], "sawtri_vol_11");

        print(&tri[0][192], "pt25_vol_01");
        print(&tri[1][192], "pt25_vol_10");
        print(&tri[2][192], "pt25_vol_11");

        print(&tri[0][128], "pt50_vol_01");
        print(&tri[1][128], "pt50_vol_10");
        print(&tri[2][128], "pt50_vol_11");

        print(&tri[0][ 64], "pt75_vol_01");
        print(&tri[1][ 64], "pt75_vol_10");
        print(&tri[2][ 64], "pt75_vol_11");

        print(&saw[0][192], "ps25_vol_01");
        print(&saw[1][192], "ps25_vol_10");
        print(&saw[2][192], "ps25_vol_11");

        print(&saw[0][128], "ps50_vol_01");
        print(&saw[1][128], "ps50_vol_10");
        print(&saw[2][128], "ps50_vol_11");

        print(&saw[0][ 64], "ps75_vol_01");
        print(&saw[1][ 64], "ps75_vol_10");
        print(&saw[2][ 64], "ps75_vol_11");

        print(&sawtri[0][192], "pst25_vol_01");
        print(&sawtri[1][192], "pst25_vol_10");
        print(&sawtri[2][192], "pst25_vol_11");

        print(&sawtri[0][128], "pst50_vol_01");
        print(&sawtri[1][128], "pst50_vol_10");
        print(&sawtri[2][128], "pst50_vol_11");

        print(&sawtri[0][ 64], "pst75_vol_01");
        print(&sawtri[1][ 64], "pst75_vol_10");
        print(&sawtri[2][ 64], "pst75_vol_11");
    }

    return 0;
}
