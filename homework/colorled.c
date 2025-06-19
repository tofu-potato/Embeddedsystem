#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "colorled.h"

static const char* pwmChips[] = { PWM_CHIP_B, PWM_CHIP_G, PWM_CHIP_R };

// pwm0 export 후 약간의 시간 대기
static void pwmExport(int chipIndex) {
    char path[64];
    int fd;
    sprintf(path, "%sexport", pwmChips[chipIndex]);
    fd = open(path, O_WRONLY);
    if (fd >= 0) {
        write(fd, "0", 1);  // pwm0 export
        close(fd);
        usleep(300000);  // 0.3초 대기
    }
}

// pwm0 unexport
static void pwmUnexport(int chipIndex) {
    char path[64];
    int fd;
    sprintf(path, "%sunexport", pwmChips[chipIndex]);
    fd = open(path, O_WRONLY);
    if (fd >= 0) {
        write(fd, "0", 1);
        close(fd);
    }
}

// period 설정
static void pwmSetPeriod(int chipIndex) {
    char path[128];
    sprintf(path, "%spwm0/period", pwmChips[chipIndex]);
    int fd = open(path, O_WRONLY);
    if (fd >= 0) {
        dprintf(fd, "%d", PWM_PERIOD_NS);
        close(fd);
    }
}

// duty 설정
static void pwmSetDuty(int duty, int chipIndex) {
    char path[128];
    sprintf(path, "%spwm0/duty_cycle", pwmChips[chipIndex]);
    int fd = open(path, O_WRONLY);
    if (fd >= 0) {
        dprintf(fd, "%d", duty);
        close(fd);
    }
}

// enable/disable
static void pwmSetEnable(int enable, int chipIndex) {
    char path[128];
    sprintf(path, "%spwm0/enable", pwmChips[chipIndex]);
    int fd = open(path, O_WRONLY);
    if (fd >= 0) {
        dprintf(fd, "%d", enable);
        close(fd);
    }
}

void colorLedInit(void) {
    for (int i = 0; i < 3; i++) {
        pwmExport(i);
        pwmSetDuty(PWM_PERIOD_NS, i);         // 초기 duty: 0% 밝기 (sink 방식)
        pwmSetPeriod(i);
        pwmSetEnable(1, i);
    }
}

void colorLedSetPercent(int percent, int color) {
    if (percent < 0) percent = 0;
    if (percent > 100) percent = 100;
    int duty = (100 - percent) * PWM_PERIOD_NS / 100;  // sink 방식
    pwmSetDuty(duty, color);
}

void colorLedExit(void) {
    for (int i = 0; i < 3; i++) {
        pwmSetEnable(0, i);
        pwmUnexport(i);
    }
}
