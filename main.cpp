#include <iostream>
#include "huffman.h"

int main() {
	huffman h;
	std::cout << h.encode("123") << std::endl;
	return 0;
}
