#include <iostream>
#include "huffman.h"

int main() {
	huffman h;
	std::cout << "Encoded string : "<< h.encode("abbcccdddd") << std::endl;
	return 0;
}
