CC = g++
CFLAGS = -std=c++11 -Wall -Wextra
SMFL_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

all: bin bin/bouncing_cube bin/color_cube bin/gravity_cube bin/selection_sort bin/bubble_sort bin/insertion_sort bin/merge_sort bin/quick_sort bin/heap_sort

bin:
	mkdir -p bin

bin/bouncing_cube: bouncing_cube.cpp
	$(CC) $(CFLAGS)  bouncing_cube.cpp -o bin/bouncing_cube $(SMFL_LIBS)

bin/color_cube: color_cube.cpp
	$(CC) $(CFLAGS)  color_cube.cpp -o bin/color_cube $(SMFL_LIBS)

bin/gravity_cube: gravity_cube.cpp
	$(CC) $(CFLAGS)  gravity_cube.cpp -o bin/gravity_cube $(SMFL_LIBS)

bin/selection_sort: selection_sort.cpp SortManager.cpp SortManager.hpp
	$(CC) $(CFLAGS)  selection_sort.cpp SortManager.cpp -o bin/selection_sort $(SMFL_LIBS)

bin/bubble_sort: bubble_sort.cpp SortManager.cpp SortManager.hpp
	$(CC) $(CFLAGS)  bubble_sort.cpp SortManager.cpp -o bin/bubble_sort $(SMFL_LIBS)

bin/insertion_sort: insertion_sort.cpp SortManager.cpp SortManager.hpp
	$(CC) $(CFLAGS)  insertion_sort.cpp SortManager.cpp -o bin/insertion_sort $(SMFL_LIBS)

bin/merge_sort: merge_sort.cpp SortManager.cpp SortManager.hpp
	$(CC) $(CFLAGS)  merge_sort.cpp SortManager.cpp -o bin/merge_sort $(SMFL_LIBS)

bin/quick_sort: quick_sort.cpp SortManager.cpp SortManager.hpp
	$(CC) $(CFLAGS)  quick_sort.cpp SortManager.cpp -o bin/quick_sort $(SMFL_LIBS)

bin/heap_sort: heap_sort.cpp SortManager.cpp SortManager.hpp
	$(CC) $(CFLAGS)  heap_sort.cpp SortManager.cpp -o bin/heap_sort $(SMFL_LIBS)

bin/hello: hello.cpp
	$(CC) hello.cpp -o bin/hello

bin/io: io.cpp
	$(CC) io.cpp -o bin/io

display:
	export DISPLAY=$(cat /etc/resolv.conf | grep nameserver | awk '{print $2}'):0.0

clean:
	cd bin && rm -f *