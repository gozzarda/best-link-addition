CC=g++

CFLAGS=-std=c++11 -c -Wall -O2

whatever: main.o algorithms.o
	$(CC) main.o algorithms.o -o whatever

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

algorithms.o: algorithms.cpp
	$(CC) $(CFLAGS) algorithms.cpp