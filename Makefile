CC=clang++
CFLAGS=-std=c++23

install:
	mkdir -p /usr/include/tiny/
	cp inc/*.h /usr/include/tiny/