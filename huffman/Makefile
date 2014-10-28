FLAGS = -c -std=c++11 -Wall

all: huffman

huffman:  huffman.o main.o	
	g++  huffman.o  main.o -o huffman_algo.o

main.o: main.cpp
	g++ $(FLAGS) main.cpp

huffman.o: huffman.cpp huffman.h
	g++ $(FLAGS) huffman.cpp huffman.h

clean:
	rm -rf *.o