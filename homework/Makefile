CROSS_COMPILE = arm-linux-gnueabi-
CC = $(CROSS_COMPILE)gcc
AR = $(CROSS_COMPILE)ar

TARGET_LIB = libMyPeri.a
LIB_OBJS = led.o button.o buzzer.o fnd.o textlcd.o colorled.o temperature.o accelMagGyro.o

TEST_SRCS = \
    ledtest.c buttontest.c buzzertest.c \
    fndtest.c textlcdtest.c colorledtest.c \
    temperatureTest.c accelMagGyroTest.c

TEST_BINS = \
    ledtest buttontest buzzertest \
    fndtest textlcdtest colorledtest \
    temperatureTest accelMagGyroTest

CFLAGS = -I.

.PHONY: clean

# 기본 목표: make만 입력해도 전체 빌드됨
default: $(TARGET_LIB) $(TEST_BINS)

$(TARGET_LIB): $(LIB_OBJS)
	$(AR) rc $@ $^

# 개별 실행파일 빌드 규칙
ledtest: ledtest.o $(TARGET_LIB)
	$(CC) -o $@ $< -L. -lMyPeri

buttontest: buttontest.o $(TARGET_LIB)
	$(CC) -o $@ $< -L. -lMyPeri -lpthread

buzzertest: buzzertest.o $(TARGET_LIB)
	$(CC) -o $@ $< -L. -lMyPeri

fndtest: fndtest.o $(TARGET_LIB)
	$(CC) -o $@ $< -L. -lMyPeri

textlcdtest: textlcdtest.o $(TARGET_LIB)
	$(CC) -o $@ $< -L. -lMyPeri

colorledtest: colorledtest.o $(TARGET_LIB)
	$(CC) -o $@ $< -L. -lMyPeri

temperatureTest: temperatureTest.o $(TARGET_LIB)
	$(CC) -o $@ $< -L. -lMyPeri

accelMagGyroTest: accelMagGyroTest.o $(TARGET_LIB)
	$(CC) -o $@ $< -L. -lMyPeri

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o *.a $(TEST_BINS)
