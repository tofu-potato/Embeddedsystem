#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "colorled.h"

static void pwmExportAll() {
    int fd;
    fd = open(PWM_CHIP_R PWM_EXPORT, O_WRONLY); write(fd, "0", 1); close(fd);
    fd = open(PWM_CHIP_G PWM_EXPORT, O_WRONLY); write(fd, "0", 1); close(fd);
    fd = open(PWM_CHIP_B PWM_EXPORT, O_WRONLY); write(fd, "0", 1); close(fd);
}

static void pwmUnexportAll() {
    int fd;
    fd = open(PWM_CHIP_R PWM_UNEXPORT, O_WRONLY); write(fd, "0", 1); close(fd);
    fd = open(PWM_CHIP_G PWM_UNEXPORT, O_WRONLY); write(fd, "0", 1); close(fd);
    fd = open(PWM_CHIP_B PWM_UNEXPORT, O_WRONLY); write(fd, "0", 1); close(fd);
}

static void pwmSetPeriod(int chipIndex) {
    const char* paths[] = { PWM_CHIP_B, PWM_CHIP_G, PWM_CHIP_R };
    char path[128];
    sprintf(path, "%spwm0/period", paths[chipIndex]);
    int fd = open(path, O_WRONLY);
    dprintf(fd, "%d", PWM_PERIOD_NS);
    close(fd);
}

static void pwmSetDuty(int duty, int chipIndex) {
    const char* paths[] = { PWM_CHIP_B, PWM_CHIP_G, PWM_CHIP_R };
    char path[128];
    sprintf(path, "%spwm0/duty_cycle", paths[chipIndex]);
    int fd = open(path, O_WRONLY);
    dprintf(fd, "%d", duty);
    close(fd);
}

static void pwmEnableAll() {
    int fd;
    fd = open(PWM_CHIP_R PWM_ENABLE, O_WRONLY); write(fd, "1", 1); close(fd);
    fd = open(PWM_CHIP_G PWM_ENABLE, O_WRONLY); write(fd, "1", 1); close(fd);
    fd = open(PWM_CHIP_B PWM_ENABLE, O_WRONLY); write(fd, "1", 1); close(fd);
}

static void pwmDisableAll() {
    int fd;
    fd = open(PWM_CHIP_R PWM_ENABLE, O_WRONLY); write(fd, "0", 1); close(fd);
    fd = open(PWM_CHIP_G PWM_ENABLE, O_WRONLY); write(fd, "0", 1); close(fd);
    fd = open(PWM_CHIP_B PWM_ENABLE, O_WRONLY); write(fd, "0", 1); close(fd);
}

void colorLedInit(void) {
    pwmExportAll();
    pwmSetDuty(0, COLOR_R);
    pwmSetDuty(0, COLOR_G);
    pwmSetDuty(0, COLOR_B);
    pwmSetPeriod(COLOR_R);
    pwmSetPeriod(COLOR_G);
    pwmSetPeriod(COLOR_B);
    pwmEnableAll();
}

void colorLedSetPercent(int percent, int color) {
    if (percent < 0) percent = 0;
    if (percent > 100) percent = 100;
    int duty = (100 - percent) * PWM_PERIOD_NS / 100;  // SINK 방식
    pwmSetDuty(duty, color);
}

void colorLedExit(void) {
    pwmDisableAll();
    pwmUnexportAll();
}
