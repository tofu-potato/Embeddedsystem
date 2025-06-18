CROSS_COMPILE = arm-linux-gnueabi-
CC = $(CROSS_COMPILE)gcc
AR = $(CROSS_COMPILE)ar

TARGET_LIB = libMyPeri.a
LIB_OBJS = led.o button.o buzzer.o

TEST_SRCS = ledtest.c buttontest.c buzzertest.c
TEST_BINS = ledtest buttontest buzzertest

CFLAGS = -I.

.PHONY: all clean

all: $(TARGET_LIB) $(TEST_BINS)

$(TARGET_LIB): $(LIB_OBJS)
	$(AR) rc $@ $^

ledtest: ledtest.o $(TARGET_LIB)
	$(CC) -o $@ ledtest.o -L. -lMyPeri

buttontest: buttontest.o $(TARGET_LIB)
	$(CC) -o $@ buttontest.o -L. -lMyPeri -lpthread

buzzertest: buzzertest.o $(TARGET_LIB)
	$(CC) -o $@ buzzertest.o -L. -lMyPeri

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o *.a $(TEST_BINS)
