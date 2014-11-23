FLAGS = -std=c++11 -Wall -c

all: rsa.o gost.o huffman.o des.o main.o
	g++ rsa.o gost.o huffman.o des.o main.o -o execute

main.o: main.cpp
	g++ $(FLAGS) main.cpp

huffman.o: huffman.cpp
	g++ $(FLAGS) huffman.cpp

des.o: des.cpp
	g++ $(FLAGS) des.cpp

gost.o: gost.cpp
	g++ $(FLAGS) gost.cpp

rsa.o: rsa.cpp
	g++ $(FLAGS) rsa.cpp

clean:
	rm -rf *.o execute