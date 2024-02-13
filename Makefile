CC = g++
CFLAGS = -std=c++11 -Wall
SMFL_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

all: bin bouncing_cube

bin:
	mkdir -p bin

bouncing_cube: bouncing_cube.cpp
	$(CC) $(CFLAGS)  bouncing_cube.cpp -o bin/bouncing_cube $(SMFL_LIBS)

clean:
	cd bin && rm -f *