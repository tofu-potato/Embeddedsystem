#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "fnd.h"

#define MODE_STATIC_DIS  0
#define MODE_TIME_DIS    1
#define MODE_COUNT_DIS   2
#define MODE_OFF         3

void print_help() {
    printf("Usage:\n");
    printf("  fndtest s <number>        : static display (0~999999)\n");
    printf("  fndtest t                 : display current time (hhmmss)\n");
    printf("  fndtest c <maxcounter>    : count from 0 to maxcounter (1s interval)\n");
    printf("  fndtest o                 : turn off FND\n");
}

int main(int argc, char *argv[]) {
    int mode = -1;
    int number = 0;

    if (argc < 2) {
        print_help();
        return -1;
    }

    if (strcmp(argv[1], "s") == 0) {
        if (argc < 3) {
            print_help();
            return -1;
        }
        mode = MODE_STATIC_DIS;
        number = atoi(argv[2]);
    } else if (strcmp(argv[1], "t") == 0) {
        mode = MODE_TIME_DIS;
    } else if (strcmp(argv[1], "c") == 0) {
        if (argc < 3) {
            print_help();
            return -1;
        }
        mode = MODE_COUNT_DIS;
        number = atoi(argv[2]);
    } else if (strcmp(argv[1], "o") == 0) {
        mode = MODE_OFF;
    } else {
        print_help();
        return -1;
    }

    if (mode == MODE_STATIC_DIS) {
        fndDisp(number, 0);  // dot 없이 표시
    } else if (mode == MODE_TIME_DIS) {
        struct tm *ptmcur;
        time_t tTime;

        if (time(&tTime) == -1) return -1;
        ptmcur = localtime(&tTime);

        number = ptmcur->tm_hour * 10000;
        number += ptmcur->tm_min * 100;
        number += ptmcur->tm_sec;

        fndDisp(number, 0b001010);  // 중간에 콜론처럼 보이도록 dot
    } else if (mode == MODE_COUNT_DIS) {
        for (int counter = 0; counter <= number; counter++) {
            if (!fndDisp(counter, 0)) break;
            sleep(1);
        }
    } else if (mode == MODE_OFF) {
        fndDisp(0, 0);  // 숫자 0으로 표시
    }

    return 0;
}
