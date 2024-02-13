CC = g++
CFLAGS = -std=c++11 -Wall
SMFL_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

all: bin bouncing_cube hello io

bin:
	mkdir -p bin

bouncing_cube: bouncing_cube.cpp
	$(CC) $(CFLAGS)  bouncing_cube.cpp -o bin/bouncing_cube $(SMFL_LIBS)

hello: hello.cpp
	$(CC) hello.cpp -o bin/hello

io: io.cpp
	$(CC) io.cpp -o bin/io

display:
	export DISPLAY=$(cat /etc/resolv.conf | grep nameserver | awk '{print $2}'):0.0

clean:
	cd bin && rm -f *