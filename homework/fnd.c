#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "fnd.h"  // 함수 원형 포함

#define FND_DRIVER_NAME "/dev/perifnd"

int fndDisp(int num, int dotflag) {
    int fd;
    int temp, i;
    stFndWriteForm stWriteData;

    // dot과 valid 설정
    for (i = 0; i < MAX_FND_NUM; i++) {
        stWriteData.DataDot[i] = (dotflag & (0x1 << i)) ? 1 : 0;
        stWriteData.DataValid[i] = 1;
    }

    // 숫자 분해 (최대 6자리)
    temp = num % 1000000;
    stWriteData.DataNumeric[0] = temp / 100000;
    temp = num % 100000;
    stWriteData.DataNumeric[1] = temp / 10000;
    temp = num % 10000;
    stWriteData.DataNumeric[2] = temp / 1000;
    temp = num % 1000;
    stWriteData.DataNumeric[3] = temp / 100;
    temp = num % 100;
    stWriteData.DataNumeric[4] = temp / 10;
    stWriteData.DataNumeric[5] = temp % 10;

    // 드라이버 open
    fd = open(FND_DRIVER_NAME, O_RDWR);
    if (fd < 0) {
        perror("FND driver open error");
        return 0;
    }

    // write 호출
    write(fd, &stWriteData, sizeof(stFndWriteForm));
    close(fd);
    return 1;
}
