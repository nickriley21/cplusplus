CC = g++
CFLAGS = -std=c++11 -Wall
SMFL_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

all: bin bin/bouncing_cube bin/color_cube bin/gravity_cube

bin:
	mkdir -p bin

bin/bouncing_cube: bouncing_cube.cpp
	$(CC) $(CFLAGS)  bouncing_cube.cpp -o bin/bouncing_cube $(SMFL_LIBS)

bin/color_cube: color_cube.cpp
	$(CC) $(CFLAGS)  color_cube.cpp -o bin/color_cube $(SMFL_LIBS)

bin/gravity_cube: gravity_cube.cpp
	$(CC) $(CFLAGS)  gravity_cube.cpp -o bin/gravity_cube $(SMFL_LIBS)

bin/hello: hello.cpp
	$(CC) hello.cpp -o bin/hello

bin/io: io.cpp
	$(CC) io.cpp -o bin/io

display:
	export DISPLAY=$(cat /etc/resolv.conf | grep nameserver | awk '{print $2}'):0.0

clean:
	cd bin && rm -f *