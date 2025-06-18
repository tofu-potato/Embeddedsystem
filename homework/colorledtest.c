#include <stdio.h>
#include <stdlib.h>
#include "colorled.h"

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <R 0-100> <G 0-100> <B 0-100>\n", argv[0]);
        printf("Example: %s 100 100 100 → White\n", argv[0]);
        return 1;
    }

    int r = atoi(argv[1]);
    int g = atoi(argv[2]);
    int b = atoi(argv[3]);

    colorLedInit();
    colorLedSetPercent(r, COLOR_R);
    colorLedSetPercent(g, COLOR_G);
    colorLedSetPercent(b, COLOR_B);
    colorLedExit();

    return 0;
}
