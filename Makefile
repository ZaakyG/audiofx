CC = gcc
CFLAGS = -Iinclude
# CFLAGS = -Iinclude -Wall -Wextra -lm
LDFLAGS = -lm
LIVEAUDIO = -lportaudio

# Shared source files
COMMON_SRC = \
	src/utils/utils.c \
	src/effects/fx.c \

# Entry points
TEST_SRC = src/main.c
LIVE_SRC = src/listen.c
#SRC = $(wildcard src/**/*.c src/*.c)

# Outputs
TEST_BIN = build/test_app
LIVE_BIN = build/live_app

# Default target
all: live

# Build test version
test: 
	$(CC) $(CFLAGS) $(TEST_SRC) $(COMMON_SRC) -o $(TEST_BIN) $(LDFLAGS)

# Build live version
live:
	$(CC) $(CFLAGS) $(LIVE_SRC) $(COMMON_SRC) -o $(LIVE_BIN) $(LDFLAGS) $(LIVEAUDIO) 

