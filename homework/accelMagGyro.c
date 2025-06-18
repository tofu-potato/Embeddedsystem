#include "accelMagGyro.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

static int enable_sensor(const char* path) {
    int fd = open(path, O_WRONLY);
    if (fd < 0) return -1;
    dprintf(fd, "1");
    close(fd);
    return 0;
}

static int read_sensor_data(const char* path, Sensor3Axis* sensor) {
    FILE* fp = fopen(path, "rt");
    if (!fp) return -1;
    fscanf(fp, "%d, %d, %d", &sensor->x, &sensor->y, &sensor->z);
    fclose(fp);
    return 0;
}

int readAccel(Sensor3Axis* accel) {
    if (enable_sensor(ACCEL_PATH "enable") < 0) return -1;
    return read_sensor_data(ACCEL_PATH "data", accel);
}

int readMagnet(Sensor3Axis* mag) {
    if (enable_sensor(MAGNE_PATH "enable") < 0) return -1;
    return read_sensor_data(MAGNE_PATH "data", mag);
}

int readGyro(Sensor3Axis* gyro) {
    if (enable_sensor(GYRO_PATH "enable") < 0) return -1;
    return read_sensor_data(GYRO_PATH "data", gyro);
}
