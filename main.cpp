#include <iostream>
#include "huffman.h"

int main() {
	huffman h;
	std::cout << h.encode("test_string_for_encode") << std::endl;
	return 0;
}
