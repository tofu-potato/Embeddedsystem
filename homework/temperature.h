#ifndef __TEMPERATURE_H__
#define __TEMPERATURE_H__

// SPI 장치 경로 예: "/dev/spidev1.0"
#define SPI_DEV_PATH "/dev/spidev1.0"

// SPI 초기화 함수: 성공 시 파일 디스크립터 반환, 실패 시 -1
int spi_init(const char* device_path);

// LM74 온도 읽기 함수: 온도를 Celsius(double)로 반환, 실패 시 음수 반환
double read_temperature(int spi_fd);

#endif // __TEMPERATURE_H__
