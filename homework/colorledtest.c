#include <stdio.h>
#include <stdlib.h>
#include "colorled.h"

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s R G B\n", argv[0]);
        return 1;
    }

    int r = atoi(argv[1]);
    int g = atoi(argv[2]);
    int b = atoi(argv[3]);

    if (r < 0 || r > 100 || g < 0 || g > 100 || b < 0 || b > 100) {
        fprintf(stderr, "Error: R/G/B values must be between 0 and 100.\n");
        return 1;
    }

    colorLedInit();
    colorLedSetPercent(r, COLOR_R);
    colorLedSetPercent(g, COLOR_G);
    colorLedSetPercent(b, COLOR_B);

    printf("Color LED set to R=%d%% G=%d%% B=%d%%\n", r, g, b);
    return 0;
}
