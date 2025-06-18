#include "led.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s 0x** (e.g., 0x0F to turn on LED 0~3)\n", argv[0]);
        return -1;
    }

    // 문자열을 정수로 변환 (16진수)
    unsigned int ledData = strtol(argv[1], NULL, 16);

    if (ledLibInit() < 0) {
        fprintf(stderr, "Failed to initialize LED library\n");
        return -1;
    }

    // 8비트 LED 제어 (최대 0xFF)
    for (int i = 0; i < 8; i++) {
        int on = (ledData >> i) & 0x1;
        ledOnOff(i, on);
    }

    sleep(2); // 2초간 LED ON 상태 유지
    ledLibExit(); // 종료 시 LED OFF 및 장치 닫기

    return 0;
}
