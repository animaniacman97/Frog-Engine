CC = cc
CFLAGS = -Wall -Wextra -Wpedantic -g
SDL_CFLAGS = $(shell pkg-config --cflags sdl3)
SDL_LIBS = $(shell pkg-config --libs sdl3)
LDLIBS = -lm

TARGET = frog

SRC = main.c engine/engine.c player/player.c input/input.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SDL_CFLAGS) $(SRC) -o $(TARGET) $(SDL_LIBS) $(LDLIBS)

clean:
	rm -f $(TARGET)

.PHONY: all clean
