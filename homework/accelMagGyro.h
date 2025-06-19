#ifndef __ACCEL_MAG_GYRO_H__
#define __ACCEL_MAG_GYRO_H__

// 센서 경로 상수
#define ACCEL_PATH "/sys/class/misc/FreescaleAccelerometer/"
#define MAGNE_PATH "/sys/class/misc/FreescaleMagnetometer/"
#define GYRO_PATH  "/sys/class/misc/FreescaleGyroscope/"

// 센서 3축 데이터를 저장하는 구조체
typedef struct {
    int x;
    int y;
    int z;
} Sensor3Axis;

// 센서 enable + 값 읽기
int readAccel(Sensor3Axis* accel);
int readMagnet(Sensor3Axis* mag);
int readGyro(Sensor3Axis* gyro);

#endif // __ACCEL_MAG_GYRO_H__