FLAGS = -std=c++11 -Wall -c

all: huffman.o des.o main.o
	g++ huffman.o des.o main.o -o execute

main.o: main.cpp
	g++ $(FLAGS) main.cpp

huffman.o: huffman.cpp
	g++ $(FLAGS) huffman.cpp

des.o: des.cpp
	g++ $(FLAGS) des.cpp

clean:
	rm -rf *.o execute