CC = gcc
CFLAGS = -Wall -Wextra -pedantic -O2 -lpthread

TARGET = tcp

SRC = main.c server_config.c clients.c

all:
	$(CC) -o $(TARGET) $(SRC) $(CFLAGS)

run:
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean
