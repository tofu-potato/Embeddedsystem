#include "temperature.h"
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

static char gbuf[10];

int spi_init(const char* device_path)
{
    int fd;
    __u8 mode, lsb, bits;
    __u32 speed = 20000;

    fd = open(device_path, O_RDWR);
    if (fd < 0) {
        perror("Failed to open SPI device");
        return -1;
    }

    if (ioctl(fd, SPI_IOC_RD_MODE, &mode) < 0) {
        perror("SPI rd_mode");
        close(fd);
        return -1;
    }

    if (ioctl(fd, SPI_IOC_RD_LSB_FIRST, &lsb) < 0) {
        perror("SPI rd_lsb_first");
        close(fd);
        return -1;
    }

    if (ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits) < 0) {
        perror("SPI bits_per_word");
        close(fd);
        return -1;
    }

    return fd;
}

double read_temperature(int spi_fd)
{
    int len;
    memset(gbuf, 0, sizeof(gbuf));
    len = read(spi_fd, gbuf, 2);  // 2바이트 읽기
    if (len != 2) {
        perror("SPI read failed");
        return -1.0;
    }

    int raw_value = 0;
    raw_value = (gbuf[1] >> 3);  // LSB: 하위 5비트
    raw_value |= ((int)gbuf[0]) << 5;  // MSB: 상위 8비트

    // signed 처리 (13비트 2의 보수)
    if (raw_value & (1 << 12)) {  // 음수면 sign extend
        raw_value |= 0xFFFFE000;
    }

    return raw_value * 0.0625;
}
