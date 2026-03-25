CC = gcc
CFLAGS = -Iinclude

SRC = $(wildcard src/**/*.c src/*.c)
OUT = app

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)
