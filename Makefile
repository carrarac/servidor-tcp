CC = gcc
CFLAGS = -I./ -Wall -Wextra -pedantic -O2 -fsanitize=address
SOURCES = server_config.c clients.c main.c
TARGET = tcp


all:
	$(CC) $(SOURCES) -o $(TARGET) $(CFLAGS)

clean:
	rm -rf $(TARGET)
