#include "led.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

static unsigned int ledValue = 0;
static int fd = 0;

int ledOnOff(int ledNum, int onOff)
{
    int mask = 1 << ledNum;
    ledValue &= ~mask;         // 해당 비트를 0으로 초기화
    if (onOff) {
        ledValue |= mask;      // ON이면 해당 비트만 1로 설정
    }
    return write(fd, &ledValue, sizeof(ledValue));
}

int ledLibInit(void)
{
    fd = open(LED_DRIVER_NAME, O_WRONLY);
    ledValue = 0;
    if (fd < 0) {
        perror("ledLibInit: open failed");
        return -1;
    }
    return 0;
}

int ledStatus(void)
{
    return ledValue;
}

int ledLibExit(void)
{
    ledValue = 0;
    ledOnOff(0, 0);  // 모든 LED를 OFF 상태로 초기화
    return close(fd);
}
