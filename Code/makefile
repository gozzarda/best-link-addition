CC=g++

CFLAGS=-std=c++11 -c -Wall -O2

all: speed_test correctness_test

speed_test: speed_test.o algorithms.o graph_gen.o
	$(CC) speed_test.o algorithms.o graph_gen.o -o speed_test

correctness_test: correctness_test.o algorithms.o graph_gen.o
	$(CC) correctness_test.o algorithms.o graph_gen.o -o correctness_test

correctness_test.o: correctness_test.cpp graph_gen.h algorithms.h
	$(CC) $(CFLAGS) correctness_test.cpp

speed_test.o: speed_test.cpp graph_gen.h algorithms.h
	$(CC) $(CFLAGS) speed_test.cpp

graph_gen.o: graph_gen.cpp graph_gen.h algorithms.h
	$(CC) $(CFLAGS) graph_gen.cpp

algorithms.o: algorithms.cpp algorithms.h
	$(CC) $(CFLAGS) algorithms.cpp

clean:
	rm -f *.o