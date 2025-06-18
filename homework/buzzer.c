#include "buzzer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>

#define BUZZER_BASE_SYS_PATH "/sys/bus/platform/devices/"
#define BUZZER_FILENAME      "peribuzzer"
#define BUZZER_ENABLE_NAME   "enable"
#define BUZZER_FREQUENCY_NAME "frequency"
#define MAX_SCALE_STEP 8

// 도~도까지 8음계
const int musicScale[MAX_SCALE_STEP] = {
    262, // 도
    294, // 레
    330, // 미
    349, // 파
    392, // 솔
    440, // 라
    494, // 시
    523  // 도
};

static char gBuzzerBaseSysDir[128] = {0,}; // ex: "/sys/bus/platform/devices/peribuzzer.0/"

// peribuzzer.XX 경로 탐색
int findBuzzerSysPath() {
    DIR *dir_info = opendir(BUZZER_BASE_SYS_PATH);
    if (dir_info == NULL) return 1;

    while (1) {
        struct dirent *dir_entry = readdir(dir_info);
        if (dir_entry == NULL) break;

        if (strncasecmp(BUZZER_FILENAME, dir_entry->d_name, strlen(BUZZER_FILENAME)) == 0) {
            sprintf(gBuzzerBaseSysDir, "%s%s/", BUZZER_BASE_SYS_PATH, dir_entry->d_name);
            closedir(dir_info);
            return 0; // 성공
        }
    }

    closedir(dir_info);
    return 1; // 실패
}

// enable = 1 or 0
void buzzerEnable(int bEnable) {
    char path[200];
    sprintf(path, "%s%s", gBuzzerBaseSysDir, BUZZER_ENABLE_NAME);

    int fd = open(path, O_WRONLY);
    if (fd < 0) return;

    if (bEnable)
        write(fd, "1", 1);
    else
        write(fd, "0", 1);

    close(fd);
}

// 주파수 설정
void setFrequency(int frequency) {
    char path[200];
    sprintf(path, "%s%s", gBuzzerBaseSysDir, BUZZER_FREQUENCY_NAME);

    int fd = open(path, O_WRONLY);
    if (fd < 0) return;

    dprintf(fd, "%d", frequency);
    close(fd);
}

// 초기화
int buzzerInit(void) {
    return findBuzzerSysPath();  // 0이면 성공
}

// 주어진 scale(0~7)에 해당하는 음계 재생
int buzzerPlaySong(int scale) {
    if (scale < 0 || scale >= MAX_SCALE_STEP)
        return -1;

    setFrequency(musicScale[scale]);
    buzzerEnable(1);
    return 0;
}

// 소리 끔
int buzzerStopSong(void) {
    buzzerEnable(0);
    return 0;
}

// 종료
int buzzerExit(void) {
    buzzerStopSong();
    return 0;
}
