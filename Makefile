CC = g++
CFLAGS = -std=c++17 -Wall
INCLUDE = -I/opt/homebrew/opt/raylib/include
LDFLAGS = -L/opt/homebrew/opt/raylib/lib -lraylib -lm -lpthread

SRC = src/main.cpp src/spaceship.cpp src/game.cpp src/laser.cpp
OUT = space_invader

all:
	$(CC) $(CFLAGS) $(INCLUDE) $(SRC) -o $(OUT) $(LDFLAGS)

clean:
	rm -f $(OUT)
