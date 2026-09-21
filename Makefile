TARGET = battery-monitor
SRCS = src/main.c src/battery/battery.c src/core/core.c src/notify/notify.c
OBJS = $(SRCS:.c=.o)

CC = gcc
CFLAGS = -Wall -Isrc

all: build

build: $(TARGET)

run: build
	./$(TARGET)

$(TARGET): $(OBJS)
	$(CC) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all build run clean
clean:
	rm -f $(OBJS) $(TARGET)
