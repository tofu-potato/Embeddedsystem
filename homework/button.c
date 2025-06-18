#include "button.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/msg.h>
#include <pthread.h>

#define INPUT_DEVICE_LIST "/dev/input/event"
#define PROBE_FILE "/proc/bus/input/devices"
#define HAVE_TO_FIND_1 "N: Name=\"ecube-button\"\n"
#define HAVE_TO_FIND_2 "H: Handlers=kbd event"

static char buttonPath[200];
static int fd = -1;
static int msgID = -1;
static pthread_t buttonTh_id;

// 디바이스 경로를 자동으로 찾아서 저장
int probeButtonPath(char *newPath) {
    int returnValue = 0;
    int number = 0;
    FILE *fp = fopen(PROBE_FILE, "rt");
    if (fp == NULL) {
        perror("Failed to open input devices list");
        return 0;
    }

    while (!feof(fp)) {
        char tmpStr[200];
        fgets(tmpStr, sizeof(tmpStr), fp);

        if (strcmp(tmpStr, HAVE_TO_FIND_1) == 0) {
            returnValue = 1;
        }

        if (returnValue == 1 && strncmp(tmpStr, HAVE_TO_FIND_2, strlen(HAVE_TO_FIND_2)) == 0) {
            // eventX의 X 추출
            char *p = strstr(tmpStr, "event");
            if (p != NULL) {
                sscanf(p + 5, "%d", &number);  // event 뒤 숫자만 추출
            }
            break;
        }
    }

    fclose(fp);

    if (returnValue == 1) {
        sprintf(newPath, "%s%d", INPUT_DEVICE_LIST, number);
    }

    return returnValue;
}

// 버튼 이벤트를 감지하고 메시지 큐로 전송하는 쓰레드 함수
void* buttonThFunc(void* arg) {
    struct input_event stEvent;
    BUTTON_MSG_T msg;

    while (1) {
        int readSize = read(fd, &stEvent, sizeof(stEvent));
        if (readSize != sizeof(stEvent)) continue;

        if (stEvent.type == EV_KEY) {
            msg.messageNum = 1L;
            msg.keyInput = stEvent.code;
            msg.pressed = stEvent.value;
            msgsnd(msgID, &msg, sizeof(BUTTON_MSG_T) - sizeof(long int), 0);
        }
    }
    return NULL;
}

// 라이브러리 초기화 함수
int buttonInit(void) {
    if (probeButtonPath(buttonPath) == 0) {
        fprintf(stderr, "Failed to find button device\n");
        return 0;
    }

    fd = open(buttonPath, O_RDONLY);
    if (fd < 0) {
        perror("button device open failed");
        return 0;
    }

    msgID = msgget(MESSAGE_ID, IPC_CREAT | 0666);
    if (msgID < 0) {
        perror("msgget failed");
        return 0;
    }

    pthread_create(&buttonTh_id, NULL, buttonThFunc, NULL);
    return 1;
}

// 라이브러리 종료 함수
int buttonExit(void) {
    if (fd >= 0) {
        close(fd);
    }
    msgctl(msgID, IPC_RMID, NULL);
    pthread_cancel(buttonTh_id);
    return 0;
}
