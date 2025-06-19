#include <stdio.h>
#include "accelMagGyro.h"

int main() {
    Sensor3Axis accel, mag, gyro;

    if (readAccel(&accel) == 0)
        printf("Accel: X=%d, Y=%d, Z=%d\n", accel.x, accel.y, accel.z);
    else
        printf("Failed to read accelerometer\n");

    if (readMagnet(&mag) == 0)
        printf("Magnet: X=%d, Y=%d, Z=%d\n", mag.x, mag.y, mag.z);
    else
        printf("Failed to read magnetometer\n");

    if (readGyro(&gyro) == 0)
        printf("Gyro: X=%d, Y=%d, Z=%d\n", gyro.x, gyro.y, gyro.z);
    else
        printf("Failed to read gyroscope\n");

    return 0;
}
