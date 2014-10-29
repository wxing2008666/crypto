FLAGS = -std=c++11 -Wall -c

all: huffman.o main.o
	g++ huffman.o main.o -o execute

main.o: main.cpp
	g++ $(FLAGS) main.cpp

huffman.o: huffman.cpp
	g++ $(FLAGS) huffman.cpp

clean:
	rm -rf *.o