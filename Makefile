CC = g++
#CC = gcc
FILES = src/*.cpp
OUT_EXE = out_exe.o

build:
	$(CC) -D_GLIBCXX_USE_NANOSLEEP -D__USE_XOPEN2K8 -std=gnu++0x -o $(OUT_EXE) $(FILES)

clean:
	-rm -f *.o core

rebuild: clean build
