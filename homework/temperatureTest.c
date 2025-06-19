#include <stdio.h>
#include <unistd.h>
#include "temperature.h"

int main() {
    int spi_fd = spi_init(SPI_DEV_PATH);
    if (spi_fd < 0) return -1;

    double temp = read_temperature(spi_fd);
    if (temp >= 0)
        printf("Current Temperature: %.2f °C\n", temp);
    else
        printf("Failed to read temperature.\n");

    close(spi_fd);
    return 0;
}
