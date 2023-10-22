
#include <stdio.h>

// rates in ms, 6581 datasheet, table 2 - envelope rates

static const int attack_rates[16] =
    {     2,   8,  16,  24,   38,   56,   68,   80,
        100, 250, 500, 800, 1000, 3000, 5000, 8000 };

static const int decay_release_rates[16] =
    {     6,  24,   48,   72,  114,  168,   204,   240,
        300, 750, 1500, 2400, 3000, 9000, 15000, 24000 };

static void print(int i, int v) {
    printf("0x%04x", v>0x0f00 ? 0x0f00 : v);
    if (i==7) printf(")\n    dta a(");
    else if (i==15) printf(")\n");
    else printf(", ");
}

int main(int argc, char **argv) {
    int i;


    printf("attacks\n    dta a(");
    for (i=0; i<16; i++) {
        print(i, (0x0f00 / (attack_rates[i]/10.0))+0.5);
    }
    printf("releases\n    dta a(");
    for (i=0; i<16; i++) {
        print(i, (0x0f00 / (decay_release_rates[i]/10.0))+0.5);
    }
}

